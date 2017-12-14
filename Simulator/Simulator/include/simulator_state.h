#pragma once
#include "register_file.h"
#include "result.h"
#include "buffer.h"
#include "instruction.h"
#include <vector>
struct SimState {
	RegisterFile register_file;
	Memory memory;
	int program_counter = 0;
	int instructions_executed = 0;
	bool flush = false;
	int mispredicts = 0;
};
