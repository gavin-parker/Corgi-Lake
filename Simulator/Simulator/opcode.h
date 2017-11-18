#pragma once
#include <unordered_set>
#include <unordered_map>
enum OP { DATA, IADD, IADDI, IMUL, IMULI, ICMP, LD, STR, LDI, STRI, BRA, JUM, BLT, HALTEZ, HALTEQ, NOP, ISUB };
enum UNIT { MATH, LDSTR, BRANCH, SKIP };

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
	OP op;
	int operand_num;
	Opcode(OP op) ;
	OP_SETTINGS settings;
};