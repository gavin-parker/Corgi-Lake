#include "stdafx.h"
#include "alu.h"
#include "result.h"
#include "instruction.h"
#include <iostream>

static void print_operand(int64_t operand, RegisterFile *register_file) {
	std::cout << " r" << operand;
	std::cout << "(" << register_file->gp[operand].data << ")";
}

ALU::ALU(SimState *simState, std::shared_ptr<Buffer> input, std::shared_ptr<std::deque<Result>> output) : simState(simState), input(input), output(output)
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
	std::cout << opcode_string(instruction.opcode.op) << " ";
	print_operand(r0, register_file);
	switch (instruction.opcode.op) {
	case IADD:
		print_operand(r1, register_file);
		print_operand(r2, register_file);
		result = register_file->gp[r1].data + register_file->gp[r2].data;
		state = EXECUTING;
		break;
	case IADDI:
	{
		v = r2;
		result = register_file->gp[r1].data + v;
		print_operand(r1, register_file);
		std::cout << " " << v;
		state = EXECUTING;
		break;
	}
	case IMUL:
		result = register_file->gp[r1].data * register_file->gp[r2].data;
		std::cout << register_file->gp[r1].data << " " << register_file->gp[r2].data;
		state = EXECUTING;
		break;
	case IMULI:
		v = r2;
		result = register_file->gp[r1].data * v;
		std::cout << register_file->gp[r1].data << " " << v;
		state = EXECUTING;
		break;
	case ICMP:
	{
		uint64_t ans = 0;
		std::cout << register_file->gp[r1].data << " " << register_file->gp[r2].data;
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
	std::cout << std::endl;
	simState->instructions_executed++;
	return result;
}

int ALU::tick() {
	if (result_ready) {
		output->push_back(lastResult);
		result_ready = false;
	}
	switch (state) {
	case READY:
		if (!input->isEmpty()) {
			current_instruction = input->pop();
			state = EXECUTING;
			wait_cycles = current_instruction.opcode.settings.ticks;
		}
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			/*Hold result in lastResult to simulate writeback happening on NEXT tick!!*/
			if (current_instruction.opcode.op != NOP) {
				lastResult = Result(current_instruction, execute(current_instruction));
				result_ready = true;
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
	if (output->size() > 0) {
		Result res = output->front();
		output->pop_front();
		register_file->gp[res.instruction.operands[0]].data = res.result;
	}
}
