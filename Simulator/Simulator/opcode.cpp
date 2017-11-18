#include "stdafx.h"
#include "opcode.h"
#include "opcode_settings.h"
Opcode::Opcode(OP op) : op(op), reads(op_map[op].reads), writes(op_map[op].writes), operand_num(op_map[op].operands), settings(op_map[op])
{
}
