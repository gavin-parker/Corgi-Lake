#include "../../include/stdafx.h"
#include "../../include/opcode.h"
#include "../../include/opcode_settings.h"
#include <algorithm>

Opcode::Opcode(OP op) : op(op), reads(op_map[op].reads), writes(op_map[op].writes), operand_num(op_map[op].operands), settings(op_map[op]), reg_args(std::unordered_set<uint16_t>())
{
	for(auto read : reads)
	{
		reg_args.insert(read);
	}
	for(auto write : writes)
	{
		reg_args.insert(write);
	}

}
