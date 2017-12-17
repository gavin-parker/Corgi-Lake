#include "../include/reservation_station.h"
#include <assert.h>
#include "../include/result.h"

ReservationStation::ReservationStation(RegisterFile* register_file, ReorderBuffer* reorder_buffer) : register_file(register_file), reorder_buffer_(reorder_buffer)
{
}

ReservationStation::~ReservationStation()
{
}

bool ReservationStation::is_ready()
{
	if(is_free())
	{
		return false;
	}
	for(auto read : current_instruction.opcode.reads)
	{
		if(!ready_args[read])
		{
			return false;
		}
	}
    if(current_instruction.opcode.settings.unit == LDSTR){
        int target = args[0];
        OP op = current_instruction.opcode.op;
        if (op == LD || op == STR){
            target = args[0] + args[1];
        }
        bool isLoad = op == LD || op == LDI;
        for(auto rs : register_file->reservation_stations){
            if(rs->is_memory_dependency(isLoad, target)){
                return false;
            }
        }
    }
	return true;
}

bool ReservationStation::is_free()
{
	return isFree;
}

void ReservationStation::insert(Instruction instruction)
{
	assert(isFree);
	current_instruction = instruction;
	for (auto read : current_instruction.opcode.reads)
	{
		const auto reg = current_instruction.operands[read];

		if(register_file->register_address_table[reg] == nullptr)
		{
			if(!reorder_buffer_->get_result_for_dependency(reg, &args[read]))
			{
				args[read] = register_file->gp[reg].data;
			}
			ready_args[read] = true;
		}else
		{
			dependencies[read] = register_file->register_address_table[reg];
			ready_args[read] = false;
		}
	}
	for(auto write : current_instruction.opcode.writes)
	{
		const auto reg = current_instruction.operands[write];
		register_file->register_address_table[reg] = this;
	}
	isFree = false;
}

/**
 * \brief Update waiting instructions that depend on this result
 */
void ReservationStation::complete(Result result)
{
	for(auto &station : register_file->reservation_stations)
	{
		if(!station->is_free())
		{
			station->resolve(this, result);
		}
	}
	for(int i=0; i < 64; i++)
	{
		auto entry = register_file->register_address_table[i];
		if(entry == this)
		{
			register_file->register_address_table[i] = nullptr;
		}
	}
	dependencies = { nullptr, nullptr, nullptr };
	isFree = true;
	args = { 0, 0, 0 };
}

void ReservationStation::resolve(ReservationStation* dependent, Result result)
{
	/*
	 * Look through the args being waited on, resolve if it's this one
	 */
	for(int i=0; i < 3; i++	)
	{
		auto dependency = dependencies[i];
		if(dependency != nullptr && dependency == dependent)
		{
			dependencies[i] = nullptr;
			ready_args[i] = true;
			args[i] = result.result;
		}
	}
}

void ReservationStation::clear()
{
	isFree = true;
	args = { 0,0,0 };
	ready_args = { false, false, false };
	dependencies = { nullptr, nullptr, nullptr };
}
/*
 * Memory dependency exists if LD then STR or vv. and same/unknown target
 *
 */
bool ReservationStation::is_memory_dependency(bool isLoad, int target) {
    if(!is_free() || current_instruction.opcode.settings.unit != LDSTR){
        return false;
    }
    OP op = current_instruction.opcode.op;
    bool isLoad_b = op == LD || op == LDI;
    if(isLoad && isLoad_b) return false;
    if(!ready_args[0]) return true;
    int target_b = args[0];
    if(op == LD || op == STR){
        if(!ready_args[1]) return true;
        target_b += args[1];
    }
    return target == target_b;
}
