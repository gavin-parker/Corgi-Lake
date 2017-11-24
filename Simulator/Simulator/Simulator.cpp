// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simulator.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
std::unordered_set<int64_t> breakpoints = { 3 };


Simulator::Simulator(std::vector<Data> boot_disk) : simState({ RegisterFile(), boot_disk, 0 }), alu(1, &simState), fetcher(&simState, &branch_predictor), load_store(LoadStore(&simState)), branch_unit(&alu, &load_store, &branch_predictor, &simState)
{
	simState.memory = boot_disk;
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
	if (fetcher.state == DONE) {
		for (auto data : simState.register_file.fetch_buffer) {
			const auto next = data.instruction;
			size_t nops = 0;
			nops = instruction_buffer.find_hazard(next);
			if (!nops) {
				nops = std::max(load_store.findHazard(next), alu.find_hazard(next));
				nops = std::max(nops, branch_unit.findHazard(next));
			}
			for (int i = 0; i < nops; i++) {
				instruction_buffer.push(Instruction(NOP));
			}
			instruction_buffer.push(next);
		}
		simState.register_file.fetch_buffer.clear();
		state = READY;
		fetcher.state = READY;
	}
}

void Simulator::writeback()
{
	alu.write();
	load_store.write();
}

//mega code smell
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

	if (current_instruction.opcode.settings.unit == LDSTR) {
		load_store.input.push(current_instruction);
		assert(load_store.input.size() == 1);
		state = READY;
		return 0;
	}
	if (current_instruction.opcode.settings.unit == BRANCH) {
		branch_unit.input.push(current_instruction);
		assert(branch_unit.input.size() == 1);
		state = READY;
		return 0;
	}
	if (current_instruction.opcode.settings.unit == MATH) {
		alu.input->push(current_instruction);
		assert(alu.input->size() == 1);
		state = READY;
	}
	return 0;
};

int Simulator::tick() {
	//If halted, just stop
	if (branch_unit.halt) {
		return HALT_PROGRAM;
	}
	fetch();
	decode();
	if (load_store.state == EXECUTING || branch_unit.state == EXECUTING || alu.isExecuting())
	{
		return 0;
	}
	if (!instruction_buffer.isEmpty()) {

		stall_instruction = instruction_buffer.pop();

		if (execute(stall_instruction) == HALT_PROGRAM) {
			return HALT_PROGRAM;
		}
	}
	return 0;
}

void Simulator::flush() {
	//alu.flush();
	//load_store.flush();
	//branch_unit.flush();
	instruction_buffer.flush();
	simState.register_file.fetch_buffer.clear();
	simState.flush = false;
}

void Simulator::simulate() {
	state = READY;
	fetcher.state = READY;
	load_store.state = READY;
	branch_unit.state = READY;
	while (true) {
		int err = 0;
		ticks++;
		err = tick();
		if (err == HALT_PROGRAM)
		{
			return;
		}
		fetcher.tick();
		branch_unit.tick();
		if (simState.flush) {
			flush();
		}
		simState.memory.tick();
		load_store.tick();
		alu.tick();
		writeback();

	}
}


