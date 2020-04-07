#include"TitleScene.h"

TitleScene::TitleScene()
{
	interval = Stopwatch(true);
	Sound::PlayBGM(U"BGMIdle2", true, 2, 0, 0.8);
}

void TitleScene::Loop()
{
	if (interval.sF() >= 1)
	{
		Event::New(std::shared_ptr<IEvent>(new BoxFloatEffect(6, Size(30, 30))), 0, 300, Background);
		interval.restart();
	}
}
