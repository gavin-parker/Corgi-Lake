#pragma once
#include "component.h"
#include "alu.h"
#include "simulator_state.h"
#include <vector>
#include <type_traits>

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
	std::shared_ptr<Buffer<Instruction>> input = std::make_shared<Buffer<Instruction>>();
	std::shared_ptr<Buffer<Result>> output = std::make_shared<Buffer<Result>>();
	Bank(int count, SimState* simState)
	{
		members.reserve(count);
		for (int i = 0; i < count; i++) {
			members.emplace_back(simState, input, output);
			members[i].state = READY;
		}
		simState->output_buffers.push_back(*output);
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
			member.state = READY;
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
		if (!output->isEmpty()) {
			return false;
		}
		for (auto &member : members) {
			if (member.state == EXECUTING) {
				return false;
			}
		}
		return true;
	}
	/*Determine if the ALU pipeline contains a hazard.
	  Hazards found in input pipeline and in the execution unit.*/
	bool containsHazard(Instruction other) {
		if (input->containsHazard(other)) {
			return true;
		}
		for (auto &member : members) {
			if (member.state == EXECUTING && member.current_instruction.isHazard(other)) {
				return true;
			}
		}
		return false;
	}
};