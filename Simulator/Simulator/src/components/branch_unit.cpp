#include "../../include/stdafx.h"
#include "../../include/branch_unit.h"
#include <iostream>
#include <assert.h>

static void print_operand(const int64_t operand, RegisterFile *register_file) {
	std::cout << " r" << operand;
	std::cout << "(" << register_file->gp[operand].data << ")";
}

BranchUnit::BranchUnit(ALU* alu, LoadStore * load_store, BranchPredictor *branch_predictor, SimState *simState) : alu(alu), load_store(load_store), branch_predictor(branch_predictor), program_counter(&(*simState).program_counter), register_file(&(*simState).register_file), simState(simState)
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
	const bool prediction = branch_predictor->getPrediction(current_instruction);
	auto branched = true;
	auto target = current_instruction.location + 1;
	switch (current_instruction.opcode.op)
	{
	case BRA:
		target = r0;
		state = READY;
		break;
	case JUM:
		target = current_instruction.location + r0;
		state = READY;
		break;
	case BLT:
		if (register_file->gp[r0].data < register_file->gp[r1].data) {
			target = current_instruction.location + r2;
		}
		else {
			branched = false;
		}
		state = READY;
		break;
	case HALTEZ:
		if (register_file->gp[r0].data == 0) {
			halt = true;
		}
		else {
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
		}
		state = READY;
		break;
	default:
		std::cout << "oops";
	}
	simState->instructions_executed++;
    register_file->stall = false;
	/*
	 * If the branch was predicted, don't change the program counter
	 */
	if (prediction != branched) {
		(*program_counter) = target;
		simState->flush = true;
	}
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
