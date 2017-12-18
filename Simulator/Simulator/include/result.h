#pragma once
#include "instruction.h"
class Result {
public:
	Instruction instruction;
	int result;
	int target;
	Result(Instruction instruction, int result, int target = 0);
	~Result();
	Result();
};