#pragma once

// インクルードガード
#ifndef BULLET_HPP
#define BULLET_HPP

#include <Siv3D.hpp>

class Bullet
{
public:
	Bullet()
	{

	}

	
	Bullet(Texture image, int width, int height, Vec2 default_pos, Vec2 speed, int damage, int visible_frame, String tag)
	{
		bullet_image = image;
		pos = default_pos;
		collision = Rect(pos.x, pos.y, width, height);
		this->damage = damage;
		this->speed = speed;
		this->visible_frame = visible_frame;
		this->tag = tag;
		dead = false;
	}
	

	void update()
	{
		visible_frame--;
		pos += speed;
		// posが長方形の中心の座標になるようにする
		collision.pos = (pos - Vec2(collision.w, collision.h) / 2).asPoint();
		

		// 弾丸の座標が画面外に出たときと、弾丸が発生してからvisible_frame経過したとき
		// 取り合えず簡潔に書いたけど、重かったら真っ先に変更すべき場所です。
		if (!pos.intersects(Scene::Rect()) || visible_frame < 0)
		{
			dead = true;
		}
	}


	void draw() const
	{
		// posを中心とした四角形のテクスチャが描画される
		bullet_image.resized(collision.w, collision.h).drawAt(pos);
	}


	void setTexture(Texture new_image)
	{
		this->bullet_image = new_image;
	}


	void setSize(int width, int height)
	{
		collision = Rect(pos.x, pos.y, width, height);
	}


	Rect& getCollision()
	{
		return collision;
	}


	String getTag()
	{
		return tag;
	}


	int getDamage()
	{
		return damage;
	}


	int getVisibleFrame()
	{
		return visible_frame;
	}


	int hit()
	{
		dead = true;
		return damage;
	}


	bool isDead()
	{
		return dead;
	}


private:
	Vec2 pos;
	Vec2 speed;
	Texture bullet_image;
	Rect collision;

	bool dead;
	int damage;
	int visible_frame;
	String tag;
	
};


#endif
