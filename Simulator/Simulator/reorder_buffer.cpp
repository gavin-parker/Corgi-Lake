#include "reorder_buffer.h"



ReorderBuffer::ReorderBuffer(RegisterFile *register_file) : register_file_(register_file)
{
}


ReorderBuffer::~ReorderBuffer()
{
}

void ReorderBuffer::insert(Instruction instruction)
{
	buffer.push_back({ instruction, false });
}

void ReorderBuffer::update(Result result)
{
	for(auto &ordered_instruction : buffer)
	{
		if(result.instruction == ordered_instruction.instruction)
		{
			ordered_instruction.finished = true;
			ordered_instruction.result = result.result;
		}
	}
}

void ReorderBuffer::writeback()
{
	while (buffer.size() > 0) {
		auto ordered_instruction = buffer.front();
		if (ordered_instruction.finished)
		{
			const auto destination = ordered_instruction.instruction.operands[0];
			register_file_->gp[destination].data = ordered_instruction.result;
			buffer.pop_front();
		}
		else
		{
			return;
		}
	}
}

bool ReorderBuffer::get_result_for_dependency(int reg, int *result)
{
	for(auto ordered_instruction : buffer)
	{
		for(auto write : ordered_instruction.instruction.opcode.writes)
		{
			auto target_reg = ordered_instruction.instruction.operands[write];
			if(target_reg == reg && ordered_instruction.finished)
			{
				*result = ordered_instruction.result;
				return true;
			}
		}
	}
	return false;
}
