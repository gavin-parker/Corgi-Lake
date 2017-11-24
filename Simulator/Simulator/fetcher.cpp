#include "stdafx.h"
#include "fetcher.h"
#include <cassert>

Fetcher::Fetcher(SimState *simState, BranchPredictor *branch_predictor) : simState(simState), branch_predictor(branch_predictor)
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

		while (register_file->fetch_buffer.size() < 5) {
			if (simState->program_counter >= memory->size()) {
				break;
			}
			Data next = (*memory)[simState->program_counter];
			register_file->fetch_buffer.push_back(next);
			simState->program_counter++;
			Opcode opcode = next.instruction.opcode;
			assert(opcode.op != DATA);
			if (opcode.settings.unit == BRANCH ) {
				if (branch_predictor->predict(next.instruction)) {
					uint32_t target = 0;
					if (opcode.op == BLT) {
						target = next.instruction.location + next.instruction.operands[2];
					}
					else if(opcode.op ==  BRA){
						target = next.instruction.operands[0];
					}
					else {
						target = next.instruction.location - next.instruction.operands[0];
					}
					simState->program_counter = target;
				}
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