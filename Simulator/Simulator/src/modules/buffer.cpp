#include "../../include/stdafx.h"
#include "../../include/buffer.h"
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

void Buffer::push_front(Instruction item){
	queue.push_front(item);
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

size_t Buffer::size()
{
	return queue.size();
}