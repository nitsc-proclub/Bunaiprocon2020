#include<Siv3D.hpp>

// blockの位置をランダムに作成する関数
Vec2 Generateblock()
{
	return RandomVec2({ 50, 750 }, -20);
}
void Main()
{
	double right = 0, left = 0, v0 = -10.0, gravity = 0.3, muki = 0;
	Vec2 move(0.0, 0.0);
	Scene::SetBackground(ColorF(0, 0, 0));
	constexpr bool useConstantDeltaTime = true;
	if (useConstantDeltaTime)
	{
		// フレームレート上限を 60 FPS に
		Graphics::SetTargetFrameRateHz(60);
	}
	constexpr int32 velocityIterations = 12;
	constexpr int32 positionIterations = 4;
	const Texture playerTexture(Emoji(U"🤔"));
	Vec2 playerPos(300, 300);
	Array<Vec2> playerRBullets;
	Array<Vec2> playerLBullets;
	constexpr double playerSpeed = 550.0;
	constexpr double playerBulletSpeed = 100.0;
	constexpr double playerShotCoolTime = 1.0;
	double playerShotTimer = 0.0;

	// blockテクスチャ
	const Texture blockTexture(Emoji(U"◆"));
	// block
	Array<Vec2> blocks = { Generateblock() };
	// blockのスピード
	constexpr double blockSpeed = 100.0;
	// blockの発生間隔の初期値（秒）
	double initialblockSpawnTime = 2.0;
	// blockの発生間隔（秒）
	double blockSpawnTime = initialblockSpawnTime;
	// blockの発生間隔タイマー
	double blockSpawnTimer = 0.0;
	Effect effect;
	//床
	const Line floor(100, 400, 700, 400);
	while (System::Update())
	{
		// 通常の線
		floor.draw(LineStyle::RoundCap, 12, Palette::Orange);
		const double deltaTime = Scene::DeltaTime();
		playerShotTimer = Min(playerShotTimer + deltaTime, playerShotCoolTime);
		//--------------------
		//移動
		if (KeyD.pressed())
		{
			right = 4.0, muki = 0;
		}
		else
		{
			right = 0.0;
		}
		if (KeyA.pressed())
		{
			left = 4.0, muki = 1;
		}
		else
		{
			left = 0.0;
		}
		if (400 > playerPos.y&& playerPos.y > 365 && 100 < playerPos.x && playerPos.x < 700)//床との当たり判定とジャンプ
		{
			move.y = 0;
			if (KeySpace.down() && playerPos.y < 401)
			{
				move.y = v0;
			}
		}
		else
		{
			move.y += gravity;
		}
		playerPos.y += move.y;
		move.x = right - left;
		playerPos.x += move.x;
		playerRBullets.remove_if([](const Vec2& b) { return b.x > 1000; });
		playerLBullets.remove_if([](const Vec2& b) { return b.x < 0; });
		playerTexture.resized(80).drawAt(playerPos);
		if (MouseL.down())
		{
			if (muki == 0)
			{
				playerRBullets.push_back(playerPos);
			}
			if (muki == 1)
			{
				playerLBullets.push_back(playerPos);
			}
		}
		playerRBullets.each([](Vec2& b) { b.x += 8.0; });
		playerRBullets.each([](const Vec2& b) { Circle(b, 7).draw(Palette::Orange); });
		playerLBullets.each([](Vec2& b) { b.x -= 8.0; });
		playerLBullets.each([](const Vec2& b) { Circle(b, 7).draw(Palette::Orange); });

		const double deltaTime_b = Scene::DeltaTime();
		blockSpawnTimer += deltaTime_b;

		// 敵の発生
		while (blockSpawnTimer > blockSpawnTime)
		{
			blockSpawnTimer -= blockSpawnTime;
			blockSpawnTime = Max(blockSpawnTime * 0.95, 0.3);
			blocks << Generateblock();
		}

		// 敵の移動
		for (auto& block : blocks)
		{
			block.y += deltaTime * blockSpeed;
		}

		// 敵の描画
		for (const auto& block : blocks)
		{
			blockTexture.resized(60).drawAt(block);
		}


		effect.update();
	}
}