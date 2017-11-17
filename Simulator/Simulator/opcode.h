#pragma once
#include <unordered_set>
enum OP { DATA, IADD, IADDI, IMUL, IMULI, ICMP, LD, STR, LDI, STRI, BRA, JUM, BLT, HALTEZ, HALTEQ, NOP };

class Opcode {
public:
	std::unordered_set<uint16_t> reads;
	std::unordered_set<uint16_t> writes;
	OP op;
	Opcode(OP op) : op(op) {
		switch (op) {
		case DATA: case NOP: case BRA: case JUM:
			break;
		case IADD: case IMUL: case ICMP:
			reads.insert(1);
			reads.insert(2);
			writes.insert(0);
			break;
		case IADDI: case IMULI: case LD:
			reads.insert(1);
			writes.insert(0);
			break;
		case LDI:
			writes.insert(0);
			break;
		case STR:
			reads.insert(0);
			reads.insert(1);
			reads.insert(2);
			break;
		case STRI: case HALTEQ: case HALTEZ:
			reads.insert(0);
			break;
		case BLT:
			reads.insert(0);
			reads.insert(1);
			break;
		}
	}
};