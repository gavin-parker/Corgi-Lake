#pragma once
#include "register_file.h"
#include "alu.h"
#include "memory.h"
#include "fetcher.h"
#include "load_store.h"
#include "branch_unit.h"
#include "simulator_state.h"
#include "../static_branch_predictor.h"
#include "../saturating_counter.h"
#include "../reorder_buffer.h"
#define HALT_PROGRAM -1
class Simulator : public Component
{
	void fetch();
	void decode();
	void writeback();
	int execute(Instruction current_instruction);
	void flush();
	Fetcher fetcher;
	LoadStore load_store;
	Instruction stall_instruction;
	Buffer instruction_buffer;
	BranchUnit branch_unit;
	SaturatingCounter branch_predictor;
	std::vector<ALU> alus_;
	ReorderBuffer reorder_buffer_;
public:	
	SimState simState;
	int ticks = 0;
	explicit Simulator(std::vector<Data> boot_disk);
	~Simulator();
	void simulate();
	int tick();
	bool debug = true;
	bool findHazard(Instruction other);
};
