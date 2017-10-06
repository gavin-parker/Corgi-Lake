#pragma once
#include <stdint.h>
#include "memory.h"
class RegisterFile
{
public:
	RegisterFile();
	~RegisterFile();
	uint64_t MAR;
	Data MDR;
	Data CIR;
	Data gp[64];
};

