// Simulator.cpp : Defines the entry point for the console application.
//

#include "../include/simulator.h"
#include <algorithm>


Simulator::Simulator(std::vector<Data> boot_disk, uint64_t alu_count, uint64_t ldstr_count) : simState({RegisterFile(), Memory(boot_disk), 0}),
                                                    reorder_buffer_(&simState.register_file, &simState, &simState.memory),
                                                    alus_(alu_count, ALU(&simState, &reorder_buffer_)),
                                                    fetcher(&simState, &branch_predictor),
                                                    load_stores_(ldstr_count, LoadStore(&simState, &reorder_buffer_)),
                                                    branch_unit(&reorder_buffer_, &branch_predictor, &simState) {
    for (auto &alu : alus_) {
        simState.register_file.reservation_stations.push_back(&alu.reservation_station);
    }
    for (auto &load_store : load_stores_) {
        simState.register_file.reservation_stations.push_back(&load_store.reservation_station);
    }
    simState.register_file.reservation_stations.push_back(&branch_unit.reservation_station);
}

Simulator::~Simulator()
= default;

void Simulator::fetch() {
    if (fetcher.state == READY) {
        fetcher.state = EXECUTING;
    }
}

/*
 * Insert NOPS for nearest hazard. Instruction Buffer > Inputs_Buffers > Execution Units
 */
void Simulator::decode() {
    const auto fetch_buffer = &simState.register_file.fetch_buffer;
    if (fetcher.state == DONE && instruction_buffer.size() < (max_instruction_queue_length - fetcher.max_fetch)) {
        int instructions_pushed = 0;
        for (const auto &next : (*fetch_buffer)) {
            if (instructions_pushed == fetcher.max_fetch) break;
            instruction_buffer.push(next.instruction);
            instructions_pushed++;
        }
        (*fetch_buffer).clear();
        state = READY;
        fetcher.state = READY;
    }
}

void Simulator::writeback() {
    reorder_buffer_.writeback();
}

int Simulator::execute(Instruction current_instruction) {

    if (current_instruction.opcode.settings.unit == SKIP) {
        state = READY;
        return 0;
    }

    state = READY;
    switch (current_instruction.opcode.settings.unit) {
        case MATH:
            for (auto &alu : alus_) {
                if (alu.reservation_station.is_free()) {
                    current_instruction.tag = counter;
                    counter++;
                    alu.reservation_station.insert(current_instruction);
                    reorder_buffer_.insert(current_instruction);
                    return 0;
                }
            }
            instruction_buffer.push_front(current_instruction);
            break;
        case LDSTR:
            for (auto &load_store : load_stores_) {
                if (load_store.reservation_station.is_free()) {
                    current_instruction.tag = counter;
                    counter++;
                    load_store.reservation_station.insert(current_instruction);
                    reorder_buffer_.insert(current_instruction);
                    return 0;
                }
            }
            instruction_buffer.push_front(current_instruction);
            break;
        case BRANCH:
            if (branch_unit.reservation_station.is_free()) {
                current_instruction.tag = counter;
                counter++;
                branch_unit.reservation_station.insert(current_instruction);
                reorder_buffer_.insert(current_instruction);
            } else {
                instruction_buffer.push_front(current_instruction);
            }

            break;
        case SKIP:
            break;
    }
    return 0;
};

int Simulator::tick() {

    fetch();
    decode();
    for (int i = 0; i < max_issue; i++) {
        if (!instruction_buffer.isEmpty()) {
            stall_instruction = instruction_buffer.pop();
            execute(stall_instruction);

        }
    }
    return 0;
}

void Simulator::flush() {
    instruction_buffer.flush();
    simState.register_file.fetch_buffer.clear();
    fetcher.state = READY;
    for (auto &reservation_station : simState.register_file.reservation_stations) {
        reservation_station->clear();
    }
    for(auto &load_store : load_stores_) {
        load_store.result_ready = false;
        load_store.state = READY;
    }
    for (auto &alu : alus_) {
        alu.result_ready = false;
        alu.state = READY;
    }
    branch_unit.state = READY;
    for (auto &i : simState.register_file.register_address_table) {
        i = nullptr;
    }
    simState.flush = false;
}

void Simulator::simulate() {
    state = READY;
    fetcher.state = READY;
    branch_unit.state = READY;
    std::for_each(load_stores_.begin(), load_stores_.end(), [](LoadStore &ldstr) { ldstr.state = READY; });
    std::for_each(alus_.begin(), alus_.end(), [](ALU &alu) { alu.state = READY; });
    simState.register_file.stall = false;
    /*
     * Execute pipeline stages.
     */
    while (true) {
        ticks++;
        tick();
        //If halted, just stop
        if (branch_unit.halt) {
            return;
        }
        fetcher.tick();
        branch_unit.tick();
        simState.memory.tick();
        std::for_each(load_stores_.begin(), load_stores_.end(), [](LoadStore &ldstr) { ldstr.tick(); });
        std::for_each(alus_.begin(), alus_.end(), [](ALU &alu) { alu.tick(); });
        writeback();
        if (simState.flush) {
            flush();
        }
    }
}

