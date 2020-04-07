#pragma once
#include"Shared.h"

class KeyConfigWindow :
	public IEvent
{
private:
	enum ConfButton
	{
		None, Select, Cancel, L, R
	};
	const ImVec2 WindowSize = ImVec2(300, 250);
	Array<std::string> controllerNames;
	Controller* controller;
	ConfButton confButton;
	bool ShowAsChild = false;
	void UpdateControllers();
public:
	KeyConfigWindow();
	KeyConfigWindow(Controller* ctrl);
	void ShowChildWindow();
	bool RunEvent(double per);
};