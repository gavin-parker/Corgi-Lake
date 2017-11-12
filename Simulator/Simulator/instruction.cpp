#include "stdafx.h"
#include "instruction.h"


Instruction::Instruction()
{

}

Instruction::~Instruction()
{
}

Result::Result(Instruction instruction, uint64_t result) : instruction(instruction), result(result)
{
}

Result::~Result()
{
}
