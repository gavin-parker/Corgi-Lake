// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simulator.h"
#include <string>
#include <iostream>

Simulator::Simulator(std::vector<Data> boot_disk) : memory(boot_disk), alu(2, &register_file), fetcher(&memory, &register_file), load_store(LoadStore(&memory, &register_file)), branch_unit(&alu, &load_store, &register_file, &program_counter)
{
}

Simulator::~Simulator()
{
}

void Simulator::fetch() {
	if (fetcher.state == READY && !branch_unit.stall) {
		register_file.MAR = program_counter;
		fetcher.state = EXECUTING;
	}
}
void Simulator::decode()
{
	if (fetcher.state == DONE && !branch_unit.stall) {
		instruction_buffer.push(register_file.MDR.instruction);
		std::cout << register_file.MDR.line << std::endl;
		state = READY;
		program_counter++;
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

	if (current_instruction.opcode >= LD && current_instruction.opcode <= STRI) {
		load_store.input.push(current_instruction);
		state = READY;
		return 0;
	}
	if(current_instruction.opcode >= BRA && current_instruction.opcode <= HALTEQ)

	if (current_instruction.opcode != DATA) {
		alu.input->push(current_instruction);
		state = READY;
	}
	
	return 0;
};

int Simulator::tick() {
	if (branch_unit.halt) {
		return HALT_PROGRAM;
	}
	fetch();
	decode();
	if (state == READY) {
		if (!instruction_buffer.isEmpty()) {
			stall_instruction = instruction_buffer.pop();
			if (execute(stall_instruction) == HALT_PROGRAM) {
				return HALT_PROGRAM;
			}
		}
	}
	else if (branch_unit.stall) {
		if (execute(stall_instruction) == HALT_PROGRAM) {
			return HALT_PROGRAM;
		}
	}
	else if (state == WAIT_FOR_MEM) {
		if (memory.state == DONE) {
			state = READY;
		}
	}
	writeback();
	//writeback

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
		memory.tick();
		alu.tick();
		load_store.tick();
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
		if (register_file.gp[i].data >= -10000 && register_file.gp[i].data <= 10000) {
			contents = std::to_string(register_file.gp[i].data);
		}
		reg_contents += contents + " | ";
	}
	std::cout << reg_header;
	std::cout << std::endl;
	std::cout << "| " << ticks << " | " << program_counter << " | " << state << " | ";
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


