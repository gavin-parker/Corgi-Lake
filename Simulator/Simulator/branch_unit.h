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
	ReservationStation input;
	Instruction current_instruction;
public:
	BranchUnit(Bank<ALU> *alus, LoadStore *load_store, RegisterFile *register_file, uint64_t *program_counter);
	~BranchUnit();
	bool stall = false;
	int tick();
	bool halt = false;
	bool flush = false;
};

