#include <utility>


#include "../../include/memory.h"


Memory::Memory(std::vector<Data> program) : main_memory(std::move(program))
{
}


Memory::~Memory()
= default;

int Memory::tick() {
	switch (state) {
	case READY:
		wait_cycles = 1;
		state = EXECUTING;
		break;
	case EXECUTING:
		if (wait_cycles <= 1) {
			state = DONE;
		}
		else {
			wait_cycles--;
		}
		break;
	case DONE:
		break;
	}
	return 0;
}