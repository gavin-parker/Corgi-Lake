#include "stdafx.h"
#include "benchmark_runner.h"
#include <iostream>
#include <fstream>
#include <string>

BenchmarkRunner::BenchmarkRunner()
{
}


BenchmarkRunner::~BenchmarkRunner()
{
}


std::vector<uint64_t> BenchmarkRunner::load_assembly_file(std::ifstream assembly_file) {
	if (assembly_file.is_open()) {
		std::string line;
		while (std::getline(assembly_file, line)) {
			if (line.at(0) != '#') {
				std::string opcode;
				std::string operand;
				opcode < line;
				operand < line;

			}
		}
	}
}

int main()
{
	std::cout << "hi" << std::endl;
	getchar();
	return 0;
}

