#include "TestSkill.h"

TestSkill::TestSkill()
{
	SkillImage = Texture(U"Assets/TNTImage.png");
	GuageMax = 3;
}

void TestSkill::Init(Array<TeamState>* teamStates, int myTeam)
{

}

void TestSkill::Run(Array<TeamState>* teamStates, int myTeam) 
{
	int enemyTeam = !myTeam;
	auto myState = &((*teamStates)[myTeam]);
	auto enemyState = &((*teamStates)[enemyTeam]);
	auto gridSize = myState->NodeStates.size();
	for (int i = 0; i < 1; i++)
	{
		bool fail;
		do
		{
			fail = false;
			Point pos = RandomPoint(Rect(0, 0, gridSize));
			auto state = &(myState->NodeStates.at(pos));
			auto estate = &(enemyState->NodeStates.at(pos));
			if (RandomBool())
			{
				if(state->Bottom)
				{
					state->Bottom = false;
					estate->Bottom = false;
				}
				else
				{
					fail = true;
				}
			}
			else
			{
				if (state->Right)
				{
					state->Right = false;
					estate->Right = false;
				}
				else
				{
					fail = true;
				}
			}
		} while (fail);
	}
}
