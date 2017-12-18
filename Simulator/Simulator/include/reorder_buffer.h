#pragma once
#include "instruction.h"
#include "result.h"
#include <deque>
#include "register_file.h"
#include "simulator_state.h"

struct OrderedInstruction
{
	Instruction instruction;
	bool finished = false;
	int result;
	bool success = false;
    int target;
};

class ReorderBuffer
{
private:
	std::deque<OrderedInstruction> buffer;
	RegisterFile *register_file_;
	SimState *sim_state_;
    Memory *memory;
	int counter = 0;
	bool debug_ = true;
public:
	ReorderBuffer(RegisterFile *register_file, SimState *sim_state, Memory *memory);
	~ReorderBuffer();
	void insert(Instruction instruction);
	void update(Result result, bool success = true, int target=0);
    void writeback();
	bool get_result_for_dependency(int reg, int *result);
	bool check_memory_dependency(int target, bool isLoad);
};