#pragma once
#include <stdint.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "component.h"
#include "data.h"

class Memory : public Component
{
private:
	std::vector<Data> main_memory;
public:
	explicit Memory(std::vector<Data> program_memory);
	~Memory();
	Data operator [](uint64_t i){
 		return main_memory[static_cast<size_t>(i)];
	};
	int tick();
	size_t size() {
		return main_memory.size();
	}
};