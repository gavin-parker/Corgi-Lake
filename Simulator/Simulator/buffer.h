#pragma once
#include <deque>
#include "memory.h"
#include "instruction.h"
#include <iostream>
class Buffer
{
private:
	std::deque<Instruction> queue;
public:
	Buffer();
	~Buffer();
	void push(Instruction item);
	Instruction pop();
	bool isEmpty();
	void flush();
	size_t find_hazard(Instruction instruction);
	size_t size();
	size_t completion_time();
};