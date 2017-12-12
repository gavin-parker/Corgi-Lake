#pragma once
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "opcode.h"
static const char * OpcodeStrings[] = { "DATA", "IADD", "IADDI", "IMUL", "IMULI", "ICMP", "LD", "STR", "LDI", "STRI", "BRA", "JUM", "BLT", "HALTEZ", "HALTEQ", "NOP", "ISUB" };

static const char* opcode_string(OP op) {
	return OpcodeStrings[op];
}



class Instruction
{
public:
	Opcode opcode;
	std::vector<int> operands;
	int location;
	Instruction();
	Instruction(OP op, int location, int r0, int r1, int r2);
	~Instruction();
	Instruction(const Instruction &other);
	Instruction(Opcode opcode);
	bool raw(Instruction other) const;
	bool war(Instruction other);
	bool waw(Instruction other);
	bool isHazard(Instruction other) const;
	int num_operands() {
		return opcode.operand_num;
	}
	bool operator==(const Instruction& instruction)const
	{
		return opcode.op == instruction.opcode.op
			&& operands[0] == instruction.operands[0]
			&& operands[1] == instruction.operands[1]
			&& operands[2] == instruction.operands[2];
	};

};

namespace std
{
	template<>
	struct hash<Instruction> {
		size_t operator()(const Instruction &pt) const {
			return std::hash<int>()((int)pt.location);
		}
	};
};