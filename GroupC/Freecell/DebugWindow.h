#pragma once
#include "Shared.h"
class DebugWindow :
	public IEvent
{
private:
	bool ShowImGuiDemo = false;
public:
	bool RunEvent(double per);
};

