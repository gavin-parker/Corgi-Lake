
#include "../../include/alu.h"

ALU::ALU(SimState* simState, ReorderBuffer *reorder_buffer) :
        sim_state_(simState),
        reorder_buffer(reorder_buffer),
        reservation_station(ReservationStation(&simState->register_file, reorder_buffer))
{
	register_file_ = &(*simState).register_file;
}

ALU::~ALU()
= default;

int ALU::execute(Instruction instruction) {
	const int r1 = reservation_station.args[1];
	const int r2 = reservation_station.args[2];
	int v;
	auto result = 0;
	switch (instruction.opcode.op) {
	case IADD:
		result = r1 + r2;
		state = EXECUTING;
		break;
	case IADDI:
	{
		v = instruction.operands[2];
		result = r1 + v;
		state = EXECUTING;
		break;
	}
	case IMUL:
		result = r1 * r2;
		state = EXECUTING;
		break;
	case IMULI:
		v = instruction.operands[2];
		result = r1 * v;
		state = EXECUTING;
		break;
	case ICMP:
	{
        result = 0;
        if (r1 - r2 < 0) {
			result = -1;
		}else if (r1 - r2 > 0) {
			result = 1;
		}
		state = READY;
		break;
	}
	case ISUB:
		result = r1 - r2;
		state = EXECUTING;
		break;
	default: ;
	}
	if (instruction.opcode.op != NOP) {
		sim_state_->instructions_executed++;
	}
	return result;
}

int ALU::tick() {
	if (result_ready) {
		reservation_station.complete(lastResult);
		reorder_buffer->update(lastResult);
		result_ready = false;
	}
	switch (state) {
	case READY:
		if (reservation_station.is_ready()) {
			current_instruction = reservation_station.current_instruction;
            if (current_instruction.opcode.op == NOP) {
                register_file_->print(current_instruction);
                return 0;
            }
            state = EXECUTING;
            wait_cycles = current_instruction.opcode.settings.ticks;
        }
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			/*Hold result in lastResult to simulate writeback happening on NEXT tick!!*/
			register_file_->print(current_instruction);
			lastResult = Result(current_instruction, static_cast<uint64_t>(execute(current_instruction)));
			result_ready = true;
			state = READY;
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

void ALU::flush()
{
	state = READY;
}
