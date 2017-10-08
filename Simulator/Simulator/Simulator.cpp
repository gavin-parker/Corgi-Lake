// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simulator.h"
#include <string>
#include <iostream>

Simulator::Simulator(std::vector<Data> boot_disk) : memory(boot_disk), alu(&register_file)
{
}

Simulator::~Simulator()
{
}

void Simulator::fetch() {
	register_file.MDR = memory[register_file.MAR];
};

//mega code smell
int Simulator::execute() {
	Instruction current_instruction = register_file.CIR.instruction;
	int64_t r0 = current_instruction.operands[0];
	int64_t r1 = current_instruction.operands[1];
	int64_t r2 = current_instruction.operands[2];
	uint64_t v;
	switch (current_instruction.opcode)
	{
	case BRA:
		program_counter = r0;
		state = READY;
		break;
	case JUM:
		program_counter += r0;
		state = READY;
		break;
	case BLT:
		if (register_file.gp[r0].data < register_file.gp[r1].data) {
			program_counter += r2;
		}
		state = READY;
		break;
	case ICMP:
	{
		uint64_t ans = 0;
		if (register_file.gp[r1].data - register_file.gp[r2].data < 0) {
			ans = -1;
		}
		else if (register_file.gp[r1].data - register_file.gp[r2].data > 0) {
			ans = 1;
		}
		register_file.gp[r0].data = ans;
		state = READY;
		break;
	}
	case LD:
		register_file.gp[r0].data = memory[register_file.gp[r1].data + r2].data;
		state = WAIT_FOR_MEM;
		break;
	case LDI:
		register_file.gp[r0].data = r1;
		state = WAIT_FOR_MEM;
		break;
	case STR:
		memory[register_file.gp[r0].data + register_file.gp[r1].data] = register_file.gp[r2];
		state = WAIT_FOR_MEM;
		break;
	case STRI:
		v = r1; 
		memory[v] = register_file.gp[r0];
		state = WAIT_FOR_MEM;
		break;
	case HALTEZ:
		if (register_file.gp[r0].data == 0) {
			return HALT_PROGRAM;
		}
		break;
	default:
		alu.state = READY;
		state = WAIT_FOR_ALU;
		return 0;
	}
	
	return 0;
};

void Simulator::tick() {
	switch (state) {
	case READY:
		if (alu.state != DONE) { //only continue if ALU has finished
			break;
		}
		register_file.MAR = program_counter;
		wait_cycles = 1;
		fetch();
		state = FETCHING_INSTRUCTION; //Wait for instruction to be fetched
		break;
	case FETCHING_INSTRUCTION:
		if (memory.state == DONE) {
			register_file.CIR = register_file.MDR;
			program_counter++;
			wait_cycles = 1;
			state = EXECUTING;
		}
		break;
	case WAIT_FOR_MEM:
		if (memory.state == DONE) {
			state = READY;
		}
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			if (execute() == HALT_PROGRAM) {
				throw std::runtime_error("Program halted!");
			}
		}
		else {
			wait_cycles--;
		}
		break;
	case WAIT_FOR_ALU:
		if (alu.state == DONE) {
			state = READY;
		}
		break;
	case DONE:
		break;
	}
}

void Simulator::simulate() {
	state = READY;
	while (true) {
		try {
			ticks++;
			tick();
			memory.tick();
			alu.tick();
			if (debug) {
				print_state();
			}
		}
		catch (std::runtime_error e) {
			dump();
			return;
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
	std::cout << "r3: " << register_file.gp[3].data << std::endl;
	std::cout << "r0: " << register_file.gp[0].data << std::endl;
	//std::cout << "state: " << state;
	//std::cout << " PC: " << program_counter;
	//std::cout << " tick: " << ticks << std::endl;
}


