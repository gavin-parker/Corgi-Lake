#pragma once
#include "instruction.h"
class Result {
public:
	const Instruction instruction;
	const uint64_t result;
	bool isHazard(Instruction other) { return instruction.isHazard(other); };
	Result(Instruction instruction, uint64_t result);
	~Result();
};