#include "../include/static_branch_predictor.h"



StaticBranchPredictor::StaticBranchPredictor()
= default;


StaticBranchPredictor::~StaticBranchPredictor()
= default;

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
	return !(instruction.opcode.op == HALTEQ || instruction.opcode.op == HALTEZ);
}