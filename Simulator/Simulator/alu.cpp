#include "stdafx.h"
#include "alu.h"
#include "result.h"
#include <iostream>


ALU::ALU(SimState *simState, std::shared_ptr<Buffer<Instruction>> input, std::shared_ptr<Buffer<Result>> output) : simState(simState), input(input), output(output)
{
	register_file = &(*simState).register_file;
}

ALU::~ALU()
{
}


uint64_t ALU::execute(Instruction instruction) {
	uint64_t r0 = instruction.operands[0];
	uint64_t r1 = instruction.operands[1];
	uint64_t r2 = instruction.operands[2];
	uint64_t v;
	uint64_t result;
	switch (instruction.opcode) {
	case IADD:
		result = register_file->gp[r1].data + register_file->gp[r2].data;
		state = EXECUTING;
		break;
	case IADDI:
	{
		v = r2;
		result = register_file->gp[r1].data + v;
		state = EXECUTING;
		break;
	}
	case IMUL:
		result = register_file->gp[r1].data * register_file->gp[r2].data;
		state = EXECUTING;
		break;
	case IMULI:
		v = r2;
		result = register_file->gp[r1].data * v;
		state = EXECUTING;
		break;
	case ICMP:
	{
		uint64_t ans = 0;
		if (register_file->gp[r1].data - register_file->gp[r2].data < 0) {
			result = -1;
		}
		else if (register_file->gp[r1].data - register_file->gp[r2].data > 0) {
			result = 1;
		}
		state = READY;
		break;
	}
	}
	simState->instructions_executed++;
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
			if (current_instruction.opcode != NOP && !containsHazard(*simState, current_instruction)) {
				output->push(Result(current_instruction, execute(current_instruction)));
			}
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

void ALU::write()
{
	if (!output->isEmpty()) {
		Result res = output->pop();
		register_file->gp[res.instruction.operands[0]].data = res.result;
	}
}
