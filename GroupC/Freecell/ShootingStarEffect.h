#pragma once
#include"Shared.h"
class ShootingStarEffect :
	public IEvent
{
private:
	int starCount = 0;
	Array<Vec2> pos;
	Array<Vec2> move;
	Color starColor = Color(Palette::Yellow, 100);
public:
	ShootingStarEffect(Vec2 startPos, int starCnt, double maxXmove = 3, double maxYmove = 3)
	{
		pos = Array<Vec2>(starCnt);
		move = Array<Vec2>(starCnt);
		for (int i = 0; i < starCnt; i++)
		{
			pos[i] = startPos;
			move[i] = Vec2(maxXmove - maxXmove * 2 * Random(), maxYmove - maxYmove * 2 * Random());
		}
		starCount = starCnt;
	}

	bool RunEvent(double per)
	{
		for (int i = 0; i < starCount; i++)
		{
			Shape2D::Star(10, pos[i]).draw(starColor);
			pos[i] += move[i];
		}
		return true;
	}
};

