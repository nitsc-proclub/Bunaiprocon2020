#pragma once

// インクルードガード
#ifndef ENEMY_WEAPON_EXTENSION_HPP
#define ENEMY_WEAPON_EXTENSION_HPP

#include <Siv3D.hpp>
#include "Weapon.hpp"
#include "ExtensionWeapons.hpp"

class EnemyNormalGun : public WeaponBase
{
public:
	EnemyNormalGun() : WeaponBase()
	{

	}


	EnemyNormalGun(Vec2 pos) : WeaponBase()
	{
		bullet_image_ = Texture(U"Path");
		firing_rate_ = 2; // 決め打ち
		damage_ = 5;
		pos_ = pos;
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
	Texture bullet_image_;
	Array<Bullet> bullet_list_;

	int damage_;
	int firing_rate_;

	const Rect bullet_base_ = Rect(0, 0, 10, 10);
	const int bullet_visible_frame_ = 120;
	const double ammunition_rate_ = 30; // 集弾率のパラメーター　0だとまっすぐとび、値を増やすと-rate_～rateの間で弾丸の方向が変わる

	void shot() override
	{
		// 発射エフェクトの描画のフラグを立てるならここに書くとよいかもしれない
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_, Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), 15), damage_, bullet_visible_frame_, U"enemy"));
	}
};


class EnemyShotGun : public WeaponBase
{
public:
	EnemyShotGun() : WeaponBase()
	{

	}


	EnemyShotGun(Vec2 pos) : WeaponBase()
	{
		bullet_image_ = Texture();
		firing_rate_ = 1; // 決め打ち
		damage_ = 3;
		pos_ = pos;
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
	Texture bullet_image_;
	Array<Bullet> bullet_list_;

	int damage_;
	int firing_rate_;

	const Rect bullet_base_ = Rect(0, 0, 10, 10);
	const int bullet_visible_frame_ = 120;
	const double ammunition_rate_ = 30; // 集弾率のパラメーター　0だとまっすぐとび、値を増やすと-rate_～rateの間で弾丸の方向が変わる

	void shot() override
	{
		// 発射エフェクトの描画のフラグを立てるならここに書くとよいかもしれない
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_, Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), 10), damage_, bullet_visible_frame_, U"enemy"));
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_, Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), 10), damage_, bullet_visible_frame_, U"enemy"));
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_, Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), 10), damage_, bullet_visible_frame_, U"enemy"));
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_, Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), 10), damage_, bullet_visible_frame_, U"enemy"));
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_, Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), 10), damage_, bullet_visible_frame_, U"enemy"));
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_, Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), 10), damage_, bullet_visible_frame_, U"enemy"));
	}
};



class BossWeapon : public WeaponBase
{
public:
	BossWeapon() : WeaponBase()
	{

	}


	BossWeapon(Vec2 pos) : WeaponBase()
	{
		bullet_image_ = Texture();
		firing_rate_ = 10; // 決め打ち
		damage_ = 2;
		pos_ = pos;
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
	Texture bullet_image_;
	Array<Bullet> bullet_list_;

	int damage_;
	int firing_rate_;

	const Rect bullet_base_ = Rect(0, 0, 10, 10);
	const int bullet_visible_frame_ = 120;
	const double ammunition_rate_ = 30; // 集弾率のパラメーター　0だとまっすぐとび、値を増やすと-rate_～rateの間で弾丸の方向が変わる

	void shot() override
	{
		// 発射エフェクトの描画のフラグを立てるならここに書くとよいかもしれない
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_, Vec2(Random<double>(-1, 1), Random<double>(-1, 1)).setLength(10), damage_, bullet_visible_frame_, U"enemy"));
	}
};


#endif