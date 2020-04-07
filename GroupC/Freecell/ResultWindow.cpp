#include"ResultWindow.h"
#include"TitleWindow.h"

bool ResultWindow::RunEvent(double per)
{
	bool cont = true;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("ResultWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImVec2 buttonSize(120, 55);
	ImGui::SetCursorPos(ImVec2(Scene::Width() -10 - buttonSize.x, Scene::Height() - 10 - buttonSize.y));
	if (ImGui::Button((char*)u8"èIóπ", buttonSize))
	{
		Event::New(std::shared_ptr<IEvent>(new TitleWindow()), 0, 0);
		cont = false;
	}
	ImGui::End();
	Loop();
	return cont;
}