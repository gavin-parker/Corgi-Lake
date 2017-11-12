#pragma once
#include "component.h"
#include "instruction.h"
#include "buffer.h"
#include "register_file.h"
#include "simulator_state.h"
#include "memory.h"
#include <memory>
class LoadStore : public Component
{
private:
	Instruction current_instruction;
	void execute(Instruction instruction);
	Memory *memory;
	RegisterFile *register_file;
	SimState *simState;
	Data result;
	int result_location = 0;
	bool result_ready = false;
public:
	Buffer<Instruction> input;
	LoadStore(SimState *simState);
	~LoadStore();
	int tick();
	void write();
	bool flushed();
};

