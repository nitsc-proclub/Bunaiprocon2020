#include "DebugWindow.h"

bool DebugWindow::RunEvent(double per)
{
	bool cont = true;
	ImGui::SetNextWindowSize(ImVec2(300, 400));
	ImGui::Begin((char*)u8"Debug", &cont, ImGuiWindowFlags_None);
	if (ImGui::CollapsingHeader((char*)u8"Controller"))
	{
		for (int i = 0; i < ControllerCfgs.size(); i++)
		{
			auto conf = ControllerCfgs[i];
			ImGui::Text((U"{}"_fmt(i)).toUTF8().c_str());
			ImGui::BulletText((U"Index:{}"_fmt(conf.Index)).toUTF8().c_str());
			ImGui::BulletText((U"Pov:{}"_fmt(conf.Pov)).toUTF8().c_str());
			ImGui::BulletText((U"PreviousPov:{}"_fmt(conf.PreviousPov)).toUTF8().c_str());
			ImGui::BulletText((U"Select:{}"_fmt(conf.Select.pressed())).toUTF8().c_str());
			ImGui::BulletText((U"SelectId:{}"_fmt(conf.SelectId)).toUTF8().c_str());
			ImGui::BulletText((U"Cancel:{}"_fmt(conf.Cancel.pressed())).toUTF8().c_str());
			ImGui::BulletText((U"CancelId:{}"_fmt(conf.CancelId)).toUTF8().c_str());
			ImGui::BulletText((U"L:{}"_fmt(conf.L.pressed())).toUTF8().c_str());
			ImGui::BulletText((U"LId:{}"_fmt(conf.LId)).toUTF8().c_str());
			ImGui::BulletText((U"R:{}"_fmt(conf.R.pressed())).toUTF8().c_str());
			ImGui::BulletText((U"RId:{}"_fmt(conf.RId)).toUTF8().c_str());
		}
	}
	if (ImGui::CollapsingHeader((char*)u8"Event"))
	{
		ImGui::Text((U"BackEvents:{}"_fmt(Event::GetEventCnt(Background))).toUTF8().c_str());
		ImGui::Text((U"NomalEvents:{}"_fmt(Event::GetEventCnt(Nomal))).toUTF8().c_str());
		ImGui::Text((U"ForeEvents:{}"_fmt(Event::GetEventCnt(Foreground))).toUTF8().c_str());
	}
	if (ImGui::CollapsingHeader((char*)u8"Sound"))
	{
		ImGui::Text((U"PlayingBGM:" + Sound::GetPlayingBGM()).toUTF8().c_str());
	}
	ImGui::Checkbox((char*)u8"Demo", &ShowImGuiDemo);
	ImGui::End();
	if (ShowImGuiDemo)
	{
		ImGui::ShowDemoWindow(&ShowImGuiDemo);
	}
	return cont;
}
