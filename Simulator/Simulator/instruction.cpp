#include "stdafx.h"
#include "instruction.h"


Instruction::Instruction()
{

}

Instruction::~Instruction()
{
}

bool Instruction::raw(Instruction other) const
{
	return (operands[0] == other.operands[1] || operands[0] == other.operands[2]);
}

bool Instruction::war(Instruction other)
{
	return false;
}

bool Instruction::waw(Instruction other)
{
	return false;
}

bool Instruction::isHazard(Instruction other) const
{
	return raw(other);
}