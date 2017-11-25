#include "../../include/stdafx.h"
#include "../../include/branch_unit.h"
#include <iostream>

static void print_operand(int64_t operand, RegisterFile *register_file) {
	std::cout << " r" << operand;
	std::cout << "(" << register_file->gp[operand].data << ")";
}

BranchUnit::BranchUnit(Bank<ALU>* alus, LoadStore * load_store, BranchPredictor *branch_predictor, SimState *simState) : alus(alus), load_store(load_store), branch_predictor(branch_predictor), program_counter(&(*simState).program_counter), register_file(&(*simState).register_file), simState(simState)
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
	//bool prediction = branch_predictor->getPrediction(current_instruction);
	bool branched = true;
	switch (current_instruction.opcode.op)
	{
	case BRA:
		(*program_counter) = r0;
		state = READY;
		break;
	case JUM:
		(*program_counter) = current_instruction.location + r0;
		state = READY;
		break;
	case BLT:
		if (register_file->gp[r0].data < register_file->gp[r1].data) {
			(*program_counter) = current_instruction.location + r2;
		}
		else {
			(*program_counter) = current_instruction.location + 1;
			branched = false;
		}
		state = READY;
		break;
	case HALTEZ:
		if (register_file->gp[r0].data == 0) {
			halt = true;
		}
		else {
			(*program_counter) = current_instruction.location + 1;
			branched = false;
		}
		state = READY;
		break;
	case HALTEQ:
		if (register_file->gp[r0].data == r1) {
			halt = true;
		}
		else {
			branched = false;
			(*program_counter) = current_instruction.location + 1;
		}
		state = READY;
		break;
	}
	simState->instructions_executed++;
    register_file->stall = false;
//	if (branched != prediction) {
//		simState->flush = true;
//	}
}

int BranchUnit::tick()
{
	switch (state) {
	case READY:
		if (!input.isEmpty()) {
            current_instruction = input.pop();
            if (current_instruction.opcode.op == NOP) {
                return 0;
            }
            state = EXECUTING;
            wait_cycles = current_instruction.opcode.settings.ticks;
        }
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			register_file->print(current_instruction);
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

void BranchUnit::flush()
{
	input.flush();
	state = READY;
}

bool BranchUnit::isHazard(Instruction other)
{
	return false;
}
