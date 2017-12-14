#pragma once
#include "instruction.h"
class Result {
public:
	Instruction instruction;
	uint64_t result;
	Result(Instruction instruction, int result);
	~Result();
	Result();
};