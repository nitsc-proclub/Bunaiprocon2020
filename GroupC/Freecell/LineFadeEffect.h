#pragma once
#include "Shared.h"
/// <summary>
/// 線が浮かび上がって消えるエフェクト
/// </summary>
class LineFadeEffect :public IEvent
{
private:
	Array<Line> lines;
public:
	/// <summary>
	/// 線が浮かび上がって消えるエフェクト
	/// </summary>
	/// <param name="lineCnt">線の数</param>
	LineFadeEffect(int lineCnt);
	bool RunEvent(double per);
};

