#pragma once
#include <string>
#include <map>
class Assembler
{
private:
	std::map<std::string, uint32_t> opcodes = {
	{"IADD", 1},
	{"IADDI",2},
	{"ICMP", 3},
	{"LD", 4},
	{"LDI", 5},
	{"BRA", 6},
	{"JUM",7},
	{"BLT",8} };
	
	std::map<std::string, uint32_t> labels = std::map<std::string, uint32_t>();
public:
	Assembler();
	~Assembler();
	uint64_t assemble(std::string opcode, std::string operand);
};

