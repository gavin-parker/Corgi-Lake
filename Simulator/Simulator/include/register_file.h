#pragma once
#include <stdint.h>
#include <vector>
#include "data.h"
class ReservationStation;

class RegisterFile
{
public:
	RegisterFile();
	~RegisterFile();
	Data gp[64];
	ReservationStation* register_address_table[64] = {nullptr};
	std::vector<ReservationStation*> reservation_stations = {};
	std::vector<Data> fetch_buffer;
	void print(Instruction instruction);
	bool stall;
};