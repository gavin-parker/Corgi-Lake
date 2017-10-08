#pragma once
#include <string>
#include <map>
#include "memory.h"
class Assembler
{
	std::map<std::string, uint32_t> labels = std::map<std::string, uint32_t>();
	std::map<std::string, Opcode> opcodes = { {"DATA", DATA}, {"IADD", IADD}, {"IADDI", IADDI},
											{"ICMP", ICMP}, {"LD", LD}, {"LDI", LDI}, {"BRA", BRA},
											{"JUM", JUM}, {"BLT", BLT}, {"HALTEZ", HALTEZ}, {"IMUL", IMUL},
											{"IMULI", IMULI}, {"STR",STR}, {"STRI", STRI},
											{"HALTEQ", HALTEQ} };
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
		for (int i = 0; i < results.size(); i++) {
			auto result = results[i];
			//clip whitespace
			if (result.size() == 0 || result == delimeter) {
				results.erase(results.begin() +i,results.begin() + i+1);
			}
		}
		return results;
	}

};

