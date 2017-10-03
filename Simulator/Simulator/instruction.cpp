#include "stdafx.h"
#include "instruction.h"

int operand_count(Opcode opcode) {
	if ((opcode >= IADD && opcode <= LD) || opcode == BLT) {
		return 3;
	}
	else if (opcode == LDI) {
		return 2;
	}
	else {
		return 1;
	}
}

Instruction::Instruction()
{

}

Instruction::~Instruction()
{
}
