#include "../../include/stdafx.h"
#include "../../include/benchmark_runner.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../../include/simulator.h"
#include <iomanip>
#include <stdlib.h>
struct benchmark_result {
	std::string name;
	int ticks;
	int instructions;
	bool pass;
	int mispredicts;
};
using std::string;
BenchmarkRunner::BenchmarkRunner()
= default;


BenchmarkRunner::~BenchmarkRunner()
= default;

int main()
{
	BenchmarkRunner benchmarker;
	std::vector<std::string> paths = { "vector_add.corg", "vector_sum.corg",/* "label_test.corg"*/ "dot_product.corg",/* "raw_hazards.corg",*/ "gcd.corg" , "factorial.corg" };
	int tests_passed = 0;
	int tests_failed = 0;
	std::vector<std::string> failed_tests;
	Assembler assembler;
	std::vector<benchmark_result> results;
	for (const auto &path : paths) {
        std::cout << "Executing: " << path << std::endl;
		std::vector<Data> disk = assembler.load_assembly_file(std::string("C:/Users/gavin/workspace/Advanced-Architecture/Simulator/Simulator/tests/" + path));
		Simulator simulator(disk);
		try {
			simulator.simulate();
		}catch(std::exception e){
		}
		tests_passed++;
		results.push_back({ path, simulator.ticks, simulator.simState.instructions_executed, false, simulator.simState.mispredicts });
        std::cout << std::endl;
	}
	std::cout
		<< std::setw(18) << "NAME"
		<< std::setw(14) << "INSTRUCTIONS"
		<< std::setw(14) << "TICKS"
		<< std::setw(14) << "MISPREDICTS"
		<< std::endl;

	for (auto result : results) {
		std::cout
			<< std::setw(18) << result.name
			<< std::setw(14) << result.instructions
			<< std::setw(14) << result.ticks
			<< std::setw(14) << result.mispredicts
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

