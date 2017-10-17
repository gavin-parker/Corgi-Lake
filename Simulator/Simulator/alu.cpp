#include "stdafx.h"
#include "alu.h"


ALU::ALU(RegisterFile *register_file) : register_file(register_file)
{
}


ALU::~ALU()
{
}

Data ALU::execute(Instruction instruction) {
	uint64_t r0 = instruction.operands[0];
	uint64_t r1 = instruction.operands[1];
	uint64_t r2 = instruction.operands[2];
	uint64_t v;

	switch (instruction.opcode) {
	case IADD:
		result.data = register_file->gp[r1].data + register_file->gp[r2].data;
		wait_cycles = 1;
		state = DONE;
		register_file->gp[current_instruction.operands[0]] = result;
		break;
	case IADDI:
	{
		v = r2;
		result.data = register_file->gp[r1].data + v;
		wait_cycles = 1;
		state = DONE;
		register_file->gp[current_instruction.operands[0]] = result;
		break;
	}
	case IMUL:
		result.data = register_file->gp[r1].data * register_file->gp[r2].data;
		wait_cycles = 3;
		state = EXECUTING;
		break;
	case IMULI:
		v = r2;
		result.data = register_file->gp[r1].data * v;
		wait_cycles = 3;
		state = EXECUTING;
		break;
	}
	return result;
}
int ALU::tick() {
	switch (state) {
	case READY:
		if (!reservation_station.isEmpty()) {
			current_instruction = reservation_station.pop();
			result = execute(current_instruction);
		}
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			register_file->gp[current_instruction.operands[0]] = result;
			state = DONE;
		}
		else {
			wait_cycles--;
		}
		break;
	case DONE:
		break;
	}
	return 0;
}
