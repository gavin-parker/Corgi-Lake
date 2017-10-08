#pragma once
#include "instruction.h"
#include "register_file.h"
class ALU
{
public:
	ALU();
	~ALU();
	void execute(Instruction instruction, RegisterFile registers);
};

