#include "../include/reorder_buffer.h"
#include <cassert>


ReorderBuffer::ReorderBuffer(RegisterFile *register_file, SimState *sim_state) : register_file_(register_file), sim_state_(sim_state)
{
}


ReorderBuffer::~ReorderBuffer()
= default;

void ReorderBuffer::insert(Instruction instruction)
{
	buffer.push_back({ instruction, false, false });
}

void ReorderBuffer::update(Result result, bool success, int target)
{
	bool updated = false;
	for(auto &ordered_instruction : buffer)
	{
		if(result.instruction.sameTag(ordered_instruction.instruction))
		{
			ordered_instruction.finished = true;
			ordered_instruction.result = static_cast<int>(result.result);
			ordered_instruction.success = success;
            ordered_instruction.target = target;

			return;
		}
	}
	assert(updated);
}

void ReorderBuffer::writeback()
{
	while (!buffer.empty()) {
		auto ordered_instruction = buffer.front();
		const auto isBranch = ordered_instruction.instruction.opcode.settings.unit == BRANCH;
		if (ordered_instruction.finished)
		{
			if(debug_) {
				register_file_->print(ordered_instruction.instruction);
			}
            if(isBranch && ordered_instruction.success)
			{
				//change PC && flush
				sim_state_->program_counter = ordered_instruction.result;
				sim_state_->flush = true;
				buffer.clear();
			}else if(isBranch && !ordered_instruction.success)
			{
				buffer.pop_front();
			}else {
				if(!ordered_instruction.instruction.opcode.writes.empty()) {
					const auto destination = ordered_instruction.instruction.operands[0];
					register_file_->gp[destination].data = ordered_instruction.result;
				}
				buffer.pop_front();
			}
		}
		else
		{
			return;
		}
	}
}

bool ReorderBuffer::get_result_for_dependency(int reg, int *result)
{
	for(auto it = buffer.rbegin(); it != buffer.rend(); ++it)
	{
        auto ordered_instruction = *it;
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
/*
 * Return true if there is a dependency
 */
bool ReorderBuffer::check_memory_dependency(int target, bool isLoad) {
    for(auto it = buffer.rbegin(); it != buffer.rend(); ++it) {
        auto ordered_instruction = *it;
        if(ordered_instruction.instruction.opcode.settings.unit) {
            OP op = ordered_instruction.instruction.opcode.op;
            bool isLoadB = op == LD || op == LDI;
            /*
             * only Loads are allowed OoO
             */
            if((!(isLoad && isLoadB) && target == ordered_instruction.target)
               || !ordered_instruction.finished){
                return true;
            }
        }
    }
    return false;
}
