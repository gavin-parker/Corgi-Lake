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
		register_file->MDR = (*memory)[register_file->MAR];
		state = DONE;
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