#pragma once
#include "instruction.h"
class Result {
public:
	Instruction instruction;
	int result;
	Result(Instruction instruction, int result);
	~Result();
	Result();
};