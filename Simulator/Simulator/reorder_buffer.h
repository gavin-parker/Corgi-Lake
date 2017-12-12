#pragma once
#include "include/instruction.h"
#include "include/result.h"
#include <deque>
#include "include/register_file.h"

struct OrderedInstruction
{
	Instruction instruction;
	bool finished = false;
	int result;
};

class ReorderBuffer
{
	std::deque<OrderedInstruction> buffer;
	RegisterFile *register_file_;
public:
	ReorderBuffer(RegisterFile *register_file);
	~ReorderBuffer();
	void insert(Instruction instruction);
	void update(Result result);
	void writeback();
	bool get_result_for_dependency(int reg, int *result);
};