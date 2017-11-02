#pragma once
#include "component.h"
#include "alu.h"
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
	std::shared_ptr<ReservationStation> input = std::make_shared<ReservationStation>();
	std::shared_ptr<ReservationStation> output = std::make_shared<ReservationStation>();
	Bank(int count, RegisterFile* register_file)
	{
		members.reserve(count);
		for (int i = 0; i < count; i++) {
			members.emplace_back(register_file, input, output);
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
			member.state = READY;
		}
	}

};