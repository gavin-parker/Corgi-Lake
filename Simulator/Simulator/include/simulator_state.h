#pragma once
#include "register_file.h"
#include "result.h"
#include "buffer.h"
#include "instruction.h"
#include <vector>
#include "../reorder_buffer.h"

struct SimState {
	RegisterFile register_file;
	Memory memory;
	uint64_t program_counter = 0;
	int instructions_executed = 0;
	bool flush = false;
	int mispredicts = 0;
};
