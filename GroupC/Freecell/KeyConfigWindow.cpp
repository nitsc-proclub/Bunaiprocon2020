#include "KeyConfigWindow.h"

void KeyConfigWindow::UpdateControllers()
{
	controller->Index = 0;
	controllerNames.clear();
	controllerNames.push_back(String(U"ソフトコントローラー").toUTF8());
	for (const auto& info : System::EnumerateGamepads())
	{
		controllerNames.push_back(U"[{}] {}"_fmt(info.index, info.name).narrow());
	}
	confButton = ConfButton::None;
}

KeyConfigWindow::KeyConfigWindow()
{
}

KeyConfigWindow::KeyConfigWindow(Controller* ctrl)
{
	controller = ctrl;
	UpdateControllers();
}

void KeyConfigWindow::ShowChildWindow()
{
	ShowAsChild = true;
	RunEvent(0);
	ShowAsChild = false;
}

bool KeyConfigWindow::RunEvent(double per)
{
	bool cont = true;
	auto windowTitle = U"コントローラーを選択##{}"_fmt(this).toUTF8();
	if (ShowAsChild)
	{
		ImGui::BeginChild(windowTitle.c_str(), WindowSize,true);
		ImGui::Text((char*)u8"コントローラーを選択");
		ImGui::Separator();
	}
	else
	{
		ImGui::SetNextWindowSize(WindowSize);
		ImGui::Begin(windowTitle.c_str(), (bool*)0, ImGuiWindowFlags_NoResize);
	}
	if (controllerNames.size() == 0)
	{
		ImGui::Text((char*)u8"使えるコントローラーがありません");
	}
	else
	{
		if (ImGui::BeginCombo("", controllerNames[controller->Index].c_str()))
		{
			for (int i = 0; i < controllerNames.size(); i++)
			{
				if (ImGui::Selectable(controllerNames[i].c_str()))
				{
					controller->Index = i;
				}
				if (controller->Index == i)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
	ImGui::SameLine();
	if (ImGui::Button((char*)u8"更新"))
	{
		UpdateControllers();
	}
	if (controller->Index == 0)
	{

	}
	else
	{
		auto gamepad = Gamepad(controller->Index - 1);
		if (!JoyCon::IsJoyCon(gamepad) && !ProController::IsProController(gamepad))
		{
			ImGui::BeginGroup();
			ImGui::Text((char*)u8"キーコンフィグ");
			ImGui::Text((char*)u8"Select:");
			ImGui::SameLine();
			if (confButton == Select)
			{
				if (ImGui::Button((char*)u8"ボタンを押してください"))
				{
					confButton = None;
				}
			}
			else
			{
				if (ImGui::Button(U"button{}"_fmt(controller->SelectId).narrow().c_str()))
				{
					confButton = Select;
				}
			}
			ImGui::Text((char*)u8"Cancel:");
			ImGui::SameLine();
			if (confButton == Cancel)
			{
				if (ImGui::Button((char*)u8"ボタンを押してください"))
				{
					confButton = None;
				}
			}
			else
			{
				if (ImGui::Button(U"button{}"_fmt(controller->CancelId).narrow().c_str()))
				{
					confButton = Cancel;
				}
			}
			ImGui::Text((char*)u8"L:");
			ImGui::SameLine();
			if (confButton == L)
			{
				if (ImGui::Button((char*)u8"ボタンを押してください"))
				{
					confButton = None;
				}
			}
			else
			{
				if (ImGui::Button(U"button{}"_fmt(controller->LId).narrow().c_str()))
				{
					confButton = L;
				}
			}
			ImGui::Text((char*)u8"R:");
			ImGui::SameLine();
			if (confButton == R)
			{
				if (ImGui::Button((char*)u8"ボタンを押してください"))
				{
					confButton = None;
				}
			}
			else
			{
				if (ImGui::Button(U"button{}"_fmt(controller->RId).narrow().c_str()))
				{
					confButton = R;
				}
			}
			ImGui::EndGroup();
		}
		if (confButton != None)
		{
			for (int i = 0; i < gamepad.buttons.size(); i++)
			{
				if (gamepad.buttons[i].down())
				{
					switch (confButton)
					{
					case Select:
						controller->SelectId = i;
						break;
					case Cancel:
						controller->CancelId = i;
						break;
					case L:
						controller->LId = i;
						break;
					case R:
						controller->RId = i;
						break;
					}
					confButton = None;
					break;
				}
			}
		}
	}
	if (ShowAsChild)
	{
		ImGui::EndChild();
	}
	else
	{
		if (ImGui::Button("OK"))
		{
			cont = false;
		}
		ImGui::End();
	}
	return cont;
}