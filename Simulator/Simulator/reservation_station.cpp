#include "stdafx.h"
#include "reservation_station.h"


ReservationStation::ReservationStation()
{
}


ReservationStation::~ReservationStation()
{
}

void ReservationStation::push(Instruction item)
{
	queue.push(item);
}

Instruction ReservationStation::pop()
{
	Instruction ret = queue.front();
	queue.pop();
	return ret;
}

bool ReservationStation::isEmpty()
{
	return (queue.size() == 0);
}

void ReservationStation::flush()
{
	queue.empty();
}
