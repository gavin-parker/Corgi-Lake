#include "../../include/stdafx.h"
#include "../../include/load_store.h"
#include <algorithm>


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
	uint64_t result = 0;
	switch (current_instruction.opcode.op)
	{
	case LD:
		if (memory->state != EXECUTING) {

			result = (*memory)[register_file->gp[r1].data + r2].data;
		}
		break;
	case LDI:
		if (memory->state != EXECUTING) {
			result = r1;
		}
		break;
	case STR:
		if (memory->state != EXECUTING) {
			(*memory)[register_file->gp[r0].data + register_file->gp[r1].data] = register_file->gp[r2];
		}
		break;
	case STRI:
		if (memory->state != EXECUTING) {
			v = r1;
			(*memory)[v] = register_file->gp[r0];
		}
		break;
		default:
			break;
	}
	simState->instructions_executed++;
	return result;
}

LoadStore::LoadStore(SimState *simState) : register_file(&(*simState).register_file), memory(&(*simState).memory), simState(simState)
{
}

LoadStore::~LoadStore()
{
}

int LoadStore::tick() {
	if (result_ready) {
		output.push_back(lastResult);
		result_ready = false;
	}
	switch (state) {
	case READY:
		if (!input.isEmpty()) {
            current_instruction = input.pop();
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
			register_file->print(current_instruction);
			uint64_t result = execute(current_instruction);
			if (current_instruction.opcode.op != STR && current_instruction.opcode.op != STRI) {
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
	while (!output.empty()) {
		Result result = output.front();
		output.pop_front();
		register_file->gp[result.instruction.operands[0]].data = result.result;
	}
}

bool LoadStore::isHazard(Instruction other)
{
	return ((state == EXECUTING && current_instruction.isHazard(other))
            || (result_ready && lastResult.isHazard(other)));
}

void LoadStore::flush()
{
	//result_ready = false;
	state = READY;
	input.flush();
	//output.clear();
}
