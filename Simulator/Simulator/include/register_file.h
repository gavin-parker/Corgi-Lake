#pragma once
#include <stdint.h>
#include <vector>
#include "data.h"
class RegisterFile
{
public:
	RegisterFile();
	~RegisterFile();
	Data gp[64];
	std::vector<Data> fetch_buffer;
	void print(Instruction instruction);
	bool stall;
};

