#pragma once
#include"Shared.h"
#include"MainScene.h"
class MainWindow :public IEvent, public MainScene
{
public:
	bool RunEvent(double per);
};

