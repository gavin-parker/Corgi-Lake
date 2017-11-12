#pragma once
#include "register_file.h"
#include "result.h"
#include "buffer.h"
#include "instruction.h"
#include <vector>
struct SimState {
	RegisterFile register_file;
	Memory memory;
	uint64_t program_counter = 0;
	int instructions_executed = 0;
	std::vector<Buffer<Result>> output_buffers;
};

static bool containsHazard(SimState simstate, Instruction instruction) {
	for (auto &buffer : simstate.output_buffers) {
		if (buffer.containsHazard(instruction)) {
			return true;
		}
	}
	return false;
}