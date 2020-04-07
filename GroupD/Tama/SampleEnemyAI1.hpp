#pragma once

// インクルードガード
#ifndef EXTENSION_AI_HPP
#define EXTENSION_AI_HPP

#include <Siv3D.hpp>
#include "EnemyAI.hpp"
#include "ExtensionWeapons.hpp"

class EnemyAISample : public EnemyAIBase
{
public:
	EnemyAISample() : EnemyAISample(nullptr)
	{
	}
	
	EnemyAISample(WeaponBase* wp) : EnemyAIBase(wp)
	{
	}

	~EnemyAISample()
	{
	}

	// enemyの動き方を記述する関数
	Vec2 update(Vec2 last_pos) override
	{
		if (last_pos != Scene::Center())
		{
			next_pos_ = last_pos;
			next_pos_ += get_direction_to_center(last_pos, 5);
		}
		get_weapon()->update(next_pos_); // 武器のアップデート、この武器はEnemyクラスに入っているものと同じ存在
		return next_pos_;
	}

private:
	Vec2 next_pos_;

	// posから画面の中心に向いた、speedの長さのベクトルを取得する
	static Vec2 get_direction_to_center(const Vec2 pos, const int speed)
	{
		auto move = (Scene::Center() - pos).setLength(speed);
		return move;
	}
	
};


class SampleWeapon : public WeaponBase
{
public:
	SampleWeapon() : SampleWeapon(Vec2(0, 0), Vec2(0, 0))
	{

	}


	SampleWeapon(const Vec2 pos, const Vec2 bullet_speed) : WeaponBase()
	{
		bullet_image_ = Texture(U"path");
		firing_rate_ = 1;
		damage_ = 10;
		pos_ = pos;
		speed_ = bullet_speed;
		bullet_list_.clear();
	}


	void update(Vec2 gun_pos) override
	{
		pos_ = gun_pos;

		if (Scene::FrameCount() % (FPS / firing_rate_) == 0)
		{
			shot();
		}

		for (int i = 0; i < bullet_list_.size(); i++)
		{
			bullet_list_[i].update();
			if (bullet_list_[i].isDead())
			{
				bullet_list_.remove_at(i);
				i--;
			}
		}
	}


	void draw() const override
	{
		for (int i = 0; i < bullet_list_.size(); i++)
		{
			bullet_list_[i].draw();
		}
	}


	Array<Bullet>& getBullets() override
	{
		return bullet_list_;
	}


private:
	Vec2 pos_;
	Vec2 speed_;
	Texture bullet_image_;
	Array<Bullet> bullet_list_;

	int damage_;
	int firing_rate_;

	const Rect bullet_base_ = Rect(0, 0, 5, 10);
	const int bullet_visible_frame_ = 120;

	void shot() override
	{
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_, speed_, damage_, bullet_visible_frame_, U"sample"));
	}
};

#endif