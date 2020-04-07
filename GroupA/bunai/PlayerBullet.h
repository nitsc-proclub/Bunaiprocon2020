#pragma once

#include <Siv3D.hpp>
#include "Player.h"
#include "Common.h"


class PlayerBullet
{
private:
	Array<Vec2> Bullet;
	int Bullet_Frag[20];
	RectF collision[20];
	Texture Karasawa;
	Player player;
public:
	PlayerBullet()
	{
		for (int i = 0; i < 20; i++)
		{
			Bullet_Frag[i] = 0;
		}
		Karasawa = Texture(U"example/Karasawa.jpg");
	}
	void update()
	{
		if (KeyZ.down())
		{
			for (int i = 0; i < 20; i++)
			{
				if (Bullet_Frag[i] == 0)
				{
					Bullet[i].x = Player_x;
					Bullet[i].y = Player_y;
					Bullet_Frag[i] = 1;
					break;
				}
			}
		}
		for (int i = 0; i < 20; i++)
		{
			if (Bullet_Frag[i] == 1)
			{
				Bullet[i].y = Bullet[i].y - 10;
				collision[i] = RectF(Bullet[i].x - 5, Bullet[i].y - 5, 10, 10);
				if (Bullet[i].y <= 0)
				{
					Bullet_Frag[i] = 0;
				}
			}
		}
	}
	void draw() const
	{
		for (int i = 0; i < 20; i++)
		{
			if (Bullet_Frag[i] == 1)
			{
				Karasawa.resized(50, 50).draw(Bullet[i].x, Bullet[i].y - 10);
			}
		}
	}

	int hitPoint = 1;
	bool dead() const
	{
		return (hitPoint <= 0);
	}
	RectF& getcollision(int a)
	{
		return collision[a];
	}
};
