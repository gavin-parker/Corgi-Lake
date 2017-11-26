#include "saturating_counter.h"



SaturatingCounter::SaturatingCounter()
{
}


SaturatingCounter::~SaturatingCounter()
{
}

CounterState iterate(CounterState state, bool taken )
{
	switch (state) { 
	case CounterState::Strongly_Not_Taken:
		if (taken) return CounterState::Weakly_Not_Taken;
		break;
	case CounterState::Weakly_Not_Taken:
		if (taken) return CounterState::Weakly_Taken;
		return CounterState::Strongly_Not_Taken;
		break;
	case CounterState::Weakly_Taken:
		if (taken) return CounterState::Strongly_Taken;
		return CounterState::Weakly_Not_Taken;
		break;
	case CounterState::Strongly_Taken:
		if (!taken) return CounterState::Weakly_Taken;
		break;
	}
	return state;
}

bool SaturatingCounter::predict(const Instruction instruction)
{
	if(instruction.opcode.op == HALTEZ || instruction.opcode.op == HALTEQ)
	{
		return false;
	}
	if(prediction_map.find(instruction) == prediction_map.end())
	{
		prediction_map[instruction] = CounterState::Weakly_Taken;
	}else
	{
		return getPrediction(instruction);
	}
	return true;
}

bool SaturatingCounter::getPrediction(Instruction instruction)
{
	if (instruction.opcode.op == HALTEZ || instruction.opcode.op == HALTEQ)
	{
		return false;
	}
	const CounterState state = prediction_map[instruction];
	switch (state) { case CounterState::Strongly_Not_Taken:
	case CounterState::Weakly_Not_Taken:
		return false;
	case CounterState::Weakly_Taken:
	case CounterState::Strongly_Taken:
		return true;
	}
}

void SaturatingCounter::updatePrediction(Instruction instruction, bool taken)
{
	prediction_map[instruction] = iterate(prediction_map[instruction], taken);
}
 