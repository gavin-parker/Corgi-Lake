#pragma once
#include "component.h"
class LoadStore : public Component
{
public:
	LoadStore();
	~LoadStore();
	int tick();
};

