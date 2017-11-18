#include "stdafx.h"
#include "benchmark_runner.h"
#include <iostream>
#include <fstream>
#include <string>
#include "simulator.h"
#include <fstream>
#include <iomanip>
struct benchmark_result {
	std::string name;
	int ticks = 0;
	int instructions;
	bool pass = false;
};

BenchmarkRunner::BenchmarkRunner()
{
}


BenchmarkRunner::~BenchmarkRunner()
{
}

int main()
{
	BenchmarkRunner benchmarker;
	std::vector<std::string> paths = { "vector_add.corg", "vector_sum.corg", "label_test.corg", "dot_product.corg", "raw_hazards.corg" };
	int tests_passed = 0;
	int tests_failed = 0;
	std::vector<std::string> failed_tests;
	Assembler assembler;
	std::vector<benchmark_result> results;
	for (auto path : paths) {
		bool passed = true;
		std::vector<Data> disk = assembler.load_assembly_file("../Simulator/" + path);
		Simulator simulator(disk);
		try {
			simulator.simulate();
		}catch(std::exception e){
			passed = false;
		}
		tests_passed++;
		results.push_back({ path, simulator.ticks, simulator.simState.instructions_executed, false });

	}
	std::cout
		<< std::setw(18) << "NAME"
		<< std::setw(14) << "TICKS"
		<< std::setw(14) << "INSTRUCTIONS"
		<< std::endl;

	for (auto result : results) {
		std::cout
			<< std::setw(18) << result.name
			<< std::setw(14) << result.ticks
			<< std::setw(14) << result.instructions
			<< std::endl;
	}


	std::cout << "TESTS PASSED: " << tests_passed << std::endl;
	std::cout << "TESTS FAILED: " << tests_failed << std::endl;
	for (auto failure : failed_tests) {
		std::cout << "failed " << failure << std::endl;
	}
	getchar();
	return 0;
}

