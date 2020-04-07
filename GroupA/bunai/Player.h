
#pragma once
#include <Siv3D.hpp>
#include "Common.h"


int Player_x, Player_y;
class  Player
{		
private:
	Texture player;
public:
	int speed;
	int Life;

	Rect collision;
	Player() //プレイヤーの初期値
	{
		Player_x = 320;
		Player_y = 240;
		speed = 5;
		Life = 3;
		player = Texture(U"example/player.jpg");
	}
	void update() //移動
	{
		if (KeyLeft.pressed())
		{
			Player_x = Player_x - speed;
		}
		if (KeyRight.pressed())
		{
			Player_x = Player_x + speed;
		}
		if (KeyUp.pressed())
		{
			Player_y = Player_y - speed;
		}
		if (KeyDown.pressed())
		{
			Player_y = Player_y + speed;
		}
		collision = Rect(Player_x - 25, Player_y, 50, 50);
	}
	void draw() const//描画
	{
		player.resized(50, 50).draw(Player_x, Player_y);
	}
	Rect getcollision()
	{
		return collision;
	}
	int X()
	{
		return Player_x;
	}
	int Y()
	{
		return Player_y;
	}
};