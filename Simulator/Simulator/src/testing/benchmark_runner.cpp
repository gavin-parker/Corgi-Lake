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

int main(int argc, char *argv[])
{
    std::vector<std::string> paths;
    ulong alu_count=16;
    ulong ldstr_count=16;
    if(argc == 1){
        paths = { "vector_add.corg", "vector_sum.corg", "dot_product.corg", "raw_hazards.corg", "gcd.corg" , "factorial.corg", "matrixmul.corg", "swapsort.corg"};
    }else{
        for(int i=1; i < argc; i++){
            string arg(argv[i]);
            if(arg.find("--alus=") != string::npos){
                auto val = arg.substr(7,string::npos);
                alu_count = static_cast<ulong>(std::stoi(val));
            }else if(arg.find("--ldstrs=") != string::npos){
                auto val = arg.substr(9, string::npos);
                ldstr_count = static_cast<ulong>(std::stoi(val));
            }else {
                paths.push_back(argv[i]);
            }
        }
    }
	BenchmarkRunner benchmarker;
	int tests_passed = 0;
	int tests_failed = 0;
	std::vector<std::string> failed_tests;
	Assembler assembler;
	std::vector<benchmark_result> results;
	for (const auto &path : paths) {
        std::cout << "Executing: " << path << " ALUS: " << alu_count << " LDSTRS: " << ldstr_count << std::endl;
		std::vector<Data> disk = assembler.load_assembly_file(std::string("/home/gavin/workspace/Advanced-Architecture/Simulator/Simulator/tests/" + path));
		Simulator simulator(disk, alu_count, ldstr_count);
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
	return 0;
}

