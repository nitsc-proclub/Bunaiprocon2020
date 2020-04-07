
#pragma once
#include "Common.h"


class Enemy
{

public:

	Vec2 GenerateEnemy()
	{
		return RandomVec2({ 50, 750 }, 1);
	}
	Circle collision[20];
	int Frag[20];

	Enemy()
	{
		for (int i = 0; i < 20; i++)
		{
			Frag[i] = 0;
		}
	}

	// “G
	Array<Vec2> enemies = { GenerateEnemy() };

	void update()
	{


		// “G‚ÌƒXƒs[ƒh
		constexpr double enemySpeed = 100.0;


		// “G‚Ì”­¶ŠÔŠu‚Ì‰Šú’li•bj
		double initialEnemySpawnTime = 2.0;
		// “G‚Ì”­¶ŠÔŠui•bj
		double enemySpawnTime = initialEnemySpawnTime;
		// “G‚Ì”­¶ŠÔŠuƒ^ƒCƒ}[
		double enemySpawnTimer = 1.0;

		// ‰æ–ÊŠO‚Éo‚½“G‚ÍÁ–Å
		enemies.remove_if([&](const Vec2& e)
			{
				if (e.y > 700)
				{
					// “G‚ª‰æ–ÊŠO‚Éo‚½‚çƒQ[ƒ€ƒI[ƒo[

					return true;
				}
				else
				{
					return false;
				}

			});

		const double deltaTime = Scene::DeltaTime();
		enemySpawnTimer += deltaTime;

		// “G‚Ì”­¶
		for (int i = 0; i < 20; i++)
		{
			enemySpawnTimer -= enemySpawnTime;
			enemySpawnTime = Max(enemySpawnTime * 0.95, 0.3);
			enemies << GenerateEnemy();
		}
		// “G‚ÌˆÚ“®
		for (auto& enemy : enemies)
		{
			enemy.y += deltaTime * enemySpeed;
		}

		for (int i = 0; i < 20; i++)
		{
			if (Frag[i] == 1)
			{
				collision[i] = Circle(enemies[i], 5.0);

				if (enemies[i].y <= 0)
				{
					Frag[i] = 0;
				}
			}
		}


	}
	
	Circle& getcollision(int a)
	{
		return collision[a];
	}

	void draw() const
	{
		// “G‚Ì•`‰æ
		for (const auto& enemy : enemies)
		{
			//“G‚ÌƒeƒNƒXƒ`ƒƒ
			TextureAsset(U"u-tan").resized(1).drawAt(enemy);
		}
	}
	int hitPoint = 1;
	bool dead() const
	{
		return (hitPoint <= 0);
	}
};