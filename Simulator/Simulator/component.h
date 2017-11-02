#pragma once
#include "state.h"
#include "non_copyable.h"
class Component //: public NonCopyable
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

	virtual void start() {
		state = READY;
	}
};

