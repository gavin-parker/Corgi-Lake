#include "../../include/stdafx.h"
#include "../../include/branch_predictor.h"


BranchPredictor::BranchPredictor()
{
}


BranchPredictor::~BranchPredictor()
{
}

bool BranchPredictor::predict(Instruction instruction)
{
	bool prediction = true;
	if (instruction.opcode.op == HALTEQ || instruction.opcode.op == HALTEZ)
	{
		return false;
	}
	return prediction;
}

bool BranchPredictor::getPrediction(Instruction instruction)
{
	if(instruction.opcode.op == HALTEQ || instruction.opcode.op == HALTEZ)
	{
		return false;
	}
	return true;
}

void BranchPredictor::flush()
{
	predictions.clear();
}
