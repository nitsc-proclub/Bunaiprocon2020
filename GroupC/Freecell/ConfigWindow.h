#pragma once
#include"Shared.h"
#include"ConfigScene.h"
#include"KeyConfigWindow.h"

class ConfigWindow :public IEvent, public ConfigScene
{
private:
	KeyConfigWindow cfg1P = KeyConfigWindow((Controller*)&(ControllerCfgs[0]));
	KeyConfigWindow cfg2P = KeyConfigWindow((Controller*)&(ControllerCfgs[1]));

public:
	ConfigWindow();
	bool RunEvent(double per);
};