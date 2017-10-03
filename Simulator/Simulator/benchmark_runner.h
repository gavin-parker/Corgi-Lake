#pragma once

#define BENCHMARK_PASS 0
#define BENCHMARK_FAIL -1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class BenchmarkRunner
{
public:
	BenchmarkRunner();
	~BenchmarkRunner();

private:
	std::vector<uint64_t> load_assembly_file(std::ofstream assembly_file);
};

