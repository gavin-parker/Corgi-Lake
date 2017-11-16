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
	Buffer<Result> output;
	Buffer<Instruction> input;
	LoadStore(SimState *simState);
	~LoadStore();
	int tick();
	void write();
	bool flushed();
	size_t findHazard(Instruction other);
};

