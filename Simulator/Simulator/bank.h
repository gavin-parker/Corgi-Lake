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
	std::vector<Component> members;

public:
	std::shared_ptr<ReservationStation> input = std::shared_ptr<ReservationStation>(new ReservationStation());
	std::shared_ptr<ReservationStation> output = std::shared_ptr<ReservationStation>(new ReservationStation());
	Bank(int count, std::shared_ptr<RegisterFile> register_file);
	~Bank();
	int tick() {
		for (auto member : members) {
			member.tick();
		}
	};
};

template<>
class Bank <ALU> : public Component
{
	std::vector<Component> members;
public:
	std::shared_ptr<ReservationStation> input = std::shared_ptr<ReservationStation>(new ReservationStation());
	std::shared_ptr<ReservationStation> output = std::shared_ptr<ReservationStation>(new ReservationStation());
	Bank(int count, std::shared_ptr<RegisterFile> register_file)
	{
		for (int i = 0; i < count; i++) {
			ALU alu(register_file, input, output);
			alu.state = READY;
			members.push_back(alu);
		}
	}
	int tick() {
		for (auto member : members) {
			member.tick();
		}
		return 0;
	};
};