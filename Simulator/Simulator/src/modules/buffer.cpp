
#include "../../include/buffer.h"

Buffer::Buffer()
= default;

Buffer::~Buffer()
= default;

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
	return (queue.empty());
}

void Buffer::flush()
{
	queue.clear();
}

size_t Buffer::size()
{
	return queue.size();
}