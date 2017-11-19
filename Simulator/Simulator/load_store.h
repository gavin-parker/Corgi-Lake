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
class LoadStore : public Component
{
private:
	Instruction current_instruction;
	uint64_t execute(Instruction instruction);
	Memory *memory;
	RegisterFile *register_file;
	SimState *simState;
public:
	bool result_ready = false;
	Result lastResult;
	std::deque<Result> output;
	Buffer input;
	LoadStore(SimState *simState);
	~LoadStore();
	int tick();
	void write();
	static const int pipeline_length = 3;
	size_t findHazard(Instruction other);
	void flush(); //Stop executing current instruction and empty the buffer
};

