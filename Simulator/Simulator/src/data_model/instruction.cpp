#include "../../include/stdafx.h"
#include "../../include/instruction.h"


Instruction::Instruction() : opcode(Opcode(NOP)), location(0), operands({0,0,0})
{
}

Instruction::Instruction(OP op, int64_t location, int32_t r0, int32_t r1, int32_t r2) : opcode(Opcode(op)), location(location), operands({r0,r1,r2})
{
}

Instruction::~Instruction()
{
}

Instruction::Instruction(const Instruction & other) : opcode(other.opcode.op), location(other.location), operands(other.operands)
{

}

Instruction::Instruction(Opcode opcode) : opcode(opcode), location(0)
{
}

bool Instruction::raw(Instruction other) const
{
	for (auto read : other.opcode.reads) {
		int32_t read_operand = other.operands[read];
		for (auto write : opcode.writes) {
			int32_t write_operand = operands[write];
			if (read_operand == write_operand) {
				return true;
			}
		}
	}
	return false;
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