#pragma once
#include "register_file.h"
#include "reorder_buffer.h"

class Result;

class ReservationStation
{
	RegisterFile *register_file;
	ReorderBuffer *reorder_buffer_;
	bool isFree = true;
public:
	Instruction current_instruction;
	ReservationStation(RegisterFile *register_file, ReorderBuffer *reorder_buffer);
	~ReservationStation();
	bool is_ready();
	bool is_free();
	void insert(Instruction instruction);
	void complete(Result result);
	void resolve(ReservationStation* dependent, Result result);
	void clear();
	std::vector<int> args = { 0,0,0 };
	std::vector< bool> ready_args = { false, false, false };
	std::vector<ReservationStation*> dependencies = { nullptr,nullptr,nullptr };
};

