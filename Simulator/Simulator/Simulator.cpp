// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simulator.h"
#include <string>
#include <iostream>

Simulator::Simulator(std::vector<Data> boot_disk) : memory(boot_disk), alu(&register_file), fetcher(&memory, &register_file)
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
		if (alu.state == DONE && memory.state == DONE) {
			program_counter = r0;
			state = READY;
			flush();
		}
		break;
	case JUM:
		if (alu.state == DONE && memory.state == DONE) {
			program_counter += r0;
			state = READY;
			flush();
		}
		break;
	case BLT:
		if (alu.state == DONE && memory.state == DONE) {
			if (register_file.gp[r0].data < register_file.gp[r1].data) {
				program_counter += r2;
			}
			state = READY;
			flush();
		}
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
		if (memory.state != EXECUTING) {
			register_file.gp[r0].data = memory[register_file.gp[r1].data + r2].data;
			state = WAIT_FOR_MEM;
		}
		break;
	case LDI:
		if (memory.state != EXECUTING) {
			register_file.gp[r0].data = r1;
			state = WAIT_FOR_MEM;
		}
		break;
	case STR:
		if (memory.state != EXECUTING) {
			memory[register_file.gp[r0].data + register_file.gp[r1].data] = register_file.gp[r2];
			state = WAIT_FOR_MEM;
		}
		break;
	case STRI:
		if (memory.state != EXECUTING) {
			v = r1;
			memory[v] = register_file.gp[r0];
			state = WAIT_FOR_MEM;
		}
		break;
	case HALTEZ:
		if (register_file.gp[r0].data == 0) {
			return HALT_PROGRAM;
		}
		break;
	case HALTEQ:
		if (register_file.gp[r0].data == r1) {
			return HALT_PROGRAM;
		}
		break;
	default:
		if (alu.state == DONE) {
			alu.state = READY;
		}
		alu.reservation_station.push(current_instruction);
		state = READY;
		return 0;
	}
	
	return 0;
};

int Simulator::tick() {

	if (fetcher.state == READY) {
		register_file.MAR = program_counter;
		fetcher.state = EXECUTING;
	}
	//fetch
	if (fetcher.state == DONE) {
		register_file.CIR = register_file.MDR;
		state = READY;
		program_counter++;
		fetcher.state = READY;
	}
	//execute
	if (state == READY) {
		if (execute() == HALT_PROGRAM) {
			return HALT_PROGRAM;
		}
	}
	else if (state == WAIT_FOR_ALU) {
		if (alu.state == DONE) {
			state = READY;
		}
	}
	else if (state == WAIT_FOR_MEM) {
		if (memory.state == DONE) {
			state = READY;
		}
	}

	//writeback

	return 0;
}

void Simulator::flush() {
	fetcher.state = READY;
	alu.state = DONE;
	memory.state = DONE;
	state = READY;
}
void Simulator::simulate() {
	state = READY;
	fetcher.state = READY;
	while (true) {
		int err = 0;
		ticks++;
		err = tick();
		if (err == HALT_PROGRAM)
		{
			return;
		}
		fetcher.tick();
		memory.tick();
		alu.tick();
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

	std::cout << register_file.CIR.line << std::endl;
	//std::cout << "r3: " << register_file.gp[3].data << std::endl;
	//std::cout << "r0: " << register_file.gp[0].data << std::endl;
	//std::cout << "state: " << state;
	//std::cout << " PC: " << program_counter;
	//std::cout << " tick: " << ticks << std::endl;
}


