#pragma once
class Constant
{
public:
	static const int windowWidth = 960; //ウィンドウの幅
	static const int windowHeight = 540; //ウィンドウの高さ

	static const int buildingHeight = windowHeight * 4/5; //ビルの高さ
	static const int groundHeight = windowHeight * 1/36; //地面の高さ
	static const int humanHeight = windowHeight / 4; //人間の高さ
	static const int humanWidth = humanHeight / 2; //人間の幅
	static const int creatureWidth = humanWidth; //生き物の幅
	static const int creatureHeight = creatureWidth * 36 / 98; //生き物の高さ
	static const int walletWidth = humanWidth/1.5; //財布の幅
	static const int walletHeight = walletWidth * 42/54; //財布の高さ
	static const int playerSpeed = 10; //プレイヤーの移動スピード
	static const int scrollSpeed = 1; //スクロールスピード
	static const int creatureSpeed = scrollSpeed + 1; //生き物の移動スピード
	static const int buddhaSpeed = scrollSpeed;
	static const int moneySpeedY = 3;
	static const int moneySpeedX = 3;
};

