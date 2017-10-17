#pragma once
#include "component.h"
#include "memory.h"
#include "register_file.h"
class Fetcher : public Component
{
private:
	Memory *memory;
	RegisterFile *register_file;
public:
	Fetcher(Memory* memory, RegisterFile* register_file);
	~Fetcher();
	int tick();
};

