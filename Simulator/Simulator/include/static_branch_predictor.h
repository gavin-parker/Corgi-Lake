#pragma once
#include "branch_predictor.h"
class StaticBranchPredictor :
	public BranchPredictor
{
public:
	StaticBranchPredictor();
	~StaticBranchPredictor();
	bool predict(Instruction instruction) override;
	bool getPrediction(Instruction instruction) override;
};

