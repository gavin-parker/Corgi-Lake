#pragma once
#include "component.h"
#include "memory.h"
#include "register_file.h"
#include "simulator_state.h"
class Fetcher : public Component
{
private:
	Memory *memory;
	RegisterFile *register_file;
	SimState *simState;
public:
	Fetcher(SimState *simState);
	~Fetcher();
	int tick();
};

