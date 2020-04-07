
#include <Siv3D.hpp> // OpenSiv3D v0.4.2
#include "Constant.hpp"
#include "BackGround.hpp"
#include "Player.hpp"
#include "CollisionObject.hpp"
#include "Creature.hpp"
#include "Wallet.hpp"
#include "Bar.hpp"
#include "Money.hpp"
#include "Buddha.hpp"


struct  GameData{
	int point = 0;
};

using App = SceneManager<String, GameData>;



// タイトルシーン
class Title : public App::Scene
{

private:
	const Font titleFont = Font(100, FileSystem::SpecialFolderPath(SpecialFolder::SystemFonts) + U"ariblk.ttf", FontStyle::Italic);
	const Font nomalFont = Font(20, Typeface::Default, FontStyle::Bold);
	const Texture backGroundTex = Texture(U"img/machi.png");
	BackGround backGround = BackGround(backGroundTex);

public:

	Title(const InitData& init) : IScene(init)
	{
	}

	// 更新関数
	void update() override
	{
		backGround.update();
		if (KeySpace.down())
		{
			// ゲームシーンに遷移
			changeScene(U"Stage1");
		}
	}

	// 描画関数 (const 修飾)
	void draw() const override
	{
		//Scene::SetBackground(Palette::Black);
		backGround.draw();
		titleFont(U"HAKAI-SO").drawAt(Constant::windowWidth / 2 + 8, Constant::windowHeight / 4 + 8, Color(0, 255, 180));
		titleFont(U"HAKAI-SO").drawAt(Constant::windowWidth/2,Constant::windowHeight/4 ,Color(255, 0, 211));
		nomalFont(U"スペースキーでスタート").drawAt(Constant::windowWidth / 2, Constant::windowHeight * 3 / 4);
	}
};



//ゲームステージ1
class Stage1 : public App::Scene {
	
private:
	const Texture playerTex = Texture(U"img/hakai-sow_smoking.png");
	const Texture backGroundTex = Texture(U"img/machi.png");
	const Texture creatureTex = Texture(U"img/mushikera_elite.png");
	const Texture walletTex = Texture(U"img/kane_yen-mark.png");
	const Texture buddhaTex = Texture(U"img/hotoke.png");
	const Texture moneyTex = Texture(U"img/satsu_yen-mark.png");
	const Texture barTex = Texture(U"img/nomiya_close.png");
	const Texture lifeGageTex = Texture(U"img/hotoke-face.png");

	BackGround backGround = BackGround(backGroundTex);
	Player player = Player(playerTex);
	Buddha buddha = Buddha(buddhaTex);


	Array<Creature> creatures;
	Array<Wallet> wallets;
	Array<Money> moneys;
	Array<Bar> bars;

	const Font font = Font(20, Typeface::Default, FontStyle::Bold);
	const Font pointFont = Font(20, FileSystem::SpecialFolderPath(SpecialFolder::SystemFonts) + U"ariblk.ttf");
	int life = 3;
	bool watched;
	int count = 0;
	bool inBar = false;
	int barCount = 0;

public:

	Stage1(const InitData& init) : IScene(init)
	{
		for (int i = 0; i < 30; i++) {
			creatures << Creature(creatureTex, Random(Constant::windowWidth, Constant::windowWidth * 5));
		}
		for (int i = 0; i < 20; i++) {
			wallets << Wallet(walletTex, Random(Constant::windowWidth, Constant::windowWidth * 5));
		}
		for (int i = 0; i < 100; i++) {
			moneys << Money(moneyTex, Random(Constant::windowWidth, Constant::windowWidth * 5));
		}
		for (int i = 0; i < 5; i++) {
			bars << Bar(barTex, Random(6, 30) * Constant::windowWidth / 5);
		}
		watched = false;
		getData().point = 0;
	}

