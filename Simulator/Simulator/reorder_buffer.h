#pragma once
#include "include/instruction.h"
#include "include/result.h"
#include <deque>
#include "include/register_file.h"
#include "include/simulator_state.h"

struct OrderedInstruction
{
	Instruction instruction;
	bool finished = false;
	int result;
	bool success = false;
};

class ReorderBuffer
{
private:
	std::deque<OrderedInstruction> buffer;
	RegisterFile *register_file_;
	SimState *sim_state_;
public:
	ReorderBuffer(RegisterFile *register_file, SimState *sim_state);
	~ReorderBuffer();
	void insert(Instruction instruction);
	void update(Result result, bool success = true);
	void writeback();
	bool get_result_for_dependency(int reg, int *result);
};