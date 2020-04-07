#pragma once

#include "Common.h"
#include  "Enemy.h"
#include "Player.h"
#include "PlayerBullet.h"


class Game : public MyApp::Scene
{

public:

	Game(const InitData& init) : IScene(init)
	{
		// シーン読み込み時に一度だけ実行される
	/*	field = Rect(50, 50, 500, 500);*/
		Scene::SetBackground(ColorF(0.3, 0.6, 1.0));
	}

	void update() override
	{

		player.update();
		for (int i = 0; i < 20; i++)
		{
			Bullet.update();
			//for (int j = 0; j < 100; j++)
			//{
			//	enemie[j].update();
			//	if (Bullet.getcollision(i).intersects(enemies.getcollision(j)))
			//	{
			//		changeScene(State::Title, 0);
			//	}
			//}
		}
		//for (int i = 0; i < 100; i++)
		//{
		//	enemie[i].update();
		//	player.update();
		//	if (enemies.getcollision(i).intersects(player.getcollision()))
		//	{
		//		changeScene(State::Title, 0);
		//	}
		//}
		//if (!enemie)
		//{
		//	changeScene(State::Title, 0);
		//}

		for (int i = 1; i < 100; i++)
		{
		

		}

		if (KeyF.pressed())
		{
			changeScene(State::Title, 0);
		}
	}

	void draw() const override
	{
		player.draw();
		//enemies.draw();
		//for (int i = 0; i < 100; i++)
		//{
		//	if (!(enemie[i].dead()))
		//	{
		//		enemie[i].draw();
		//	}
		//}

		for (int i = 0; i < 20; i++)
		{
			if (!(Bullet.dead()))
			{
				Bullet.draw();
			}
		}

	}



private:

	Player player;
	PlayerBullet Bullet;
	Enemy enemie[100]; // 敵のリスト
	Enemy enemies;
	Rect field; // 枠
};
