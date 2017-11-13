#include "stdafx.h"
#include "result.h"

Result::Result(Instruction instruction, uint64_t result) : instruction(instruction), result(result)
{
}

Result::~Result()
{
}