	// 更新関数
	void update() override
	{
		backGround.update();


		if (inBar) { //バーに入っているとき
			barCount++;
			getData().point++;
			player.setX(player.getX() - Constant::scrollSpeed);
			if (KeyV.pressed() || player.getX() <= 0) {
				inBar = false;
				if (watched) {
					life--;
				}
			}
			player.updateCollider();
		}
		else {
			player.update();
		}
		
		buddha.update();

		//creaturesの処理(イテレータを使用)
		for (auto it = creatures.begin(); it != creatures.end();) {
			if (it->getX() <=Constant::windowWidth) {
				it->setRun(true);
			}
			it->update();
			//衝突判定と衝突処理
			if (it->getCollider().intersects(player.getCollider()) && !inBar) {
				it->setIntersectFlag(true);
				if (KeyZ.pressed()) {
					getData().point += 100;
					if (watched) {
						life--;
					}
					it = creatures.erase(it);
					continue;
				}
			}
			else {
				it->setIntersectFlag(false);
			}
			it++;
		}

		//walletsの処理(イテレータを使用)
		for (auto it = wallets.begin(); it != wallets.end();) {
			it->update();
			//衝突判定と衝突処理
			if (it->getCollider().intersects(player.getCollider()) && !inBar) {
				it->setIntersectFlag(true);
				if (KeyX.pressed()) {
					getData().point += 200;
					if (watched) {
						life--;
					}
					it = wallets.erase(it);
					continue;
				}
			}
			else {
				it->setIntersectFlag(false);
			}
			it++;
		}

		//moneysの処理(イテレータを使用)
		for (auto it = moneys.begin(); it != moneys.end();) {
			it->update();
			//衝突判定と衝突処理
			if (it->getCollider().intersects(player.getCollider()) && !inBar) {
				it->setIntersectFlag(true);
				getData().point += 100;
				if (watched) {
					life--;
				}
				it = moneys.erase(it);
				continue;
			}
			else {
				it->setIntersectFlag(false);
			}
			it++;
		}

		//barsの処理(イテレータを使用)
		for (auto it = bars.begin(); it != bars.end();) {
			it->update();
			//衝突判定と衝突処理
			if (it->getCollider().intersects(player.getCollider()) && !inBar) {
				it->setIntersectFlag(true);
				if (KeyC.pressed()) {
					getData().point += 200;
					inBar = true;
					if (watched) {
						life--;
					}
				}
				if (it->getX() <= -barTex.width()) {
					it = bars.erase(it);
					continue;
				}
			}
			else if(!inBar) {
				it->setIntersectFlag(false);
			}
			it++;
		}




		//仏に見られているかどうかの判定
		watched = player.getCollider().intersects(buddha.getCollider());


		if (life <= 0) {
			changeScene(U"GameOver");
		}

		if (count == Constant::windowWidth * 5) {
			changeScene(U"Stage1Clear");
		}
		count += Constant::scrollSpeed;
	}

	// 描画関数 (const 修飾)
	void draw() const override
	{
		backGround.draw();


		//bars関連の描画処理
		for (auto it = bars.begin(); it != bars.end();) {
			it->draw();
			if (it->getIntersectFlag()) {
				if (inBar == false) {
					font(U"C:入る").drawAt(it->getX(), Constant::windowHeight - Constant::humanHeight - 20, Palette::White);
				}
				else {
					font(U"V:出る").drawAt(it->getX(), Constant::windowHeight - Constant::humanHeight - 20, Palette::White);
				}
			}
			it++;
		}

		if (!inBar) { //バーに入っているときはプレイヤーを描画しない
			player.draw();
		}

		
		//creatures関連の描画処理
		for (auto it = creatures.begin(); it != creatures.end();) {
			it->draw();
			if (it->getIntersectFlag() && !inBar) {
				font(U"Z:踏む").drawAt(it->getX(), Constant::windowHeight - Constant::humanHeight - 20, Palette::Red);
			}
			it++;
		}

		//wallets関連の描画処理
		for (auto it = wallets.begin(); it != wallets.end();) {
			it->draw();
			if (it->getIntersectFlag() && !inBar) {
				font(U"X:拾う").drawAt(it->getX(), Constant::windowHeight - Constant::humanHeight - 20, Palette::Yellow);
			}
			it++;
		}

		//moneys関連の描画処理
		for (auto it = moneys.begin(); it != moneys.end();) {
			it->draw();
			it++;
		}
		
		buddha.draw();
		font(U"SCORE:", getData().point).draw(0,70);
		for (int i = 0; i < life; i++) {
			lifeGageTex.draw((lifeGageTex.width()+5) * i, 0);
		}
	}
};


