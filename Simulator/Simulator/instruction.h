#pragma once
#include <stdint.h>
enum Opcode { DATA, IADD, IADDI, IMUL, IMULI, ICMP, LD, STR, LDI, STRI, BRA, JUM, BLT, HALTEZ };

class Instruction
{
public:
	Opcode opcode;
	uint32_t operands[3] = { 0,0,0 };
	Instruction();
	~Instruction();

	static int operand_count(Opcode opcode) {
		if ((opcode >= IADD && opcode <= LD) || opcode == BLT) {
			return 3;
		}
		else if (opcode == LDI || opcode == STRI) {
			return 2;
		}
		else {
			return 1;
		}
	}
};

