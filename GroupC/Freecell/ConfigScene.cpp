#include"ConfigScene.h"
#include"BoxFloatEffect.h"

ConfigScene::ConfigScene()
{
	Controller::CanShowSoftKey = true;
	interval = Stopwatch(true);
}

void ConfigScene::Loop()
{
	if (interval.sF() >= 1)
	{
		Event::New(std::shared_ptr<IEvent>(new BoxFloatEffect(6, Size(30, 30))), 0, 300, Background);
		interval.restart();
	}
}
