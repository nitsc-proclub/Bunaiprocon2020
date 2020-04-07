#pragma once

// インクルードガード
#ifndef EXTENSION_WEAPONS_HPP
#define  EXTENSION_WEAPONS_HPP

#include "Weapon.hpp"


#define FPS 60


class PredatorCannon : public WeaponBase
{
public:
	PredatorCannon() : WeaponBase()
	{

	}


	PredatorCannon(Vec2 pos) : WeaponBase()
	{
		gun_image_ = Texture(U"path");
		bullet_image_ = Texture(U"path");
		firing_rate_ = 20; // 決め打ち
		damage_ = 40;
		pos_ = pos;
		bullet_list_.clear();
	}


	void update(Vec2 gun_pos) override
	{
		pos_ = gun_pos;

		if (KeySpace.pressed())
		{
			if (Scene::FrameCount() % (FPS / firing_rate_) == 0)
			{
				shot();
			}
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
		gun_image_.resized(50, 100).drawAt(pos_ - Vec2(distance_to_person_, 0));
		gun_image_.resized(50, 100).drawAt(pos_ + Vec2(distance_to_person_, 0));
	}


	Array<Bullet>&getBullets() override
	{
		return bullet_list_;
	}
	

private:
	Vec2 pos_;
	Texture gun_image_;
	Texture bullet_image_;
	Array<Bullet> bullet_list_;

	int damage_;
	int firing_rate_;
	const int distance_to_person_ = 50;

	const Rect bullet_base_ = Rect(0, 0, 10, 25);
	const int bullet_visible_frame_ = 120;
	const double ammunition_rate_ = 1; // 集弾率のパラメーター　0だとまっすぐとび、値を増やすと-rate_～rateの間で弾丸の方向が変わる

	void shot() override
	{
		// 発射エフェクトの描画のフラグを立てるならここに書くとよいかもしれない
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_ - Vec2(distance_to_person_, 0), Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), -30), damage_, bullet_visible_frame_, U"predator"));
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_ + Vec2(distance_to_person_, 0), Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), -30), damage_, bullet_visible_frame_, U"predator"));
	}
};



class PlasmaRailGun : public WeaponBase
{
public:
	PlasmaRailGun() : WeaponBase()
	{

	}


	PlasmaRailGun(Vec2 pos) : WeaponBase()
	{
		gun_image_ = Texture(U"path");
		bullet_image_ = Texture(U"path");
		firing_rate_ =3; // 決め打ち
		damage_ = 100;
		pos_ = pos;
		bullet_list_.clear();
	}


	void update(Vec2 gun_pos) override
	{
		pos_ = gun_pos;

		if (KeySpace.pressed())
		{
			if (Scene::FrameCount() % (FPS / firing_rate_) == 0)
			{
				shot();
			}
		}

		for (int i = 0; i < bullet_list_.size(); i++)
		{
			bullet_list_[i].update();
			if (bullet_list_[i].getVisibleFrame() <= 0)
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
		gun_image_.resized(50, 100).drawAt(pos_ - Vec2(distance_to_person_, 0));
		gun_image_.resized(50, 100).drawAt(pos_ + Vec2(distance_to_person_, 0));
	}


	Array<Bullet>& getBullets() override
	{
		return bullet_list_;
	}


private:
	Vec2 pos_;
	Texture gun_image_;
	Texture bullet_image_;
	Array<Bullet> bullet_list_;
	
	int damage_;
	int firing_rate_;

	const Vec2 bullet_size_ = Vec2(10, Scene::Height());
	const int bullet_visible_frame_ = 5;
	const int distance_to_person_ = 50;

	void shot() override
	{
		// 発射エフェクトの描画のフラグを立てるならここに書くとよいかもしれない
		bullet_list_.push_back(Bullet(bullet_image_, bullet_size_.x, bullet_size_.y, pos_ - Vec2(distance_to_person_, bullet_size_.y / 2) , Vec2(0, 0), damage_, bullet_visible_frame_, U"railgun"));
		bullet_list_.push_back(Bullet(bullet_image_, bullet_size_.x, bullet_size_.y, pos_ - Vec2(-distance_to_person_, bullet_size_.y / 2), Vec2(0, 0), damage_, bullet_visible_frame_, U"railgun"));
	}
};


class Fliegerhummer : public WeaponBase
{
public:
	Fliegerhummer() : WeaponBase()
	{

	}


	Fliegerhummer(Vec2 pos) : WeaponBase()
	{
		gun_image_ = Texture(U"path");
		bullet_image_ = Texture(U"path");
		firing_rate_ = 10; // 決め打ち
		damage_ = 1;
		pos_ = pos;
		bullet_list_.clear();
	}


	void update(Vec2 gun_pos) override
	{
		pos_ = gun_pos;

		if (KeySpace.pressed())
		{
			if (Scene::FrameCount() % (FPS / firing_rate_) == 0)
			{
				shot();
			}
		}

		for (int i = 0; i < bullet_list_.size(); i++)
		{
			bullet_list_[i].update();
			if (bullet_list_[i].isDead() && bullet_list_[i].getDamage() == 0)
			{
				Vec2 hypocenter = bullet_list_[i].getCollision().pos + Vec2(bullet_list_[i].getCollision().w / 2, bullet_list_[i].getCollision().h / 2);
				Circle explosion_range = Circle(hypocenter, explosion_radius_);
				for (int j = 0; j < explosion_density_; j++)
				{
					// 小爆発をexplosion_range中のランダムな場所に配置する、次いでに小爆発の範囲自体もランダム
					explode_small(RandomVec2(explosion_range), Random<int>(explosion_radius_ / 4, explosion_radius_ / 2));
				}
				bullet_list_.remove_at(i);
				i--;
			}
			else if(bullet_list_[i].getVisibleFrame() <= 0)
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
		gun_image_.resized(50, 100).drawAt(pos_ - Vec2(distance_to_person_, 0));
		gun_image_.resized(50, 100).drawAt(pos_ + Vec2(distance_to_person_, 0));
	}


	Array<Bullet>& getBullets() override
	{
		return bullet_list_;
	}


private:
	Vec2 pos_;
	Texture gun_image_;
	Texture bullet_image_;
	Texture explosion_image_;
	Array<Bullet> bullet_list_;

	int damage_;
	int firing_rate_;
	const int distance_to_person_ = 50;
	const int explosion_radius_ = 50; // 爆発の範囲の半径
	const int explosion_density_ = 10; // 爆発の密度、爆発の範囲にどれだけ弾(小爆発)を敷き詰めるか

	const Rect bullet_base_ = Rect(0, 0, 10, 15);
	const int bullet_visible_frame_ = 120;
	const int explosion_visible_frame_ = 20;
	const double ammunition_rate_ = 2; // 集弾率 0だとまっすぐ、大きい数だと散らばる

	void shot() override
	{
		// 発射エフェクトの描画のフラグを立てるならここに書くとよいかもしれない
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_ - Vec2(distance_to_person_, 0), Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), -15), 0, bullet_visible_frame_, U"flieger"));
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_ + Vec2(distance_to_person_, 0), Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), -15), 0, bullet_visible_frame_, U"flieger"));
	}
	

	void explode_small(Vec2 pos_center, int radius)
	{
		bullet_list_.push_back(Bullet(explosion_image_, radius * 2, radius * 2, pos_center, Vec2(0, 0), damage_, explosion_visible_frame_,U"explosion"));
	}


	
};
#endif
