#include "stdafx.h"
#include "alu.h"
#include <iostream>


ALU::ALU(RegisterFile* register_file, std::shared_ptr<ReservationStation> input, std::shared_ptr<ReservationStation> output) : register_file(register_file), input(input), output(output)
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
		state = EXECUTING;
		break;
	case IADDI:
	{
		v = r2;
		result.data = register_file->gp[r1].data + v;
		state = EXECUTING;
		break;
	}
	case IMUL:
		result.data = register_file->gp[r1].data * register_file->gp[r2].data;
		state = EXECUTING;
		break;
	case IMULI:
		v = r2;
		result.data = register_file->gp[r1].data * v;
		state = EXECUTING;
		break;
	}
	return result;
}
int ALU::tick() {
	switch (state) {
	case READY:
		if (!input->isEmpty()) {
			current_instruction = input->pop();
			state = EXECUTING;
			wait_cycles = 1;
		}
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			result = execute(current_instruction);
			register_file->gp[current_instruction.operands[0]] = result;
			state = READY;
		}
		else {
			wait_cycles--;
		}
		break;
	case DONE:
		break;
	}
	log();
	return 0;
}

void ALU::log()
{
	//std::cout << "ALU: " << current_instruction.line << std::endl;
}
