#include "stdafx.h"
#include "load_store.h"



static void print_operand(int64_t operand, RegisterFile *register_file) {
	std::cout << " r" << operand;
	std::cout << "(" << register_file->gp[operand].data << ")";
}

uint64_t LoadStore::execute(Instruction instruction)
{
	int64_t r0 = current_instruction.operands[0];
	int64_t r1 = current_instruction.operands[1];
	int64_t r2 = current_instruction.operands[2];
	uint64_t v;
	uint64_t result;
	std::cout << opcode_string(instruction.opcode) << " ";
	switch (current_instruction.opcode)
	{
	case LD:
		if (memory->state != EXECUTING) {
			print_operand(r0, register_file);
			print_operand(r1, register_file);
			std::cout << " " << r2;
			result = (*memory)[register_file->gp[r1].data + r2].data;
			std::cout << " : " << (*memory)[register_file->gp[r1].data + r2].data;
		}
		break;
	case LDI:
		if (memory->state != EXECUTING) {
			std::cout << "r" << r0 << " " << r1;
			result = r1;
		}
		break;
	case STR:
		if (memory->state != EXECUTING) {
			std::cout << register_file->gp[r0].data << " " << register_file->gp[r1].data << " " << register_file->gp[r2].data;
			(*memory)[register_file->gp[r0].data + register_file->gp[r1].data] = register_file->gp[r2];
		}
		break;	
	case STRI:
		if (memory->state != EXECUTING) {
			std::cout << r1 << " " << register_file->gp[r0].data;
			v = r1;
			(*memory)[v] = register_file->gp[r0];
		}
		break;
	}
	if (memory->state != EXECUTING) {
		simState->instructions_executed++;
		std::cout << std::endl;
	}
	return result;
}

LoadStore::LoadStore(SimState *simState) : register_file(&(*simState).register_file), memory(&(*simState).memory), simState(simState)
{
	simState->output_buffers.push_back(output);
}

LoadStore::~LoadStore()
{
}

int LoadStore::tick() {
	if (result_ready) {
		output.push(lastResult);
		result_ready = false;
	}
	switch (state) {
	case READY:
		if (!input.isEmpty()) {
			current_instruction = input.pop();
			state = EXECUTING;
			wait_cycles = 1;
		}
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {

			if (current_instruction.opcode != NOP) {
				uint64_t result = execute(current_instruction);
				lastResult = Result(current_instruction, result);
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
	return 0;
}

void LoadStore::write()
{
	if (!output.isEmpty()) {
		Result result = output.pop();
		register_file->gp[result.instruction.operands[0]].data = result.result;
	}
}

bool LoadStore::flushed()
{
	return state != EXECUTING && input.isEmpty() && output.isEmpty() && !result_ready;
}

size_t LoadStore::findHazard(Instruction other)
{
	if (input.findHazard(other)) {
		return input.findHazard(other);
	}
	if (current_instruction.isHazard(other)) {
		return 2;
	}
	return output.findHazard(other);

}
