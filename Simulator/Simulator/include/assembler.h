#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include "memory.h"
class Assembler
{
	std::map<std::string, uint32_t> labels;
	std::map<std::string, uint32_t> vars;
	std::unordered_set<uint32_t> registers;

	std::map<std::string, OP> opcodes = { {"DATA", DATA}, {"IADD", IADD}, {"IADDI", IADDI},
											{"ICMP", ICMP}, {"LD", LD}, {"LDI", LDI}, {"BRA", BRA},
											{"JUM", JUM}, {"BLT", BLT}, {"HALTEZ", HALTEZ}, {"IMUL", IMUL},
											{"IMULI", IMULI}, {"STR",STR}, {"STRI", STRI},
											{"HALTEQ", HALTEQ}, {"NOP", NOP }, {"ISUB", ISUB} };

public:
	Assembler();
	~Assembler();
	Data assemble(std::vector<std::string> tokens, int line_number);
	std::vector<Data> load_assembly_file(std::string path);
	uint32_t assign_register(std::string word);
	static std::vector<std::string> split(std::string input, std::string delimeter) {
		size_t pos = 0;
		std::vector<std::string> results;
		while ((pos = input.find(delimeter)) != std::string::npos) {
			results.push_back(input.substr(0, pos));
			input.erase(0, pos + delimeter.size());
		}
		results.push_back(input.substr(0, input.size()));
		for (size_t i = 0; i < results.size(); i++) {
			auto result = results[i];
			//clip whitespace
			if (result.size() == 0 || result == delimeter) {
				results.erase(results.begin() +i,results.begin() + i+1);
			}
		}
		return results;
	}

};

