#pragma once
#include <stdint.h>
enum Opcode { DATA, IADD, IADDI, IMUL, IMULI, ICMP, LD, STR, LDI, STRI, BRA, JUM, BLT, HALTEZ, HALTEQ };
class Instruction
{
public:
	Opcode opcode;
	int32_t operands[3] = { 0,0,0 };
	Instruction();
	~Instruction();

	static int operand_count(Opcode opcode) {
		if ((opcode >= IADD && opcode <= LD) || opcode == BLT) {
			return 3;
		}
		else if (opcode == LDI || opcode == STRI || opcode == HALTEQ) {
			return 2;
		}
		else {
			return 1;
		}
	}
};

