#pragma once
#include <stdint.h>
#include <vector>
class Memory
{
private:
	std::vector<uint64_t> main_memory;
public:
	Memory(std::vector<uint64_t> program_memory);
	~Memory();
	uint64_t operator [](uint64_t i) const {

	};
};

