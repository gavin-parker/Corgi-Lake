#include "stdafx.h"
#include "alu.h"


ALU::ALU()
{
}


ALU::~ALU()
{
}

void ALU::execute(Instruction instruction, RegisterFile registers) {
	uint64_t r0 = instruction.operands[0];
	uint64_t r1 = instruction.operands[1];
	uint64_t r2 = instruction.operands[2];
	uint64_t v;

	switch (instruction.opcode) {
	case IADD:
		registers.gp[r0].data = registers.gp[r1].data + registers.gp[r2].data;
		break;
	case IADDI:
	{
		v = r2;
		registers.gp[r0].data = registers.gp[r1].data + v;
		break;
	}
	case IMUL:
		registers.gp[r0].data = registers.gp[r1].data * registers.gp[r2].data;
		break;
	case IMULI:
		v = r2;
		registers.gp[r0].data = registers.gp[r1].data * v;
		break;
	}
}
