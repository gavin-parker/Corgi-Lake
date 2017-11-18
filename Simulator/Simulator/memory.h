#pragma once
#include <stdint.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "instruction.h"
#include "component.h"
struct Data {
	bool isData = true;
	Instruction instruction;
	int64_t data;
	std::vector<std::string> line;
};
/*
static void print_data(Data data) {
		for (auto word : data.line) {
			std::cout
				<< std::setw(5) << word;
		}
		std::cout << std::endl;
}
*/
class Memory : public Component
{
private:
	std::vector<Data> main_memory;
public:
	Memory(std::vector<Data> program_memory);
	~Memory();
	Data operator [](uint64_t i){
 		return main_memory[static_cast<size_t>(i)];
	};
	int tick();
	size_t size() {
		return main_memory.size();
	}
};