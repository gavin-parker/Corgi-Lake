#pragma once
#include <string>
#include <map>
#include "memory.h"
class Assembler
{
	std::map<std::string, uint32_t> labels = std::map<std::string, uint32_t>();
	std::map<std::string, Opcode> opcodes = { {"DATA", DATA}, {"IADD", IADD}, {"IADDI", IADDI}, {"ICMP", ICMP}, {"LD", LD}, {"LDI", LDI}, {"BRA", BRA}, {"JUM", JUM}, {"BLT", BLT} };
public:
	Assembler();
	~Assembler();
	Data assemble(std::string opcode, std::string operand);

	static std::vector<std::string> split(std::string input, std::string delimeter) {
		size_t pos = 0;
		std::vector<std::string> results;
		while ((pos = input.find(delimeter)) != std::string::npos) {
			results.push_back(input.substr(0, pos));
			input.erase(0, pos + delimeter.size());
		}
		results.push_back(input.substr(0, input.size()));
		return results;
	}

};

