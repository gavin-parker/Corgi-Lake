#pragma once
#include <stdint.h>
class RegisterFile
{
public:
	RegisterFile();
	~RegisterFile();
	uint64_t MAR;
	uint64_t MDR;
	uint64_t CIR;
};

