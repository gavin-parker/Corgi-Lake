#include "stdafx.h"
#include "load_store.h"


void LoadStore::execute(Instruction instruction)
{
	int64_t r0 = current_instruction.operands[0];
	int64_t r1 = current_instruction.operands[1];
	int64_t r2 = current_instruction.operands[2];
	uint64_t v;
	switch (current_instruction.opcode)
	{
	case LD:
		if (memory->state != EXECUTING) {
			result.data = (*memory)[register_file->gp[r1].data + r2].data;
			state = WAIT_FOR_MEM;
		}
		break;
	case LDI:
		if (memory->state != EXECUTING) {
			result.data = r1;
			state = WAIT_FOR_MEM;
		}
		break;
	case STR:
		if (memory->state != EXECUTING) {
			(*memory)[register_file->gp[r0].data + register_file->gp[r1].data] = register_file->gp[r2];
			state = WAIT_FOR_MEM;
		}
		break;
	case STRI:
		if (memory->state != EXECUTING) {
			v = r1;
			(*memory)[v] = register_file->gp[r0];
			state = WAIT_FOR_MEM;
		}
		break;
	}
	if (memory->state != EXECUTING) {
		simState->instructions_executed++;
	}
}

LoadStore::LoadStore(SimState *simState) : register_file(&(*simState).register_file), memory(&(*simState).memory), simState(simState)
{
}

LoadStore::~LoadStore()
{
}
int LoadStore::tick() {
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
			execute(current_instruction);
			result_location = current_instruction.operands[0];
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
	return 0;
}

void LoadStore::write()
{
	if (result_ready) {
		register_file->gp[result_location] = result;
		result_ready = false;
	}
}

bool LoadStore::flushed()
{
	return state != EXECUTING && input.isEmpty() && !result_ready;
}
