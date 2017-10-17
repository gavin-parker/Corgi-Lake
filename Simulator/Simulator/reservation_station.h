#pragma once
#include <queue>
#include "memory.h"
class ReservationStation
{
private:
	std::queue<Instruction> queue;
public:
	ReservationStation();
	~ReservationStation();
	void push(Instruction item);
	Instruction pop();
	bool isEmpty();
	void flush();
};

