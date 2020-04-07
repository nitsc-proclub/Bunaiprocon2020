#include"ConfigWindow.h"
#include"MainWindow.h"

ConfigWindow::ConfigWindow()
{
}

bool ConfigWindow::RunEvent(double per)
{
	bool cont = true;
	ImVec2 dispSize = ImGui::GetIO().DisplaySize;
	ImVec2 windowSize = ImVec2(dispSize);
	windowSize.x = windowSize.x / 2 - 45;
	windowSize.y -= 100;
	ImGui::SetNextWindowPos(ImVec2(30, 30));
	ImGui::SetNextWindowSize(windowSize);
	ImGui::Begin((char*)u8"1P(“¦‚°‚é•û)", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);
	cfg1P.ShowChildWindow();

	ImGui::End();
	ImGui::SetNextWindowPos(ImVec2(dispSize.x/2+15, 30));
	ImGui::SetNextWindowSize(windowSize);
	ImGui::Begin((char*)u8"2P(‹S)", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);
	cfg2P.ShowChildWindow();

	ImGui::End();
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(dispSize);
	ImGui::Begin("ConfigWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImVec2 buttonSize(120, 55);
	ImGui::SetCursorPos(ImVec2(dispSize.x - 10 - buttonSize.x, dispSize.y - 10 - buttonSize.y));
	if (ImGui::Button((char*)u8"Start", buttonSize))
	{
		Event::New(std::shared_ptr<IEvent>(new MainWindow()), 0, 0);
		cont = false;
	}
	ImGui::End();

	Loop();
	return cont;
}
