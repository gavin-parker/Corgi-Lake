#include "stdafx.h"
#include "branch_unit.h"
#include <iostream>

BranchUnit::BranchUnit(Bank<ALU>* alus, LoadStore * load_store, RegisterFile *register_file, uint64_t *program_counter) : alus(alus), load_store(load_store), program_counter(program_counter), register_file(register_file)
{
}

BranchUnit::~BranchUnit()
{
}

void BranchUnit::execute(Instruction current_instruction) {
	int64_t r0 = current_instruction.operands[0];
	int64_t r1 = current_instruction.operands[1];
	int64_t r2 = current_instruction.operands[2];
	uint64_t v;
	bool canBranch = load_store->flushed() && alus->flushed();
	switch (current_instruction.opcode)
	{
	case BRA:
		if (canBranch) {
			(*program_counter) = r0;
			stall = false;
			state = READY;
		}
		else {
			stall = true;
		}
		break;
	case JUM:
		if (canBranch) {
			(*program_counter) = current_instruction.location + r0;
			stall = false;
			state = READY;
		}
		else {
			stall = true;
		}
		break;
	case BLT:
		if (canBranch) {
			if (register_file->gp[r0].data < register_file->gp[r1].data) {
				(*program_counter) = current_instruction.location + r2;
			}
			stall = false;
			state = READY;
		}
		else {
			stall = true;
		}
		break;
	case HALTEZ:
		if (canBranch) {
			if (register_file->gp[r0].data == 0) {
				halt = true;
			}
			state = READY;
			stall = false;
		}
		else {
			stall = true;
		}
		break;
	case HALTEQ:
		if (canBranch) {
			if (register_file->gp[r0].data == r1) {
				halt = true;
			}
			stall = false;
			state = READY;
		}
		else {
			stall = true;
		}
		break;
	case NOP:
		state = READY;
		break;
	}
}

int BranchUnit::tick()
{
	switch (state) {
	case READY:
		if (!input.isEmpty()) {
			current_instruction = input.pop();
			pc_at_branch = (*program_counter);
			std::cout << "PC AT BRANCH:" << pc_at_branch << "\n";
			state = EXECUTING;
			wait_cycles = 1;
		}
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			execute(current_instruction);
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
