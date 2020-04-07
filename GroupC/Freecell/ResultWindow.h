#pragma once
#include"Shared.h"
#include"ResultScene.h"

class ResultWindow :public IEvent, public ResultScene
{
public:
	bool RunEvent(double per);
};