#include "stdafx.h"
#include "assembler.h"
#include "benchmark_runner.h"

Data Assembler::assemble(std::string opcode, std::string operand) {
	int i = 0;
	Data data;
	data.instruction.opcode = opcodes[opcode];
	if (data.instruction.opcode == DATA) {
		data.isData = true;
		data.data = std::stoi(operand, NULL);
	}
	else {
		data.isData = false;
		std::vector<std::string> operands = split(operand, ",");
		int i = 0;
		for (auto op : operands) {
			if (op[0] == 'r') {
				data.instruction.operands[i] = std::stoi(op.substr(1, op.size()), NULL);
			}
			else {
				data.instruction.operands[i] = std::stoi(op, NULL);
			}
			i++;
		}
	}
	return data;
}

Assembler::Assembler()
{
}


Assembler::~Assembler()
{
}
