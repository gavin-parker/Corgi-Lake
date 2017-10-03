#include "stdafx.h"
#include "assembler.h"


uint64_t Assembler::assemble(std::string opcode, std::string operand) {
	int i = 0;
	std::string current = "";
	for (auto c : operand) {
		if (c == ',') {

		}
		current  += c;
	}
}

Assembler::Assembler()
{
}


Assembler::~Assembler()
{
}
