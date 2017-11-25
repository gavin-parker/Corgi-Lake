#pragma once
#include "instruction.h"
struct Data {
	bool isData;
	Instruction instruction;
	int data;
	std::vector<std::string> line;
};