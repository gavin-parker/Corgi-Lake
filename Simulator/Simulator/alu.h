#pragma once
#include "instruction.h"
#include "register_file.h"
#include "component.h"
#include "register_file.h"
#include "buffer.h"
#include "simulator_state.h"
#include <memory>
class ALU : public Component
{
private:
	std::shared_ptr<Buffer<Instruction>> input;
	std::shared_ptr<Buffer<Instruction>> output;
	Data result;
	int result_location = 0;
	Instruction current_instruction;
	SimState *simState;
	RegisterFile *register_file;
public:
	bool result_ready = false;
	ALU(SimState *simState, std::shared_ptr<Buffer<Instruction>> input, std::shared_ptr<Buffer<Instruction>> output);
	~ALU();
	Data execute(Instruction instruction);
	int tick();
	void log();
	void write();
};

