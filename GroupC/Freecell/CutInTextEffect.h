#pragma once
#include "EventMgr.h"
class CutInTextEffect :
	public IEvent
{
private:
	Vec2 beginPos;
	Vec2 centerPos;
	Vec2 endPos;
	double centerPer;
	DrawableText drwFont;
public:
	CutInTextEffect(String text, Font font, double center = 0.5);
	bool RunEvent(double per);
};