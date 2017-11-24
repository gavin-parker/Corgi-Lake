#include "stdafx.h"
#include "buffer.h"
#include <algorithm>
#include <cassert>
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
	queue.clear();
}

size_t Buffer::find_hazard(const Instruction instruction) {
	auto i = 1;
	auto nops = 0;
	for (auto it = queue.rbegin(); it != queue.rend() && i < 4; ++it) {
		if (it->isHazard(instruction)) {
			const auto instruction_ticks = it->opcode.settings.ticks;
			nops = std::max(nops, instruction_ticks - i);
		}
		i++;
	}
	return nops;
}

size_t Buffer::size()
{
	return queue.size();
}

/**
 * \brief Finds the sequential number of cycles until a buffer finishes executing.
 * \return 
 */
size_t Buffer::completion_time()
{
	auto total = 0;
	for (auto it = queue.rbegin(); it != queue.rend(); ++it) {
		total += it->opcode.settings.ticks;
		total += pipeline_lengths[it->opcode.settings.unit];
	}
	return total;
}
