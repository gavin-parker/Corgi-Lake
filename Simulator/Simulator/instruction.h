#pragma once
#include <stdint.h>
enum Opcode { DATA, IADD, IADDI, ICMP, LD, LDI, BRA, JUM, BLT };

class Instruction
{
public:
	Opcode opcode;
	uint32_t operands[3] = { 0,0,0 };
	Instruction();
	~Instruction();
};

