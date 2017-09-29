#pragma once

#define BENCHMARK_PASS 0
#define BENCHMARK_FAIL -1

class BenchmarkRunner
{
public:
	BenchmarkRunner();
	~BenchmarkRunner();
private:
	// Benchmarks

	int vector_add();
};

