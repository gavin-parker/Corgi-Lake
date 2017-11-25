#pragma once
#include "component.h"
#include "memory.h"
#include "register_file.h"
#include "simulator_state.h"
#include "branch_predictor.h"
class Fetcher : public Component
{
private:
	Memory *memory;
	RegisterFile *register_file;
	SimState *simState;
	BranchPredictor *branch_predictor;
public:
	Fetcher(SimState *simState, BranchPredictor *branch_predictor);
	~Fetcher();
	int tick();
};

