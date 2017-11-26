#pragma once
#include "c:\Users\gavin\workspace\Advanced-Architecture\Simulator\Simulator\include\branch_predictor.h"
class StaticBranchPredictor :
	public BranchPredictor
{
public:
	StaticBranchPredictor();
	~StaticBranchPredictor();
	bool predict(Instruction instruction) override;
	bool getPrediction(Instruction instruction) override;
};

