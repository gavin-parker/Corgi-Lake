#pragma once
#include "instruction.h"
#include <deque>
class BranchPredictor
{
private:
public:
	BranchPredictor();

	virtual ~BranchPredictor();
	virtual bool predict(Instruction instruction) = 0;
	virtual bool getPrediction(Instruction instruction) = 0;
	virtual void updatePrediction(Instruction instruction, bool taken){};
};

