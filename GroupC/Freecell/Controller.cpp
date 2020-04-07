#include"Controller.h"
#include"KeyConfigWindow.h"

//コントローラー設定
Array<Controller> ControllerCfgs = { Controller(),Controller() };
Controller::PovDirection SoftPov = Controller::PovDirection::None;
bool Controller::CanShowSoftKey = false;
bool SoftSelect = false;
bool SoftCancel = false;
bool SoftL = false;
bool SoftR = false;

void DrawSoftKey()
{
	ImGui::SetNextWindowBgAlpha(0.4f);
	ImGui::Begin((char*)u8"SoftKeyWindow", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
	ImGui::Text((char*)u8"Gamepad");
	ImGui::Separator();
	if (ImGui::Button("L", ImVec2(50, 25)))
	{
		SoftL = true;
	}
	else
	{
		SoftL = false;
	}
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(50, 25));
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(50, 25));
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(50, 25));
	ImGui::SameLine();
	if (ImGui::Button("R", ImVec2(50, 25)))
	{
		SoftR = true;
	}
	else
	{
		SoftR = false;
	}
	ImGui::Dummy(ImVec2(50, 50));
	ImGui::SameLine();
	SoftPov = Controller::PovDirection::None;
	if (ImGui::Button((char*)u8"｜##0", ImVec2(50, 50)))
	{
		SoftPov = Controller::PovDirection::Up;
	}
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(50, 50));
	if (ImGui::Button((char*)u8"ー##1", ImVec2(50, 50)))
	{
		SoftPov = Controller::PovDirection::Left;
	}
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(50, 50));
	ImGui::SameLine();
	if (ImGui::Button((char*)u8"ー##2", ImVec2(50, 50)))
	{
		SoftPov = Controller::PovDirection::Right;
	}
	ImGui::Dummy(ImVec2(50, 50));
	ImGui::SameLine();
	if (ImGui::Button((char*)u8"｜##3", ImVec2(50, 50)))
	{
		SoftPov = Controller::PovDirection::Down;
	}
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(50, 50));
	ImGui::SameLine();
	if (ImGui::Button((char*)u8"Cancel", ImVec2(50, 50)))
	{
		SoftCancel = true;
	}
	else
	{
		SoftCancel = false;
	}
	ImGui::SameLine();
	if (ImGui::Button((char*)u8"Select", ImVec2(50, 50)))
	{
		SoftSelect = true;
	}
	else
	{
		SoftSelect = false;
	}
	auto windowSize = ImGui::GetWindowSize();
	ImGui::End();
	if (windowSize.x != 32 && windowSize.y != 32)ImGui::SetWindowPos((char*)u8"SoftKeyWindow", ImVec2(30, Scene::Height() - windowSize.y - 30), ImGuiCond_Once);
}

void Controller::Update()
{
	if (Index == 0)
	{
		PreviousPov = Pov;
		Pov = SoftPov;
		Select.updateState(SoftSelect);
		Cancel.updateState(SoftCancel);
		L.updateState(SoftL);
		R.updateState(SoftR);
		return;
	}
	else
	{
		auto controller = Gamepad(Index - 1);

		Optional<int32> PovValue;

		if (JoyCon::IsJoyCon(controller))
		{
			auto joycon = JoyCon(controller);

			PovValue = Optional<int32>(joycon.povD8());
			Select = VirtualKey(joycon.button1);
			Cancel = VirtualKey(joycon.button0);
			L = VirtualKey(joycon.buttonSL);
			R = VirtualKey(joycon.buttonSR);
		}
		else if (ProController::IsProController(controller))
		{
			auto procon = ProController(controller);
			PovValue = Optional<int32>(procon.povD8());
			Select = VirtualKey(procon.buttonA);
			Cancel = VirtualKey(procon.buttonB);
			L = VirtualKey(procon.buttonL);
			R = VirtualKey(procon.buttonR);
		}
		else
		{
			PovValue = Optional<int32>(controller.povD8());
			Select = SelectId < controller.buttons.size() ? VirtualKey(controller.buttons[SelectId]) : VirtualKey();
			Cancel = CancelId < controller.buttons.size() ? VirtualKey(controller.buttons[CancelId]) : VirtualKey();
			L = LId < controller.buttons.size() ? VirtualKey(controller.buttons[LId]) : VirtualKey();
			R = RId < controller.buttons.size() ? VirtualKey(controller.buttons[RId]) : VirtualKey();
		}
		PreviousPov = Pov;
		if (PovValue)
		{
			Pov = (PovDirection)*PovValue;
		}
		else
		{
			Pov = None;
		}
	}
}

void UpdateControllers()
{
	bool softKey = true;
	for (int i = 0; i < ControllerCfgs.size(); i++)
	{
		auto config = &ControllerCfgs[i];
		if (softKey && config->Index == 0)
		{
			if (Controller::CanShowSoftKey)
			{
				DrawSoftKey();
			}
			softKey = false;
		}
		config->Update();
	}
}

VirtualKey::VirtualKey()
{
	from = Virtual;
}

VirtualKey::VirtualKey(Key key)
{
	from = Real;
	real = key;
}

void VirtualKey::updateState(bool pressed)
{
	from = Virtual;
	if (isFirst)
	{
		isFirst = false;
		_pressed = pressed;
		return;
	}
	_down = false;
	_up = false;
	if (pressed != _pressed)
	{
		if (pressed)
		{
			_down = true;
		}
		else
		{
			_up = true;
		}
	}
	_pressed = pressed;
}

bool VirtualKey::down()
{
	switch (from)
	{
	case VirtualKey::Real:
		return real.down();
	case VirtualKey::Virtual:
		return _down;
	}
}

bool VirtualKey::pressed()
{
	switch (from)
	{
	case VirtualKey::Real:
		return real.pressed();
	case VirtualKey::Virtual:
		return _pressed;
	}
}

bool VirtualKey::up()
{
	switch (from)
	{
	case VirtualKey::Real:
		return real.up();
	case VirtualKey::Virtual:
		return _up;
	}
}

