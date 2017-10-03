#pragma once
#include "register_file.h"
#include "alu.h"
#include "memory.h"
class Simulator
{
private:
	uint64_t fetch();
public:	
	RegisterFile register_file;
	Memory memory;
	int program_counter = 0;
	ALU alu;
	Simulator(std::vector<uint64_t> boot_disk);
	~Simulator();
	void simulate();
};
