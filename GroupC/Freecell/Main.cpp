
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

#include"Shared.h"
#include"EventMgr.h"
#include"TitleWindow.h"
#include"DebugWindow.h"
#include"ShootingStarEffect.h"

String Title = U"Endlle";

void Main()
{
	Window::SetTitle(Title);
	Window::Resize(1920, 1080);
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetScaleMode(ScaleMode::ResizeFill);
	Scene::SetBackground(Palette::Black);
	Event::Init();
	ImGui::CreateContext();
	ImGui_Impls3d_Init();
	{
		ImGuiIO& io = ImGui::GetIO();
		//メイリオのフォントを読み込み
		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 20, nullptr, io.Fonts->GetGlyphRangesJapanese());
		io.IniFilename = NULL;
	}

	Sound::New(U"BGMBad1", U"Assets/Club Game BGM - Bad.mp3");
	Sound::New(U"BGMBad2", U"Assets/Club Game BGM - Bad 2.mp3");
	Sound::New(U"BGMGood", U"Assets/Club Game BGM - Good.mp3");
	Sound::New(U"BGMIdle1", U"Assets/Club Game BGM - Idle 1.mp3");
	Sound::New(U"BGMIdle2", U"Assets/Club Game BGM - Idle 2.mp3");
	Sound::New(U"SEBeep", U"Assets/beep-reedy.mp3");
	Sound::New(U"SEBell", U"Assets/呼び出しベル.mp3");
	Sound::New(U"SEWhistle", U"Assets/whistle.mp3");

	//タイトル表示
	Event::New(std::shared_ptr<IEvent>(new TitleWindow()), 0, 0);
#if _DEBUG
	Event::New(std::shared_ptr<IEvent>(new DebugWindow()), 0, 0);
#endif
	//メインループ
	while (System::Update())
	{
		//フレーム開始処理
		ImGui_Impls3d_NewFrame();
		ImGui::NewFrame();
		UpdateControllers();
		Event::New(std::shared_ptr<IEvent>(new ShootingStarEffect(Cursor::Pos(), 3)), 0, 10, Foreground);
		//ImGui::ShowDemoWindow();
		//フレーム終了処理
		Event::Loop();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_Impls3d_RenderDrawData(ImGui::GetDrawData());
	}
	//ソフトの終了処理
	ImGui_Impls3d_Shutdown();
	ImGui::DestroyContext();
}