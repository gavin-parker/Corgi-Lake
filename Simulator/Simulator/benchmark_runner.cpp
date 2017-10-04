#include "stdafx.h"
#include "benchmark_runner.h"
#include <iostream>
#include <fstream>
#include <string>
#include "simulator.h"
#include <fstream>
BenchmarkRunner::BenchmarkRunner()
{
}


BenchmarkRunner::~BenchmarkRunner()
{
}


std::vector<Data> BenchmarkRunner::load_assembly_file(std::string path) {
	std::vector<Data> disk;
	std::ifstream assembly_file;
	assembly_file.open(path);
	if (assembly_file.is_open()) {
		std::string line;
		while (std::getline(assembly_file, line)) {
			if (line.at(0) != '#') {
				std::vector<std::string> contents = Assembler::split(line, " ");
				disk.push_back(assembler.assemble(contents[0], contents[1]));
			}
		}
	}
	else {
		throw std::runtime_error("File not opened!");
	}
	assembly_file.close();
	return disk;
}

int main()
{
	BenchmarkRunner benchmarker;
	std::string path = "../Simulator/benchmark_suite.corg";
	std::vector<Data> disk = benchmarker.load_assembly_file(path);
	Simulator simulator(disk);
	simulator.simulate();
	getchar();
	return 0;
}

