#include "stdafx.h"
#include "assembler.h"
#include "benchmark_runner.h"
#include <sstream>     
#include <algorithm>
#include <iterator>

using std::string;
using std::istream_iterator;

Data Assembler::assemble(std::vector<string> tokens, int line_number) {

	OP op = opcodes[tokens[0]];
	Opcode mneumonic(op);
	int i = 0;
	int64_t dat = 0;
	bool isData = false;
	std::vector<int64_t> args = { 0,0,0 };
	if (mneumonic.op == DATA) {
		isData = true;
		dat = std::stoi(tokens[1], NULL);
	}
	else {
		for (int i = 0; i < mneumonic.operand_num; i++) {
			args[i] = std::stoi(tokens[i + 1], NULL);
		}
	}
	Data data = { isData, Instruction(mneumonic.op, line_number, args[0], args[1], args[2]), dat, tokens };
	return data;
}

std::vector<Data> Assembler::load_assembly_file(std::string path) {
	std::vector<Data> disk;
	std::ifstream assembly_file;
	assembly_file.open(path);
	std::vector<std::vector<string>> first_pass;
	int index = 0;
	if (assembly_file.is_open()) {
		std::string line;
		while (std::getline(assembly_file, line)) {
			//Trim commas,
			std::replace(line.begin(), line.end(), ',', ' ');
			//Tokenize
			std::istringstream stream(line);
			std::vector<string> tokens;
			std::copy(istream_iterator<string>(stream),
				istream_iterator<string>(),
				std::back_inserter(tokens));

			bool isComment = false;

			std::vector<string> trimmed;
			//Trim comments
			for (auto word : tokens) {
				if (word[0] == '#') {
					isComment = !isComment;
					continue;
				}
				if (isComment) {
					continue;
				}
				if (word[0] == '@') {
					std::string label = word.substr(1, word.size());
					labels[label] = index;
				}
				if (word[0] == 'r') {
					registers.insert(stoi(word.substr(1, word.size())));
					word = word.substr(1, word.size());
				}
				trimmed.push_back(word);
			}
			if (trimmed.size() > 0) {
				first_pass.push_back(trimmed);
				index++;
			}
		}
	}
	else {
		throw std::runtime_error("File not opened!");
	}
	assembly_file.close();

	int line_number = 0;
	for (auto line : first_pass) {
		//Tokenize
		std::vector<string> labelled;
		for (auto word : line) {
			if (word[0] == '~') {
				std::string label = word.substr(1, word.size());
				labelled.push_back(std::to_string(labels[label]));
			}
			else if (word[0] == '_') {
				//Assign a register to this var
				auto reg = assign_register(word);
				labelled.push_back(std::to_string(reg));
			}
			else {
				labelled.push_back(word);
			}
		}
		if (line.size() > 0) {
			disk.push_back(assemble(labelled, line_number));
			line_number++;
		}
	}
	disk.resize(200, { true, Instruction(DATA, 0, 0, 0, 0), 0, {} });
	return disk;
}

uint32_t Assembler::assign_register(std::string word)
{
	if (vars.find(word) == vars.end()) {
		for (uint32_t i = 0; i < 64; i++) {
			if (registers.find(i) == registers.end()) {
				vars[word] = i;
				registers.insert(i);
				return i;
			}
		}
	}
	else {
		return vars[word];
	}
}

Assembler::Assembler()
{
}


Assembler::~Assembler()
{
}
