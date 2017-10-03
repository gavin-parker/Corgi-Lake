#include "stdafx.h"
#include "assembler.h"


uint64_t Assembler::assemble(std::string opcode, std::string operand) {
	uint32_t opcode_bits;
	uint32_t operand_bits;
	opcode_bits = opcodes[opcode];
	//Is a register
	if (operand.at(0) == 'r') {

	}
}

Assembler::Assembler()
{
}


Assembler::~Assembler()
{
}
