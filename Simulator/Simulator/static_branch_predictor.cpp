#include "static_branch_predictor.h"



StaticBranchPredictor::StaticBranchPredictor()
{
}


StaticBranchPredictor::~StaticBranchPredictor()
{
}

bool StaticBranchPredictor::predict(Instruction instruction)
{
	bool prediction = true;
	if (instruction.opcode.op == HALTEQ || instruction.opcode.op == HALTEZ)
	{
		return false;
	}
	return prediction;
}

bool StaticBranchPredictor::getPrediction(Instruction instruction)
{
	if (instruction.opcode.op == HALTEQ || instruction.opcode.op == HALTEZ)
	{
		return false;
	}
	return true;
}