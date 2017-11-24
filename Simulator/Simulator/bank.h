#pragma once
#include "component.h"
#include "alu.h"
#include "simulator_state.h"
#include <vector>
#include <type_traits>
#include <algorithm>

template <class T>
class Bank :
	public Component
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

public:
	int tick() {};
};

template<>
class Bank <ALU> : public Component
{
	std::vector<ALU> members;
public:
	std::shared_ptr<Buffer> input = std::make_shared<Buffer>();
	std::shared_ptr<std::deque<Result>> output = std::make_shared<std::deque<Result>>();
	Bank(int count, SimState* simState)
	{
		members.reserve(count);
		for (int i = 0; i < count; i++) {
			members.emplace_back(simState, input, output);
			members[i].state = READY;
		}
	}
	int tick() {
		for (auto &member : members) {
			member.tick();
		}
		return 0;
	};
	bool isExecuting() {
		for (auto &member : members) {
			if (member.state == EXECUTING) {
				return true;
			}
		}
		return false;
	}
	void flush() {
		for (auto &member : members) {
			member.flush();
		}
	}
	void write() {
		for (auto &member : members) {
			member.write();
		}
	}
	bool flushed() {
		if (!input->isEmpty()) {
			return false;
		}
		if (output->size() > 0) {
			return false;
		}
		for (auto &member : members) {
			if (member.state == EXECUTING  || member.result_ready) {
				return false;
			}
		}
		return true;
	}
	/*Determine if the ALU pipeline contains a hazard.
	  Hazards found in input pipeline and in the execution unit.
	  Return number of required NOPs*/
	size_t find_hazard(const Instruction other) const
	{
		const int input_nops = input->find_hazard(other);
		//Check if a result is waiting to be written back
		return input_nops;
	}
};