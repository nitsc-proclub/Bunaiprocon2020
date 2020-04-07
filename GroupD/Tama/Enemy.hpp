#pragma once

// インクルードガード
#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "EnemyAI.hpp"

// ここにパーソンから派生した敵のクラスを記述する
class Enemy : public PersonBase
{
public:
	Enemy() : Enemy(nullptr, nullptr, Texture(), 0, 0, 0, Vec2(0, 0))
	{
	}


	Enemy(WeaponBase* wp, EnemyAIBase* ai, const Texture image, const int width, const int height, const int hp, const Vec2 pos)
		: PersonBase(wp, hp, pos), ai_(ai), image_(image.resized(width, height)), collision_(Rect(pos.asPoint(), width, height))
	{
	}
	

	Enemy(WeaponBase* wp, EnemyAIBase* ai, TextureRegion resized_image, const int hp, const Vec2 pos)
		: PersonBase(wp, hp, pos), ai_(ai), image_(resized_image), collision_(Rect(pos.asPoint(), resized_image.size.x, resized_image.size.y))
	{
	}

	// デストラクタ(未実装)
	~Enemy()
	{
	}


	void update()
	{
		set_pos(ai_->update(get_pos()));
		collision_.pos = (get_pos() - Vec2(collision_.w, collision_.h) / 2).asPoint();
	}
	

	void draw() const override final
	{
		/*Print(this->get_hp());
		Print(this->get_weapon());
		Print(this->get_x());
		Print(this->get_y());*/
		get_weapon()->draw(); 
		image_.drawAt(get_pos());
	}


	//////////////////////////////
	// アクセサー
	Rect& get_collision()
	{
		return this->collision_;
	}

	
private:
	EnemyAIBase* ai_;
	TextureRegion image_;
	Rect collision_;
};


#endif
