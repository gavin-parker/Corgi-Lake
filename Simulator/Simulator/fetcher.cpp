#include "stdafx.h"
#include "fetcher.h"


Fetcher::Fetcher(SimState *simState) : simState(simState)
{
	register_file = &(*simState).register_file;
	memory = &(*simState).memory;
}


Fetcher::~Fetcher()
{
}

int Fetcher::tick() {
	switch (state)
	{
	case READY:
		break;
	case EXECUTING:
		state = DONE;
		if (simState->stall) {
			break;
		}

		while (register_file->fetch_buffer.size() < 5) {
			if (simState->program_counter >= memory->size()) {
				break;
			}
			Data next = (*memory)[simState->program_counter];
			register_file->fetch_buffer.push_back(next);
			simState->program_counter++;
			if (next.instruction.opcode >= BRA && next.instruction.opcode <= HALTEQ) {
				simState->stall = true;
				break;
			}
		}
		break;
	case HOLD:
		break;
	case DONE:
		break;
	case WAIT_FOR_MEM:
		break;
	case WAIT_FOR_ALU:
		break;
	case FETCHING_INSTRUCTION:
		break;
	default:
		break;
	}
	return 0;
}