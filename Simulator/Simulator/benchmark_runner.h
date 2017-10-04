#pragma once

#define BENCHMARK_PASS 0
#define BENCHMARK_FAIL -1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "assembler.h"
#include "memory.h"
class BenchmarkRunner
{
public:
	BenchmarkRunner();
	~BenchmarkRunner();
	Assembler assembler;
	std::vector<Data> load_assembly_file(std::string path);

private:
};


