#pragma once
#include <stdint.h>
#include <vector>
#include "instruction.h"
struct Data {
	bool isData = true;
	Instruction instruction;
	uint64_t data;
};

class Memory
{
private:
	std::vector<Data> main_memory;
public:
	Memory(std::vector<Data> program_memory);
	~Memory();
	Data operator [](uint64_t i) const {
		return main_memory[(size_t)i];
	};
};