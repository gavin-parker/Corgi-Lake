#pragma once
#include "register_file.h"
#include "alu.h"
#include "memory.h"
#define HALT_PROGRAM -1
class Simulator : public Component
{
private:
	void fetch();
	int execute();
	void print_state();
	int ticks = 0;
public:	
	RegisterFile register_file;
	Memory memory;
	uint64_t program_counter = 0;
	ALU alu;
	Simulator(std::vector<Data> boot_disk);
	~Simulator();
	void simulate();
	void tick();
	bool debug = true;
};
