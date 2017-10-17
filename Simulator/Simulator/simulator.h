#pragma once
#include "register_file.h"
#include "alu.h"
#include "memory.h"
#include "fetcher.h"]
#include "load_store.h"
#define HALT_PROGRAM -1
class Simulator : public Component
{
private:
	void fetch();
	int execute();
	void print_state();
	void flush();
	Fetcher fetcher;
	LoadStore load_store;
public:	
	int ticks = 0;
	RegisterFile register_file;
	Memory memory;
	uint64_t program_counter = 0;
	ALU alu;
	Simulator(std::vector<Data> boot_disk);
	~Simulator();
	void simulate();
	int tick();
	bool debug = true;
	void dump();
};
