#pragma once
#include "component.h"
#include "instruction.h"
#include "bank.h"
#include "load_store.h"
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
public:
	Buffer input;
	BranchUnit(Bank<ALU> *alus, LoadStore *load_store, SimState *simState);
	~BranchUnit();
	int tick();
	const int pipeline_length = 2;
	bool halt = false;
};

