#include "stdafx.h"
#include "branch_unit.h"
#include <iostream>

BranchUnit::BranchUnit(Bank<ALU>* alus, LoadStore * load_store, SimState *simState) : alus(alus), load_store(load_store), program_counter(&(*simState).program_counter), register_file(&(*simState).register_file), simState(simState)
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
	if (canBranch) {
		std::cout << opcode_string(current_instruction.opcode) << " ";
	}
	else {
		std::cout << "can't branch" << std::endl;
	}
	switch (current_instruction.opcode)
	{
	case BRA:
		if (canBranch) {
			(*program_counter) = r0;
			stall = false;
			state = READY;
			simState->instructions_executed++;
			std::cout << r0;
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
			simState->instructions_executed++;
			std::cout << current_instruction.location + r0;
		}
		else {
			stall = true;
		}
		break;
	case BLT:
		if (canBranch) {
			std::cout << register_file->gp[r0].data << " " << register_file->gp[r1].data << " " << current_instruction.location + r2;
			if (register_file->gp[r0].data < register_file->gp[r1].data) {
				(*program_counter) = current_instruction.location + r2;
			}
			stall = false;
			state = READY;
			simState->instructions_executed++;
		}
		else {
			stall = true;
		}
		break;
	case HALTEZ:
		if (canBranch) {
			std::cout << register_file->gp[r0].data;
			if (register_file->gp[r0].data == 0) {
				halt = true;
			}
			state = READY;
			stall = false;
			simState->instructions_executed++;
		}
		else {
			stall = true;
		}
		break;
	case HALTEQ:
		if (canBranch) {
			std::cout << register_file->gp[r0].data << " " << r1;
			if (register_file->gp[r0].data == r1) {
				halt = true;
			}
			stall = false;
			state = READY;
			simState->instructions_executed++;
		}
		else {
			stall = true;
		}
		break;
	case NOP:
		state = READY;
		break;
	}
	if (canBranch) {
		std::cout << std::endl;
	}
}

int BranchUnit::tick()
{
	switch (state) {
	case READY:
		if (!input.isEmpty()) {
			current_instruction = input.pop();
			pc_at_branch = (*program_counter);
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
