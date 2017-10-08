#pragma once
#include "state.h"
class Component
{
protected:
	int wait_cycles = 0;
public:
	State state = DONE;
	Component();
	~Component();
	virtual void tick() {
		
	};

	virtual void start() {
		state = READY;
	}
};

