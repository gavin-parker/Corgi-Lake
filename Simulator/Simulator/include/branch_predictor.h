#pragma once
#include "instruction.h"
#include <deque>
class BranchPredictor
{
private:
	std::deque<bool> predictions;
public:
	BranchPredictor();
	~BranchPredictor();
	bool predict(Instruction instruction);
	bool getPrediction(Instruction instruction);
	void flush();
};

