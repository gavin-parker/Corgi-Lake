// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simulator.h"

Simulator::Simulator(std::vector<uint64_t> boot_disk) : memory(boot_disk)
{
}

Simulator::~Simulator()
{
}

uint64_t Simulator::fetch() {
	register_file.MAR = program_counter;
	program_counter++;
	register_file.MDR = memory[register_file.MAR];

};

void decode() {};
void execute() {};

void Simulator::simulate() {
	uint64_t instruction = fetch();
	decode();
	execute();
}


