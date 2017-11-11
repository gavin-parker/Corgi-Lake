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

int main()
{
	BenchmarkRunner benchmarker;
	std::vector<std::string> paths = { "vector_add.corg", "vector_sum.corg", "label_test.corg", "dot_product.corg" };
	int tests_passed = 0;
	int tests_failed = 0;
	std::vector<std::string> failed_tests;
	Assembler assembler;
	for (auto path : paths) {
		std::vector<Data> disk = assembler.load_assembly_file("../Simulator/" + path);
		Simulator simulator(disk);
		simulator.simulate();
		tests_passed++;
		std::cout << std::endl << "Cycles: " << simulator.ticks << std::endl;

	}
	std::cout << "TESTS PASSED: " << tests_passed << std::endl;
	std::cout << "TESTS FAILED: " << tests_failed << std::endl;
	for (auto failure : failed_tests) {
		std::cout << "failed " << failure << std::endl;
	}
	getchar();
	return 0;
}

