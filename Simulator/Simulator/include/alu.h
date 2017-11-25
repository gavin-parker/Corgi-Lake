#pragma once
#include "instruction.h"
#include "register_file.h"
#include "component.h"
#include "register_file.h"
#include "buffer.h"
#include "result.h"
#include "simulator_state.h"
#include <memory>
class ALU : public Component
{

	SimState			*sim_state_;
	RegisterFile		*register_file_;
public:
	Result lastResult;
	Instruction current_instruction;
	std::deque<Result>	output;
	Buffer				input;
	bool result_ready = false;
	explicit ALU(SimState *sim_state);
	~ALU();
	uint64_t execute(Instruction instruction);
	int tick() override;
	const int pipeline_length = 3;
	void write();
	void flush(); //Stop executing current instruction and empty the buffer
	bool is_hazard(Instruction other);
};

