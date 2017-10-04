#pragma once
#include "register_file.h"
#include "alu.h"
#include "memory.h"
#include "instruction.h"


class Simulator
{
private:
	void fetch();
public:	
	RegisterFile register_file;
	Memory memory;
	int program_counter = 0;
	ALU alu;
	Simulator(std::vector<Data> boot_disk);
	~Simulator();
	void simulate();
};
