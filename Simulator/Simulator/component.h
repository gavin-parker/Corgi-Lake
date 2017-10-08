#pragma once
class Component
{
protected:
	int state = 0;
	int wait_cycles = 0;
public:
	Component();
	~Component();
	virtual void tick();
};

