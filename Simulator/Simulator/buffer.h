#pragma once
#include <deque>
#include "memory.h"
#include <iostream>
template <class T>
class Buffer
{
private:
	std::deque<T> queue;
public:
	Buffer();
	~Buffer();
	void push(T item);
	T pop();
	bool isEmpty();
	void flush();
	bool containsHazard(Instruction instruction);
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
	queue.push_back(item);
}
template <class T>
T Buffer<T>::pop()
{
	T ret = queue.front();
	queue.pop_front();
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

template<class Result>
bool Buffer<Result>::containsHazard(Instruction instruction) {

	for (auto it = queue.begin(); it != queue.end(); ++it) {
		if (it->isHazard(instruction)) {
			std::cout << "RAW HAZARD DETECTED!!" << std::endl;
			return true;
		}
	}
	return false;
}