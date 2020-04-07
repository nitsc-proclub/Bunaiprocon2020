#pragma once
#include"Shared.h"

struct VirtualKey
{
private:
	enum InputFrom
	{
		Real, Virtual
	};
	InputFrom from;
	Key real;
	bool isFirst = true;
	bool _down = false;
	bool _pressed = false;
	bool _up = false;
public:
	VirtualKey();
	VirtualKey(Key key);
	void updateState(bool stat);
	bool down();
	bool pressed();
	bool up();
};

class Controller
{
public:
	enum PovDirection
	{
		None = -1,
		Up,
		RightTop,
		Right,
		RightDown,
		Down,
		LeftDown,
		Left,
		LeftTop,
	};
	int Index = 0;
	PovDirection Pov = None;
	PovDirection PreviousPov = None;
	VirtualKey Select;
	int SelectId = 1;
	VirtualKey Cancel;
	int CancelId = 2;
	VirtualKey L;
	int LId = 5;
	VirtualKey R;
	int RId = 6;
	void Update();
	static bool CanShowSoftKey;
};

/// <summary>
/// ControllerCfgsÇÃèÓïÒÇçXêV
/// </summary>
void UpdateControllers();

extern Array<Controller> ControllerCfgs;