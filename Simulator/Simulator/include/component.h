#pragma once
#include "state.h"
class Component
{
protected:
	int wait_cycles = 0;
public:
	State state = DONE;
	Component();
	virtual ~Component();
	virtual int tick() {
		return 0;
	};
};

