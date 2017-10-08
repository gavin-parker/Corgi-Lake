#include "stdafx.h"
#include "benchmark_runner.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
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
	std::vector<std::string> first_pass;
	std::unordered_map<std::string, int> labels;
	int index = 0;
	if (assembly_file.is_open()) {
		std::string line;
		while (std::getline(assembly_file, line)) {
			first_pass.push_back(line);
			size_t label_pos = line.find("@");
			if (label_pos != std::string::npos) {
				std::string label = line.substr(label_pos+1, line.size());
				labels[label] = 0;
			}
		}
	}
	else {
		throw std::runtime_error("File not opened!");
	}
	assembly_file.close();


	for (auto line : first_pass) {
		if (line.at(0) != '#') {
			std::vector<std::string> contents = Assembler::split(line, " ");
			disk.push_back(assembler.assemble(contents[0], contents[1]));
		}
	}
	return disk;
}

int main()
{
	BenchmarkRunner benchmarker;
	std::vector<std::string> paths = { "vector_add.corg", "vector_sum.corg" };
	int tests_passed = 0;
	int tests_failed = 0;
	std::vector<std::string> failed_tests;
	for (auto path : paths) {
		try {
			std::vector<Data> disk = benchmarker.load_assembly_file("../Simulator/" + path);
			Simulator simulator(disk);
			simulator.simulate();
			tests_passed++;
		}
		catch (std::exception e) {
			tests_failed++;
			failed_tests.push_back(path);
		}
	}
	std::cout << "TESTS PASSED: " << tests_passed << std::endl;
	std::cout << "TESTS FAILED: " << tests_failed << std::endl;
	for (auto failure : failed_tests) {
		std::cout << "failed " << failure << std::endl;
	}
	getchar();
	return 0;
}

