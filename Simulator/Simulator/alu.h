#pragma once
#include "instruction.h"
#include "register_file.h"
#include "component.h"
#include "register_file.h"
class ALU : public Component
{
private:
	RegisterFile register_file;
	Data result;
	Instruction current_instruction;
public:
	ALU(RegisterFile register_file);
	~ALU();
	Data execute(Instruction instruction);
	void tick();
};

