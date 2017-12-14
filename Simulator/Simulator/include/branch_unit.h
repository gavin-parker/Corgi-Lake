#pragma once
#include "component.h"
#include "instruction.h"
#include "alu.h"
#include "load_store.h"
#include "branch_predictor.h"
class BranchUnit :
	public Component
{
private:
	RegisterFile *register_file;
	void execute(Instruction current_instruction);
	int *program_counter;
	Instruction current_instruction;
	SimState *simState;
	BranchPredictor *branch_predictor;
	ReorderBuffer *reorder_buffer_;
public:
	ReservationStation reservation_station;
	BranchUnit( ReorderBuffer *reorder_buffer, BranchPredictor *branch_predictor, SimState *simState);
	~BranchUnit();
	int tick();
	bool halt = false;
	void flush();
};

