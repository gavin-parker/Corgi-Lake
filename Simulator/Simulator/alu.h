#pragma once
#include "instruction.h"
#include "register_file.h"
#include "component.h"
#include "register_file.h"
#include "reservation_station.h"
#include <memory>
class ALU : public Component
{
private:
	std::shared_ptr<ReservationStation> input;
	std::shared_ptr<ReservationStation> output;
	RegisterFile *register_file;
	Data result;
	int result_location = 0;
	Instruction current_instruction;
public:
	bool result_ready = false;
	ALU(RegisterFile *register_file, std::shared_ptr<ReservationStation> input, std::shared_ptr<ReservationStation> output);
	~ALU();
	Data execute(Instruction instruction);
	int tick();
	void log();
	void write();
};

