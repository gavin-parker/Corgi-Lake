#pragma once
#include "reservation_station.h"
#include "register_file.h"
struct SimState {
	RegisterFile register_file;
	Memory memory;
	uint64_t program_counter = 0;
	int instructions_executed = 0;
};