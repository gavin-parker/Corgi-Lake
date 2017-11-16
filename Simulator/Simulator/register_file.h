#pragma once
#include <stdint.h>
#include <vector>
#include "memory.h"
class RegisterFile
{
public:
	RegisterFile();
	~RegisterFile();
	Data gp[64];
	std::vector<Data> fetch_buffer;
};

