#pragma once
#include <queue>
#include "memory.h"
template <class T>
class Buffer
{
private:
	std::queue<T> queue;
public:
	Buffer();
	~Buffer();
	void push(T item);
	T pop();
	bool isEmpty();
	void flush();
};
template <class T>
Buffer<T>::Buffer()
{
}

template <class T>
Buffer<T>::~Buffer()
{
}

template <class T>
void Buffer<T>::push(T item)
{
	queue.push(item);
}
template <class T>
T Buffer<T>::pop()
{
	T ret = queue.front();
	queue.pop();
	return ret;
}

template <class T>
bool Buffer<T>::isEmpty()
{
	return (queue.size() == 0);
}

template <class T>
void Buffer<T>::flush()
{
	queue.empty();
}
