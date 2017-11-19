#include "stdafx.h"
#include "branch_predictor.h"


BranchPredictor::BranchPredictor()
{
}


BranchPredictor::~BranchPredictor()
{
}

bool BranchPredictor::predict(Instruction instruction)
{
	bool prediction = true;
	if (instruction.opcode.op == HALTEZ || instruction.opcode.op == HALTEQ) {
		prediction = false;
	}
	predictions.push_back(prediction);
	return true;
}

bool BranchPredictor::getPrediction(Instruction instruction)
{
	bool wasTaken = predictions.front();
	predictions.pop_front();
	return wasTaken;
}
