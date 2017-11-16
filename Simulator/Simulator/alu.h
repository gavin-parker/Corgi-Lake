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
private:
	std::shared_ptr<Buffer<Instruction>> input;
	std::shared_ptr<Buffer<Result>> output;
	SimState *simState;
	RegisterFile *register_file;
public:
	Result lastResult;
	Instruction current_instruction;
	bool result_ready = false;
	ALU(SimState *simState, std::shared_ptr<Buffer<Instruction>> input, std::shared_ptr<Buffer<Result>> output);
	~ALU();
	uint64_t execute(Instruction instruction);
	int tick();
	void log();
	void write();
};

