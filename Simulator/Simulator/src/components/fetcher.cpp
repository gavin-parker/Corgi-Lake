#include "../../include/stdafx.h"
#include "../../include/fetcher.h"
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
			if(simState->program_counter >= memory->size())
			{
				return 0;
			}
			if ( register_file->stall) {
				break;
			}
			Data next = (*memory)[simState->program_counter];
			register_file->fetch_buffer.push_back(next);
			Opcode opcode = next.instruction.opcode;
			if (opcode.settings.unit == BRANCH && branch_predictor->predict(next.instruction)) {
				int target = 0;
					if (opcode.op == BLT) {
						target = next.instruction.location + next.instruction.operands[2];
					}
					else if(opcode.op ==  BRA){
						target = next.instruction.operands[0];
					}
					else if(opcode.op == JUM){
						target = next.instruction.location + next.instruction.operands[0];
					}
					assert(target > 0);
					simState->program_counter = target;
			}
			else {
				simState->program_counter++;
			}
		}
		break;
	default:
		break;
	}
	return 0;
}