#pragma once
#include "register_file.h"
#include "alu.h"
#include "memory.h"
#define HALT_PROGRAM -1
class Simulator
{
private:
	void fetch();
	void decode();
	int execute();
public:	
	RegisterFile register_file;
	Memory memory;
	uint64_t program_counter = 0;
	ALU alu;
	Simulator(std::vector<Data> boot_disk);
	~Simulator();
	void simulate();
};
