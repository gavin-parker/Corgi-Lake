#pragma once
#include <string>
#include <map>
class Assembler
{
	std::map<std::string, uint32_t> labels = std::map<std::string, uint32_t>();
public:
	Assembler();
	~Assembler();
	uint64_t assemble(std::string opcode, std::string operand);
};

