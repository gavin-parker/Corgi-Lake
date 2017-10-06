#pragma once
#include "register_file.h"
#include "alu.h"
#include "memory.h"
class Simulator
{
private:
	void fetch();
	void decode();
	void execute();
public:	
	RegisterFile register_file;
	Memory memory;
	uint64_t program_counter = 0;
	ALU alu;
	Simulator(std::vector<Data> boot_disk);
	~Simulator();
	void simulate();
};
