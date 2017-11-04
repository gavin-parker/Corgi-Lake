#pragma once
#include "component.h"
#include "instruction.h"
#include "reservation_station.h"
#include "register_file.h"
#include "memory.h"
#include <memory>
class LoadStore : public Component
{
private:
	Instruction current_instruction;
	void execute(Instruction instruction);
	Memory *memory;
	RegisterFile *register_file;
	Data result;
	int result_location = 0;
	bool result_ready = false;
public:
	ReservationStation input;
	LoadStore(Memory *memory, RegisterFile *register_file);
	~LoadStore();
	int tick();
	void write();
	bool flushed();
};

