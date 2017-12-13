#include "reservation_station.h"
#include <assert.h>
#include "include/result.h"

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
