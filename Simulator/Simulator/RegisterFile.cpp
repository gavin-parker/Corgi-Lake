#include "stdafx.h"
#include "register_file.h"


RegisterFile::RegisterFile()
{
}


RegisterFile::~RegisterFile()
{
}

void RegisterFile::print(Instruction instruction)
{
	std::cout
		<< std::setw(6) << instruction.opcode.settings.name;
	for (int i = 0; i < 3; i++) {
		Opcode op = instruction.opcode;
		if (op.reads.find(i) != op.reads.end() || op.writes.find(i) != op.writes.end()) {
			auto operand = instruction.operands[i];
			std::cout << std::setw(5) << "r" << std::to_string(operand)
				<< "(" << std::to_string(gp[operand].data) << ")";
		}
	}
	std::cout << std::endl;
}
