#include "stdafx.h"
#include "instruction.h"


Instruction::Instruction()
{

}

Instruction::~Instruction()
{
}
/*
void Instruction::execute(uint64_t *program_counter, Memory memory) {
	switch (opcode)
	{
	case BRA:
		*program_counter = operands[0];
		return;
	case JUM:
		*program_counter += operands[0];
		return;
	case BLT:
		if (simulator.register_file.gp[operands[0]].data < simulator.register_file.gp[operands[1]].data) {
			simulator.program_counter += operands[0];
		}
		return;
	case IADD:
		uint64_t r0 = operands[0];
		uint64_t r1 = operands[1];
		uint64_t r2 = operands[2];
		simulator.register_file.gp[r0].data = simulator.register_file.gp[r1].data + simulator.register_file.gp[r2].data;
		return;
	case IADDI:
		uint64_t r0 = operands[0];
		uint64_t r1 = operands[1];
		uint64_t v = operands[2];
		simulator.register_file.gp[r0].data = simulator.register_file.gp[r1].data + v;
	case ICMP:
		int diff = simulator.register_file.gp[operands[1]].data - simulator.register_file.gp[operands[2]].data;
		uint64_t ans = 0;
		if (diff < 0) {
			ans = -1;
		}
		else if (diff > 0) {
			ans = 1;
		}
		simulator.register_file.gp[operands[0]].data = ans;
		return;
	case LD:
		simulator.register_file.gp[operands[0]].data = simulator.memory[simulator.register_file.gp[operands[1]].data + operands[2]].data;
		return;
	case LDI:
		simulator.register_file.gp[operands[0]].data = operands[1];
		return;
	default:
		break;
	}
}*/