#include <utility>


#include "../../include/instruction.h"


Instruction::Instruction() : opcode(Opcode(NOP)), location(0), operands({0,0,0})
{
}

Instruction::Instruction(OP op, int location, int r0, int r1, int r2) : opcode(Opcode(op)), location(location), operands({r0,r1,r2})
{
}

Instruction::~Instruction()
= default;

Instruction::Instruction(const Instruction & other) : opcode(other.opcode.op), location(other.location), operands(other.operands)
{

}

Instruction::Instruction(Opcode opcode) : opcode(std::move(opcode)), location(0)
{
}