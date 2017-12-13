// Simulator.cpp : Defines the entry point for the console application.
//

#include "../include/simulator.h"
#include <cassert>
#include <algorithm>
std::unordered_set<int64_t> breakpoints = { 3 };


Simulator::Simulator(std::vector<Data> boot_disk) : simState({ RegisterFile(), boot_disk, 0}),
													reorder_buffer_(&simState.register_file),
													alus_(2, ALU(&simState, &reorder_buffer_)),
													fetcher(&simState, &branch_predictor),
													load_store(LoadStore(&simState, &reorder_buffer_)),
													branch_unit(&branch_predictor, &simState)
{
	simState.memory = boot_disk;
	for(auto &alu : alus_)
	{
		simState.register_file.reservation_stations.push_back(&alu.reservation_station);
	}
	simState.register_file.reservation_stations.push_back(&load_store.reservation_station);
}

Simulator::~Simulator()
{
}

void Simulator::fetch() {
	if (fetcher.state == READY) {
		fetcher.state = EXECUTING;
	}
}

/*
 * Insert NOPS for nearest hazard. Instruction Buffer > Inputs_Buffers > Execution Units
 */
void Simulator::decode()
{
	const auto fetch_buffer = &simState.register_file.fetch_buffer;
	if (fetcher.state == DONE && instruction_buffer.size() < 128) {
		for (const auto next : (*fetch_buffer)) {
			instruction_buffer.push(next.instruction);
		}
		(*fetch_buffer).clear();
		state = READY;
		fetcher.state = READY;
	}
}

void Simulator::writeback()
{
	reorder_buffer_.writeback();
}

int Simulator::execute(const Instruction current_instruction) {
	 

	if (breakpoints.find(current_instruction.location) != breakpoints.end()) {
		int a = 3;
		std::cout << "";
	}

	if (current_instruction.opcode.settings.unit == SKIP)
	{
		state = READY;
		return 0;
	}

    bool isHazard = findHazard(current_instruction);
    if(isHazard) {
        simState.register_file.print(Instruction(NOP));
        instruction_buffer.push_front(current_instruction);
        return 0;
    }
	state = READY;
    switch(current_instruction.opcode.settings.unit){
        case MATH:
			for(auto &alu : alus_)
			{
				if (alu.reservation_station.is_free())
				{
					alu.reservation_station.insert(current_instruction);
					reorder_buffer_.insert(current_instruction);
					return 0;
				}
			}
			instruction_buffer.push_front(current_instruction);
			break;
        case LDSTR:
			if (load_store.reservation_station.is_free())
			{
				load_store.reservation_station.insert(current_instruction);
				reorder_buffer_.insert(current_instruction);
			}else
			{
				instruction_buffer.push_front(current_instruction);
			}
            break;
        case BRANCH:
            branch_unit.input.push(current_instruction);
            break;
        case SKIP:break;
    }
    return 0;
};

int Simulator::tick() {

	fetch();
	decode();
	auto isExecuting = std::find_if(alus_.begin(), alus_.end(), [](ALU alu) {return alu.state == EXECUTING; });
	if (load_store.state == EXECUTING || branch_unit.state == EXECUTING || isExecuting != alus_.end())
	{
		return 0;
	}
	if (!instruction_buffer.isEmpty()) {

		stall_instruction = instruction_buffer.pop();
		execute(stall_instruction);

	}
	return 0;
}

void Simulator::flush() {
	instruction_buffer.flush();
	simState.register_file.fetch_buffer.clear();
    branch_unit.input.flush();
	fetcher.state = READY;
    simState.flush = false;
}

void Simulator::simulate() {
	state = READY;
	fetcher.state = READY;
	load_store.state = READY;
	branch_unit.state = READY;
	std::for_each(alus_.begin(), alus_.end(), [](ALU &alu) {alu.state = READY; });
	simState.register_file.stall = false;
	/*
	 * Execute pipeline stages.
	 */
	while (true) {
		int err = 0;
		ticks++;
		err = tick();
		//If halted, just stop
		if (branch_unit.halt) {
			return;
		}
		fetcher.tick();
		branch_unit.tick();
		if (simState.flush) {
			flush();
		}
		simState.memory.tick();
		load_store.tick();
		std::for_each(alus_.begin(), alus_.end(), [](ALU &alu) {alu.tick(); });
		writeback();
	}
}

bool Simulator::findHazard(Instruction other) {

	auto aluHazard = std::find_if(alus_.begin(), alus_.end(), [other](ALU alu) {return alu.is_hazard(other); });

	return branch_unit.isHazard(other) || load_store.isHazard(other) || aluHazard != alus_.end();
}


