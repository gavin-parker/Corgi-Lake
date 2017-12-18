#pragma once
#include <unordered_set>
#include <unordered_map>
enum OP { DATA, IADD, IADDI, IMUL, IMULI, ICMP, LD, STR, LDI, STRI, BRA, JUM, BLT, HALTEZ, HALTEQ, NOP, ISUB, JLT, PRNT, AND, NOT };
enum UNIT { MATH, LDSTR, BRANCH, SKIP };

namespace std
{
	template<>
	struct hash<OP> {
		size_t operator()(const OP &pt) const {
			return std::hash<int>()((int)pt);
		}
	};
}

struct OP_SETTINGS {
	int ticks = 1;
	int operands = 3;
	UNIT unit;
	std::unordered_set<uint16_t> reads;
	std::unordered_set<uint16_t> writes;
	std::string name;
};

class Opcode {
public:
	std::unordered_set<uint16_t> reads;
	std::unordered_set<uint16_t> writes;
	std::unordered_set<uint16_t> reg_args;
	OP op;
	int operand_num;

	explicit Opcode(OP op) ;
	OP_SETTINGS settings;
};