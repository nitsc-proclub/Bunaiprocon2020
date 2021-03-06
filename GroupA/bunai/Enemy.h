
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

	// 敵
	Array<Vec2> enemies = { GenerateEnemy() };

	void update()
	{


		// 敵のスピード
		constexpr double enemySpeed = 100.0;


		// 敵の発生間隔の初期値（秒）
		double initialEnemySpawnTime = 2.0;
		// 敵の発生間隔（秒）
		double enemySpawnTime = initialEnemySpawnTime;
		// 敵の発生間隔タイマー
		double enemySpawnTimer = 1.0;

		// 画面外に出た敵は消滅
		enemies.remove_if([&](const Vec2& e)
			{
				if (e.y > 700)
				{
					// 敵が画面外に出たらゲームオーバー

					return true;
				}
				else
				{
					return false;
				}

			});

		const double deltaTime = Scene::DeltaTime();
		enemySpawnTimer += deltaTime;

		// 敵の発生
		for (int i = 0; i < 20; i++)
		{
			enemySpawnTimer -= enemySpawnTime;
			enemySpawnTime = Max(enemySpawnTime * 0.95, 0.3);
			enemies << GenerateEnemy();
		}
		// 敵の移動
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
		// 敵の描画
		for (const auto& enemy : enemies)
		{
			//敵のテクスチャ
			TextureAsset(U"u-tan").resized(1).drawAt(enemy);
		}
	}
	int hitPoint = 1;
	bool dead() const
	{
		return (hitPoint <= 0);
	}
};