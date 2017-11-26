#pragma once
#include "c:\Users\gavin\workspace\Advanced-Architecture\Simulator\Simulator\include\branch_predictor.h"
enum class CounterState { Strongly_Not_Taken, Weakly_Not_Taken, Weakly_Taken, Strongly_Taken };

class SaturatingCounter :
	public BranchPredictor
{
	std::unordered_map<Instruction, CounterState> prediction_map;
public:
	SaturatingCounter();
	~SaturatingCounter();

	bool predict(Instruction instruction) override;
	bool getPrediction(Instruction instruction) override;
	void updatePrediction(Instruction instruction, bool taken) override;
};