// ゲームオーバーシーン
class GameOver : public App::Scene
{
private:
	const Font titleFont = Font(100, FileSystem::SpecialFolderPath(SpecialFolder::SystemFonts) + U"ariblk.ttf", FontStyle::Italic);
	const Font titleFont2 = Font(50, Typeface::Default, FontStyle::Bold);
	const Font font = Font(20, Typeface::Default, FontStyle::Bold);

	const Texture backGroundTex = Texture(U"img/machi.png");
	BackGround backGround = BackGround(backGroundTex);

public:

	GameOver(const InitData& init) : IScene(init)
	{
	}

	// 更新関数
	void update() override
	{
		backGround.update();
		if (KeySpace.pressed()) {
			changeScene(U"Stage1");
		}
	}

	// 描画関数 (const 修飾)
	void draw() const override
	{
		backGround.draw();
		//Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

		titleFont(U"HA-MON").drawAt(Constant::windowWidth / 2+8, Constant::windowHeight / 4+8, Color(0, 255, 180));
		titleFont(U"HA-MON").drawAt(Constant::windowWidth / 2, Constant::windowHeight / 4,Palette::Blue);
		titleFont2(U"GAME OVER").drawAt(Constant::windowWidth / 2, Constant::windowHeight / 4 + 70);
		font(U"スペースキーでリスタート").drawAt(Constant::windowWidth / 2, Constant::windowHeight* 3/ 4);
	}
};

//クリアシーン
class Stage1Clear : public App::Scene
{
private:
	const Font titleFont = Font(100, FileSystem::SpecialFolderPath(SpecialFolder::SystemFonts) + U"ariblk.ttf", FontStyle::Italic);
	const Font font = Font(20, Typeface::Default, FontStyle::Bold);

	const Texture backGroundTex = Texture(U"img/machi.png");
	BackGround backGround = BackGround(backGroundTex);

public:
	Stage1Clear(const InitData& init) : IScene(init)
	{
	}

	// 更新関数
	void update() override
	{
		backGround.update();
		if (KeySpace.pressed()) {
			changeScene(U"Stage1");
		}
	}

	// 描画関数 (const 修飾)
	void draw() const override
	{
		//Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
		
		backGround.draw();
		titleFont(U"CLEAR!").drawAt(Constant::windowWidth / 2+8, Constant::windowHeight / 4+8, Color(0, 255, 180));
		titleFont(U"CLEAR!").drawAt(Constant::windowWidth / 2, Constant::windowHeight / 4, Color(255, 211,0));
		font(U"SCORE:",getData().point).drawAt(Constant::windowWidth / 2, Constant::windowHeight * 3 / 4);
		font(U"スペースキーでリスタート").drawAt(Constant::windowWidth / 2, Constant::windowHeight * 4/5 );
	}
};

void Main()
{
	Window::Resize(Constant::windowWidth, Constant::windowHeight);
	Scene::Resize(Constant::windowWidth, Constant::windowHeight);

	Window::SetStyle(WindowStyle::Sizable);
	FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);
	
	// シーンマネージャーを作成
	App manager;

	//タイトルシーンをシーンマネージャーに追加
	manager.add<Title>(U"Title");
	manager.add<Stage1>(U"Stage1");
	manager.add<GameOver>(U"GameOver");
	manager.add<Stage1Clear>(U"Stage1Clear");

	while (System::Update())
	{
		// 現在のシーンを実行
		if (!manager.update())
		{
			break;
		}
	}
}
