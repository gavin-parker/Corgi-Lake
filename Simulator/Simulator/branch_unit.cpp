#include "stdafx.h"
#include "branch_unit.h"
#include <iostream>

static void print_operand(int64_t operand, RegisterFile *register_file) {
	std::cout << " r" << operand;
	std::cout << "(" << register_file->gp[operand].data << ")";
}

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
	std::cout << opcode_string(current_instruction.opcode.op) << " ";
	switch (current_instruction.opcode.op)
	{
	case BRA:
		(*program_counter) = r0;
		state = READY;
		std::cout << r0;
		break;
	case JUM:
		(*program_counter) = current_instruction.location + r0;
		state = READY;
		std::cout << current_instruction.location + r0;
		break;
	case BLT:
		print_operand(r0, register_file);
		print_operand(r1, register_file);
		std::cout << r2;
		if (register_file->gp[r0].data < register_file->gp[r1].data) {
			(*program_counter) = current_instruction.location + r2;
		}
		state = READY;
		break;
	case HALTEZ:
		print_operand(r0, register_file);
		if (register_file->gp[r0].data == 0) {
			halt = true;
		}
		state = READY;
		break;
	case HALTEQ:
		print_operand(r0, register_file);
		std::cout << r1;
		if (register_file->gp[r0].data == r1) {
			halt = true;
		}
		state = READY;
		break;
	case NOP:
		state = READY;
		break;
	}
	simState->instructions_executed++;

	std::cout << std::endl;
	simState->stall = false;
}

int BranchUnit::tick()
{
	switch (state) {
	case READY:
		if (!input.isEmpty()) {
			current_instruction = input.pop();
			state = EXECUTING;
			wait_cycles = current_instruction.opcode.settings.ticks;
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
