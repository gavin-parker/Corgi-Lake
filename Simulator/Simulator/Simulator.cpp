// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simulator.h"
#include <string>
#include <iostream>
#include <algorithm>

std::unordered_set<int64_t> breakpoints = { 3 };


Simulator::Simulator(std::vector<Data> boot_disk) : simState({ RegisterFile(), boot_disk, 0 }), alu(2, &simState), fetcher(&simState), load_store(LoadStore(&simState)), branch_unit(&alu, &load_store, &simState)
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
void Simulator::decode()
{
	if (fetcher.state == DONE) {
		for (auto data : simState.register_file.fetch_buffer) {
			Instruction next = data.instruction;
			size_t nops = 0;
			nops = std::max(load_store.findHazard(next), alu.findHazard(next));
			nops = std::max(nops, branch_unit.input.findHazard(next));
			nops = std::max(nops, instruction_buffer.findHazard(next));
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
int Simulator::execute(Instruction current_instruction) {

	if (breakpoints.find(current_instruction.location) != breakpoints.end()) {
		int a = 3;
		std::cout << "";
	}

	if (current_instruction.opcode.settings.unit == SKIP) {
		std::cout << current_instruction.opcode.settings.name << std::endl;
		return 0;
	}

	if (current_instruction.opcode.settings.unit == LDSTR) {
		load_store.input.push(current_instruction);
		state = READY;
		return 0;
	}
	if (current_instruction.opcode.settings.unit == BRANCH) {
		branch_unit.input.push(current_instruction);
		state = READY;
		return 0;
	}
	if (current_instruction.opcode.settings.unit == MATH) {
		alu.input->push(current_instruction);
		state = READY;
	}
	return 0;
};

int Simulator::tick() {
	//If halted, just stop
	if (branch_unit.halt) {
		return HALT_PROGRAM;
	}
	//If stalling, keep attempting same instruction

		fetch();
		decode();
		if (!instruction_buffer.isEmpty()) {
			stall_instruction = instruction_buffer.pop();
			if (execute(stall_instruction) == HALT_PROGRAM) {
				return HALT_PROGRAM;
			}
		}
	return 0;
}

void Simulator::flush() {
	fetcher.state = READY;
	alu.flush();
	state = READY;
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
		simState.memory.tick();
		load_store.tick();
		alu.tick();
		writeback();

		if (debug) {
			print_state();
		}
	}
}

void Simulator::dump() {
	std::cout << std::endl;
	std::cout << "| TICKS | PC | STATE | MAR | MDR | CIR | ";
	std::string reg_header = "";
	std::string reg_contents = "";
	for (int i = 0; i < 16; i++) {
		reg_header += "R" + std::to_string(i) + " | ";
		std::string contents = "X";
		if (simState.register_file.gp[i].data >= -10000 && simState.register_file.gp[i].data <= 10000) {
			contents = std::to_string(simState.register_file.gp[i].data);
		}
		reg_contents += contents + " | ";
	}
	std::cout << reg_header;
	std::cout << std::endl;
	std::cout << "| " << ticks << " | " << simState.program_counter << " | " << state << " | ";
	std::cout << "X" << " | " << "X" << " | " << "X" << " | " << reg_contents;
	std::cout << std::endl;
}

void Simulator::print_state() {

	//std::cout << register_file.CIR.line << std::endl;
	//std::cout << "r3: " << register_file.gp[3].data << std::endl;
	//std::cout << "r0: " << register_file.gp[0].data << std::endl;
	//std::cout << "state: " << state;
	//std::cout << " PC: " << program_counter;
	//std::cout << " tick: " << ticks << std::endl;
}


