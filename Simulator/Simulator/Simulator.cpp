// Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simulator.h"
#include <iostream>

Simulator::Simulator(std::vector<Data> boot_disk) : memory(boot_disk)
{
}

Simulator::~Simulator()
{
}

void Simulator::fetch() {
	register_file.MAR = program_counter;
	program_counter++;
	register_file.MDR = memory[register_file.MAR];
	std::cout << "fetched " << register_file.MDR.instruction.opcode << std::endl;
};

void decode() {};
void execute() {};

void Simulator::simulate() {
	while (true) {
		fetch();
		decode();
		execute();
	}
}


