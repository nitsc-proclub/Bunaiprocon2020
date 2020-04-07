#pragma once
#include"Shared.h"

class BoxFloatEffect :public IEvent
{
private:
	struct RectInfo
	{
		Vec2 From;
		Vec2 To;
		double Angle;
		double RotSpd;
	};

	int RectCnt;
	Size RectSize;
	Array<RectInfo> rectinfo;
public:
	/// <summary>
	/// 箱が浮かび上がるエフェクト
	/// </summary>
	/// <param name="rectCnt">箱の数</param>
	/// <param name="rectSize">箱の大きさ</param>
	/// <param name="maxMoveY">箱の移動する高さ</param>
	/// <param name="maxRotSpd">箱の回転するスピード</param>
	BoxFloatEffect(int rectCnt, Size rectSize, int maxMoveY = 500, double maxRotSpd = 2_deg)
	{
		RectCnt = rectCnt;
		RectSize = rectSize;
		rectinfo = Array<RectInfo>(rectCnt);
		auto scRect = Scene::Rect();
		int maxR = sqrt(Pow(rectSize.x, 2) + Pow(rectSize.y, 2));
		for (int i = 0; i < rectCnt; i++)
		{
			RectInfo info;
			info.From = Vec2(maxR, scRect.h + maxR) + RandomPoint(scRect.w - maxR * 2, 0);
			info.To = info.From - RandomPoint(0, maxMoveY);
			info.Angle = 0;
			info.RotSpd = Random(-maxRotSpd, maxRotSpd);
			rectinfo[i] = info;
		}
	}

	bool RunEvent(double per)
	{
		for (int i = 0; i < RectCnt; i++)
		{
			auto rect = rectinfo[i];
			Vec2 pos = rect.From.lerp(rect.To, EaseInSine(per));
			Rect(pos.asPoint() - RectSize, RectSize).rotated(rect.Angle).drawFrame(1, Color(Palette::White, EaseOutQuint(1 - per) * 255));
			rectinfo[i].Angle += rect.RotSpd;
		}
		return true;
	}
};

