#include"MainWindow.h"
#include"KeyConfigWindow.h"
#include"ResultWindow.h"
#include"DQLikeMessBox.h"
#include"imgui_impl_s3d.h"
#include"MarkdownViewWindow.h"

bool MainWindow::RunEvent(double per)
{
	bool cont = true;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("MainWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu((char*)u8"ÉLÅ[ê›íË"))
		{
			if (ImGui::MenuItem("1P", ""))
			{
				std::shared_ptr<IEvent> window(new KeyConfigWindow(&(ControllerCfgs[0])));
				Event::New(window, 0, 0);
			}
			if (ImGui::MenuItem("2P", ""))
			{
				std::shared_ptr<IEvent> window(new KeyConfigWindow(&(ControllerCfgs[1])));
				Event::New(window, 0, 0);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu((char*)u8"ÉwÉãÉv"))
		{
			if (ImGui::MenuItem((char*)u8"óVÇ—ï˚", ""))
			{
				Event::New(std::shared_ptr<IEvent>(new MarkdownViewWindow(U"HowToUse/Index.md")));
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	ImGui::End();

	cont = cont && Loop();
	return cont;
}