#include "stdafx.h"
#include "buffer.h"

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

void Buffer::push(Instruction item)
{
	queue.push_back(item);
}
Instruction Buffer::pop()
{
	Instruction ret = queue.front();
	queue.pop_front();
	return ret;
}

bool Buffer::isEmpty()
{
	return (queue.size() == 0);
}

void Buffer::flush()
{
	queue.empty();
}

size_t Buffer::findHazard(Instruction instruction) {
	int i = 1;
	for (auto it = queue.rbegin(); it != queue.rend() && i < 4; ++it) {
		if (it->isHazard(instruction)) {
			int pipeline_length = 3;
			int instruction_ticks = it->opcode.settings.ticks;
			int completion_time = pipeline_length +instruction_ticks;
			return completion_time - i;
		}
		i++;
	}
	return 0;
}