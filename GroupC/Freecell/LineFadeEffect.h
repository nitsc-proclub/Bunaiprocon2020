#pragma once
#include "Shared.h"
/// <summary>
/// ���������яオ���ď�����G�t�F�N�g
/// </summary>
class LineFadeEffect :public IEvent
{
private:
	Array<Line> lines;
public:
	/// <summary>
	/// ���������яオ���ď�����G�t�F�N�g
	/// </summary>
	/// <param name="lineCnt">���̐�</param>
	LineFadeEffect(int lineCnt);
	bool RunEvent(double per);
};

