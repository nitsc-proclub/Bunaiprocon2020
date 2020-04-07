#include "LineFadeEffect.h"

Vec2 GetRandomPos()
{
	Rect rect = Scene::Rect();
	return RandomBool() ?
		Vec2(Random(0, rect.w - 1), RandomBool() ? 0 : rect.h - 1) :
		Vec2(RandomBool() ? 0 : rect.w - 1, Random(0, rect.h - 1));
}

LineFadeEffect::LineFadeEffect(int lineCnt)
{
	lines = Array<Line>(lineCnt);
	for (int i = 0; i < lineCnt; i++)
	{
		Line line;
		line.begin = GetRandomPos();
		do
		{
			line.end = GetRandomPos();
		} while (line.begin.x == line.end.x || line.begin.y == line.end.y);
		lines[i] = line;
	}
}

bool LineFadeEffect::RunEvent(double per)
{
	Color col;
	if (per < 0.5)
	{
		col = Color(Palette::White, 255 * per / 0.5);
	}
	else
	{
		col = Color(Palette::White, 255 * (1 - per) / 0.5);
	}
	for (const auto line : lines)
	{
		line.draw(col);
	}
	return true;
}
