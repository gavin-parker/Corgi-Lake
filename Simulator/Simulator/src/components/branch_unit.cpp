
#include "../../include/branch_unit.h"

BranchUnit::BranchUnit(ReorderBuffer *reorder_buffer, BranchPredictor *branch_predictor, SimState *simState) :
																			reorder_buffer_(reorder_buffer),
																			branch_predictor(branch_predictor),
																			program_counter(&(*simState).program_counter),
																			register_file(&(*simState).register_file),
																			simState(simState), reservation_station(ReservationStation(register_file, reorder_buffer))
{
}

BranchUnit::~BranchUnit()
{
}

void BranchUnit::execute(Instruction current_instruction) {

	const int r0 = reservation_station.args[0];
	const int r1 = reservation_station.args[1];
	const int r2 = reservation_station.args[2];
	const bool prediction = branch_predictor->getPrediction(current_instruction);
	auto branched = true;
	auto target = current_instruction.location + 1;
	switch (current_instruction.opcode.op)
	{
	case BRA:
		target = current_instruction.operands[0];
		state = READY;
		break;
	case JUM:
		target = current_instruction.location + current_instruction.operands[0];
		state = READY;
		break;
	case BLT:
		if (r0 < r1) {
			target = current_instruction.location + current_instruction.operands[2];
		}
		else {
			branched = false;
		}
		state = READY;
		break;
	case JLT:
		if (r0 < r1) {
			target = current_instruction.operands[2];
		}
		else {
			branched = false;
		}
		state = READY;
		break;
	case HALTEZ:
		if (r0 == 0) {
			halt = true;
		}
		else {
			branched = false;
		}
		state = READY;
		break;
	case HALTEQ:
		if (r0 == current_instruction.operands[1]) {
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
	Result res = Result(current_instruction, target);
	reservation_station.complete(res);
	if (prediction != branched) {
		reorder_buffer_->update(res, true);
		simState->mispredicts++;
	}else
	{
		reorder_buffer_->update(res, false);
	}
	branch_predictor->updatePrediction(current_instruction, branched);
}

int BranchUnit::tick()
{
	switch (state) {
	case READY:
		if (reservation_station.is_ready()) {
			current_instruction = reservation_station.current_instruction;
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

void BranchUnit::flush()
{
	state = READY;
}
