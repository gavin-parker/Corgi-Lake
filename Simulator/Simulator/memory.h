#pragma once
#include <stdint.h>
#include <vector>
#include "instruction.h"
#include "component.h"
struct Data {
	bool isData = true;
	Instruction instruction;
	int64_t data;
	std::string line;
};

class Memory : public Component
{
private:
	std::vector<Data> main_memory;
public:
	Memory(std::vector<Data> program_memory);
	~Memory();
	Data operator [](uint64_t i){
 		return main_memory[(size_t)i];
	};
	int tick();
};