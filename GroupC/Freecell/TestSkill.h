#pragma once
#include "Shared.h"

class TestSkill : public ISkill
{
public:
	TestSkill();
	void Init(Array<TeamState>* teamStates, int myTeam) override;
	void Run(Array<TeamState>* teamStates, int myTeam) override;
};