#include "stdafx.h"
#include "assembler.h"
#include "benchmark_runner.h"

Data Assembler::assemble(std::string opcode, std::string operand, int line_number) {
	int i = 0;
	int64_t dat = 0;
	std::string line = opcode + " " + operand;
	bool isData = false;
	Opcode mneumonic(opcodes[opcode]);
	std::vector<int64_t> args = { 0,0,0 };
	if (mneumonic.op == DATA) {
		isData = true;
		dat = std::stoi(operand, NULL);
	}
	else {
		std::vector<std::string> operands = split(operand, ",");
		int i = 0;
		for (auto op : operands) {
			if (op[0] == 'r') {
				args[i] = std::stoi(op.substr(1, op.size()), NULL);
			}
			else if (op[0] == '~') {
				std::string label = op.substr(1, op.size());
				int loc = labels[label];
				args[i] = loc;
			}
			else {
				args[i] = std::stoi(op, NULL);
			}
			i++;
		}
	}
	Data data = { isData, Instruction(mneumonic.op, line_number, args[0], args[1], args[2]), dat, line };
	return data;
}

std::vector<Data> Assembler::load_assembly_file(std::string path) {
	std::vector<Data> disk;
	std::ifstream assembly_file;
	assembly_file.open(path);
	std::vector<std::string> first_pass;
	int index = 0;
	if (assembly_file.is_open()) {
		std::string line;
		while (std::getline(assembly_file, line)) {
			if (line.at(0) == '#') {
				continue;
			}

			size_t label_pos = line.find("@");
			if (label_pos != std::string::npos) {
				std::string label = line.substr(label_pos + 1, line.size());
				labels[label] = index;
				line.erase(label_pos);
			}
			first_pass.push_back(line);
			index++;
		}
	}
	else {
		throw std::runtime_error("File not opened!");
	}
	assembly_file.close();

	int line_number = 0;
	for (auto line : first_pass) {
		std::vector<std::string> contents = Assembler::split(line, " ");
		if (contents[0] == "NOP") {
			contents.push_back("");
		}
		disk.push_back(assemble(contents[0], contents[1], line_number));
		line_number++;
	}
	return disk;
}

Assembler::Assembler()
{
}


Assembler::~Assembler()
{
}
