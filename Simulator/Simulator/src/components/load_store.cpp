
#include "../../include/load_store.h"

int LoadStore::execute(Instruction instruction)
{
	const int r0 = reservation_station.args[0];
	const int r1 = reservation_station.args[1];
	const int r2 = reservation_station.args[2];
	int v;
	int result = 0;
	switch (current_instruction.opcode.op)
	{
	case LD:
		if (memory->state != EXECUTING) {
			v = instruction.operands[2];
			result = (*memory)[r1 + v].data;
		}
		break;
	case LDI:
		if (memory->state != EXECUTING) {
			v = instruction.operands[1];
			result = v;
		}
		break;
	case STR:
		if (memory->state != EXECUTING) {
			result = r2;
            lastTarget = r0 + r1;
		}
		break;
	case STRI:
		if (memory->state != EXECUTING) {
			v = instruction.operands[2];
			result = r0;
            lastTarget = v;
        }
		break;
		default:
			break;
	}
	simState->instructions_executed++;
	return result;
}

LoadStore::LoadStore(SimState *simState, ReorderBuffer *reorder_buffer) :	register_file(&(*simState).register_file),
																			memory(&(*simState).memory),
																			simState(simState),
																			reservation_station(ReservationStation(register_file, reorder_buffer)),
																			reorder_buffer(reorder_buffer)
{
	//register_file->reservation_stations.push_back(&reservation_station);
}

LoadStore::~LoadStore()
= default;

int LoadStore::tick() {
	if (result_ready) {
		reorder_buffer->update(lastResult, true, lastTarget);
		reservation_station.complete(lastResult);
		result_ready = false;
	}
	switch (state) {
	case READY:
		if (reservation_station.is_ready()) {
			current_instruction = reservation_station.current_instruction;
            if (current_instruction.opcode.op == NOP) {
                register_file->print(current_instruction);
                return 0;
            }
            state = EXECUTING;
            wait_cycles = current_instruction.opcode.settings.ticks;
        }
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			auto result = execute(current_instruction);
			lastResult = Result(current_instruction, result);
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

void LoadStore::flush()
{
	state = READY;
}
