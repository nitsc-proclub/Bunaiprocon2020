#include "CutInTextEffect.h"

CutInTextEffect::CutInTextEffect(String text, Font font, double center)
{
	drwFont = font(text);
	Vec2 txtSize = drwFont.region(0, 0).size;
	centerPer = center;
	int y = Scene::Center().y - txtSize.y / 2;
	beginPos = Vec2(-txtSize.x, y);
	centerPos = Vec2(Scene::Center().x - txtSize.x / 2, y);
	endPos = Vec2(Scene::Size().x - 1, y);
}

bool CutInTextEffect::RunEvent(double per)
{
	double p = (1 - centerPer) / 2;
	if (per <= p)
	{
		//ì¸èÍ
		Vec2 pos = beginPos.lerp(centerPos, EaseInQuint(per / p));
		Circle(beginPos, 30).draw();
		drwFont.draw(pos);
	}
	else if (per > centerPer + p)
	{
		//ëﬁèÍ
		Vec2 pos = centerPos.lerp(endPos, EaseOutQuint((per - centerPer - p) / p));
		drwFont.draw(pos);
	}
	else
	{
		//ë“ã@
		drwFont.draw(centerPos);
	}
	return true;
}