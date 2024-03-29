#pragma once
#include <unordered_set>
#include <unordered_map>
#include "opcode.h"

// OP TICKS OPERANDS UNIT READS WRITES NAME
std::unordered_map<OP, OP_SETTINGS> op_map = {
	{ DATA	,{ 0	,1	,SKIP		,{}			,{}		, "DATA" } },
	{ IADD	,{ 1	,3	,MATH		,{ 1,2 }	,{ 0 }	, "IADD" } },
	{ IADDI	,{ 1	,3	,MATH		,{ 1 }		,{ 0 }	, "IADDI" } },
	{ IMUL	,{ 4	,3	,MATH		,{ 1,2 }	,{ 0 }	, "IMUL" } },
	{ IMULI	,{ 4	,3	,MATH		,{ 1 }		,{ 0 }	, "IMULI" } },
	{ ICMP	,{ 1	,3	,MATH		,{ 1,2 }	,{ 0 }	, "ICMP" } },
	{ LD	,{ 1	,3	,LDSTR		,{ 1 }		,{ 0 }	, "LD" } },
	{ STR	,{ 1	,3	,LDSTR		,{ 0,1,2 }	,{}		, "STR" } },
	{ LDI	,{ 1	,2	,LDSTR		,{}			,{ 0 }	, "LDI" } },
	{ STRI	,{ 1	,2	,LDSTR		,{ 0 }		,{}		, "STRI" } },
	{ BRA	,{ 1	,1	,BRANCH		,{}			,{}		, "BRA" } },
	{ JUM	,{ 1	,1	,BRANCH		,{0}		,{}		, "JUM" } },
	{ BLT	,{ 1	,3	,BRANCH		,{ 0,1 }	,{}		, "BLT" } },
	{ HALTEZ,{ 1	,1	,BRANCH		,{ 0 }		,{}		, "HALTEZ" } },
	{ HALTEQ,{1		,2	,BRANCH		,{ 0 }		,{}		, "HALTEQ" } },
	{ NOP	,{1		,0	,SKIP		,{}			,{}		, "NOP"}},
	{ ISUB	,{1		,3	,MATH		,{1,2}		,{0}	, "ISUB"}},
	{ JLT	,{ 1	,3	,BRANCH		,{ 0,1 }	,{}		, "JLT" }},
    { PRNT	,{ 1	,1	,MATH		,{ 0 }	,{}		    , "PRNT" }},
    { AND	,{ 1	,3	,MATH		,{ 1,2 }	,{ 0 }	, "AND" } },
    { NOT	,{ 1	,2	,MATH		,{ 1 }	,{ 0 }	, "NOT" } }
};