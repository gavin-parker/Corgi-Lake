#pragma once
#include "instruction.h"
class Result {
public:
	const Instruction instruction;
	const uint64_t result;
	Result(Instruction instruction, uint64_t result);
	~Result();
	bool raw(Instruction other);
	bool war(Instruction other);
	bool waw(Instruction other);
	bool isHazard(Instruction other);
};