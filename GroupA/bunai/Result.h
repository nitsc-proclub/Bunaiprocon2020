
#pragma once

#include "Common.h"


class Result : public MyApp::Scene
{

public:

	const Font font = Font(60);

	Result(const InitData& init) : IScene(init)
	{
		// シーン読み込み時に一度だけ実行される
		Scene::SetBackground(ColorF(0.2, 0.2, 0.2));
	}

	void update() override
	{
		if (KeyN.up())
			changeScene(State::Title);
	}

	void draw() const override
	{
		FontAsset(U"Result")(U"You Lose!!").drawAt(400, 100);
		TextureAsset(U"Sakujo").scaled(1.5).drawAt(150, 280);
		TextureAsset(U"Yaju").scaled(1.5).drawAt(400, 400);
		TextureAsset(U"Itsuka").scaled(1.2).drawAt(650, 350);

	}
};