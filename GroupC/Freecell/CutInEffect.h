#pragma once
#include"Shared.h"

class CutInEffect :public IEvent
{
private:
	Vec2 beginPos;
	Vec2 centerPos;
	Vec2 endPos;
	Texture imageTex;
	double centerPer;
public:
	CutInEffect(Image img, double center = 0.5)
	{
		imageTex = Texture(img);
		centerPer = center;
		int y = Scene::Center().y - img.height() / 2;
		beginPos = Vec2(-img.width(), y);
		centerPos = Vec2(Scene::Center().x - img.width() / 2, y);
		endPos = Vec2(Scene::Size().x - 1, y);
	}

	bool RunEvent(double per)
	{
		double p = (1 - centerPer) / 2;
		if (per <= p)
		{
			//ì¸èÍ
			Vec2 pos = beginPos.lerp(centerPos, EaseInQuint(per / p));
			Circle(beginPos, 30).draw();
			imageTex.draw(pos);
		}
		else if (per > centerPer + p)
		{
			//ëﬁèÍ
			Vec2 pos = centerPos.lerp(endPos, EaseOutQuint((per - centerPer - p) / p));
			imageTex.draw(pos);
		}
		else
		{
			//ë“ã@
			imageTex.draw(centerPos);
		}
		return true;
	}
};

