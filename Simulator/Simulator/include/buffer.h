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
	size_t size();

	void push_front(Instruction item);
};