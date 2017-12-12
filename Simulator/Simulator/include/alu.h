#pragma once
#include "instruction.h"
#include "register_file.h"
#include "component.h"
#include "register_file.h"
#include "buffer.h"
#include "result.h"
#include "simulator_state.h"
#include <memory>
#include "../reservation_station.h"
#include "../reorder_buffer.h"

class ALU : public Component
{

	SimState			*sim_state_;
	RegisterFile		*register_file_;
	
public:
	Result lastResult;
	Instruction current_instruction;
	ReservationStation reservation_station;
	ReorderBuffer *reorder_buffer;
	bool result_ready = false;
	ALU(SimState *sim_state, ReorderBuffer *reorder_buffer);
	~ALU();
	uint64_t execute(Instruction instruction);
	int tick() override;
	const int pipeline_length = 3;
	void flush(); //Stop executing current instruction and empty the buffer
	bool is_hazard(Instruction other);
};

