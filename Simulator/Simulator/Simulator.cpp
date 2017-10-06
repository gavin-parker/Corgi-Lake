// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simulator.h"
#include <iostream>

Simulator::Simulator(std::vector<Data> boot_disk) : memory(boot_disk)
{
}

Simulator::~Simulator()
{
}

void Simulator::fetch() {
	register_file.MAR = program_counter;
	register_file.MDR = memory[register_file.MAR];
	std::cout << "fetched " << register_file.MDR.instruction.opcode << std::endl;
	register_file.CIR = register_file.MDR;
	program_counter++;
};

void Simulator::decode() {


};
void Simulator::execute() {
	Instruction current_instruction = register_file.CIR.instruction;
	uint64_t r0 = current_instruction.operands[0];
	uint64_t r1 = current_instruction.operands[1];
	uint64_t r2 = current_instruction.operands[2];
	switch (current_instruction.opcode)
	{
	case BRA:
		program_counter = r0;
		return;
	case JUM:
		program_counter += r0;
		return;
	case BLT:
		std::cout << "reached BLT!";
		if (register_file.gp[r0].data < register_file.gp[r1].data) {
			program_counter += r0;
		}
		return;
	case IADD:

		register_file.gp[r0].data = register_file.gp[r1].data + register_file.gp[r2].data;
		return;
	case IADDI:
	{
		uint64_t v = r2;
		register_file.gp[r0].data = register_file.gp[r1].data + v;
		return;
	}
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
		return;
	}
	case LD:
		register_file.gp[r0].data = memory[register_file.gp[r1].data + r2].data;
		return;
	case LDI:
		register_file.gp[r0].data = r1;
		return;
	default:
		break;
	}
};

void Simulator::simulate() {
	while (true) {
		fetch();
		decode();
		execute();
	}
}


