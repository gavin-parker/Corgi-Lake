#include "stdafx.h"
#include "result.h"

Result::Result(Instruction instruction, uint64_t result) : instruction(instruction), result(result)
{
}

Result::~Result()
{
}

bool Result::raw(Instruction other)
{
	return !(instruction.operands[0] == other.operands[1] || instruction.operands[0] == other.operands[2]);
}

bool Result::war(Instruction other)
{
	return false;
}

bool Result::waw(Instruction other)
{
	return false;
}

bool Result::isHazard(Instruction other)
{
	return raw(other);
}