#include"TitleWindow.h"
#include"ConfigWindow.h"
#include"MarkdownViewWindow.h"

bool TitleWindow::RunEvent(double per)
{
	bool cont = true;
	//Scene::Rect().draw(Palette::Black);
	font(Title).drawAt(Scene::Center() + Vec2(5, 5), Palette::Darkgray);
	font(Title).drawAt(Scene::Center(), Palette::White);
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("TitleWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImVec2 nextbutton(250,80);
	ImGui::SetCursorPos(ImVec2(ImGui::GetIO().DisplaySize.x /2 - nextbutton.x / 2, ImGui::GetIO().DisplaySize.y / 2 + 100));
	if (ImGui::Button((char*)u8"ŽŸ‚Ö", nextbutton))
	{
		Event::New(std::shared_ptr<IEvent>(new ConfigWindow()), 0, 0);
		cont = false;
	}

	ImVec2 tutorialbutton(250, 80);
	ImGui::SetCursorPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - tutorialbutton.x / 2, ImGui::GetIO().DisplaySize.y / 2 + 210));
	if (ImGui::Button((char*)u8"—V‚Ñ•û", tutorialbutton))
	{
		Event::New(std::shared_ptr<IEvent>(new MarkdownViewWindow(U"HowToUse/Index.md")));
	}
	ImGui::End();
	Loop();
	return cont;
}