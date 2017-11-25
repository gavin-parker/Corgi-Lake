#include "../../include/stdafx.h"
#include "../../include/alu.h"
#include "../../include/result.h"
#include "../../include/instruction.h"
#include <iostream>
#include <algorithm>
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
	int result;
	switch (instruction.opcode.op) {
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
		else {
			result = 0;
		}

		state = READY;
		break;
	}
	case ISUB:
		result = register_file->gp[r1].data - register_file->gp[r2].data;
		state = EXECUTING;
		break;
    }
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
            if (current_instruction.opcode.op == NOP) {
                register_file->print(current_instruction);
                return 0;
            }
            state = EXECUTING;
            wait_cycles = current_instruction.opcode.settings.ticks;
        }
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			/*Hold result in lastResult to simulate writeback happening on NEXT tick!!*/
			register_file->print(current_instruction);
			lastResult = Result(current_instruction, execute(current_instruction));
			result_ready = true;

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
	while (!output->empty()) {
		Result res = output->front();
		output->pop_front();
		register_file->gp[res.instruction.operands[0]].data = res.result;
	}
}

void ALU::flush()
{
	state = READY;
	//input->flush();
	output->clear();
}

bool ALU::isHazard(Instruction other)
{
    return ((state == EXECUTING && current_instruction.isHazard(other))
     || (result_ready && lastResult.isHazard(other)));
}
