#pragma once
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "opcode.h"
static const char * OpcodeStrings[] = { "DATA", "IADD", "IADDI", "IMUL", "IMULI", "ICMP", "LD", "STR", "LDI", "STRI", "BRA", "JUM", "BLT", "HALTEZ", "HALTEQ", "NOP", "ISUB" };

static const char* opcode_string(OP op) {
	return OpcodeStrings[op];
}

class Instruction
{
public:
	Opcode opcode;
	std::vector<int32_t> operands;
	uint64_t location;
	Instruction();
	Instruction(OP op, int64_t location, int32_t r0, int32_t r1, int32_t r2);
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

};
