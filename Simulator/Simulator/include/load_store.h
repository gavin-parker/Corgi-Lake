#pragma once
#include "component.h"
#include "instruction.h"
#include "buffer.h"
#include "register_file.h"
#include "simulator_state.h"
#include "memory.h"
#include "result.h"
#include "buffer.h"
#include <memory>
#include "../reservation_station.h"
#include "../reorder_buffer.h"

class LoadStore : public Component
{
private:
	Instruction current_instruction;
	uint64_t execute(Instruction instruction);
	Memory *memory;
	RegisterFile *register_file;
	SimState *simState;
public:
	ReservationStation reservation_station;
	bool result_ready = false;
	Result lastResult;
	ReorderBuffer *reorder_buffer;
	LoadStore(SimState *simState, ReorderBuffer *reorder_buffer);
	~LoadStore();
	int tick();
	static const int pipeline_length = 3;
	bool isHazard(Instruction other);
	void flush(); //Stop executing current instruction and empty the buffer
};

