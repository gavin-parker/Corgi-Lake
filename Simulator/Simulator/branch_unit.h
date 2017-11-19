#pragma once
#include "component.h"
#include "instruction.h"
#include "bank.h"
#include "load_store.h"
#include "branch_predictor.h"
class BranchUnit :
	public Component
{
private:
	Bank<ALU> *alus;
	LoadStore *load_store;
	RegisterFile *register_file;
	void execute(Instruction current_instruction);
	uint64_t *program_counter;
	uint64_t pc_at_branch;
	Instruction current_instruction;
	SimState *simState;
	BranchPredictor *branch_predictor;
public:
	Buffer input;
	BranchUnit(Bank<ALU> *alus, LoadStore *load_store, BranchPredictor *branch_predictor, SimState *simState);
	~BranchUnit();
	int tick();
	const int pipeline_length = 2;
	bool halt = false;
	void flush();
};

