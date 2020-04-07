#pragma once

// �C���N���[�h�K�[�h
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
		firing_rate_ = 20; // ���ߑł�
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
	const double ammunition_rate_ = 1; // �W�e���̃p�����[�^�[�@0���Ƃ܂������ƂсA�l�𑝂₷��-rate_�`rate�̊ԂŒe�ۂ̕������ς��

	void shot() override
	{
		// ���˃G�t�F�N�g�̕`��̃t���O�𗧂Ă�Ȃ炱���ɏ����Ƃ悢��������Ȃ�
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
		firing_rate_ =3; // ���ߑł�
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
		// ���˃G�t�F�N�g�̕`��̃t���O�𗧂Ă�Ȃ炱���ɏ����Ƃ悢��������Ȃ�
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
		firing_rate_ = 10; // ���ߑł�
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
					// ��������explosion_range���̃����_���ȏꏊ�ɔz�u����A�����łɏ������͈͎̔��̂������_��
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
	const int explosion_radius_ = 50; // �����͈̔͂̔��a
	const int explosion_density_ = 10; // �����̖��x�A�����͈̔͂ɂǂꂾ���e(������)��~���l�߂邩

	const Rect bullet_base_ = Rect(0, 0, 10, 15);
	const int bullet_visible_frame_ = 120;
	const int explosion_visible_frame_ = 20;
	const double ammunition_rate_ = 2; // �W�e�� 0���Ƃ܂������A�傫�������ƎU��΂�

	void shot() override
	{
		// ���˃G�t�F�N�g�̕`��̃t���O�𗧂Ă�Ȃ炱���ɏ����Ƃ悢��������Ȃ�
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_ - Vec2(distance_to_person_, 0), Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), -15), 0, bullet_visible_frame_, U"flieger"));
		bullet_list_.push_back(Bullet(bullet_image_, bullet_base_.w, bullet_base_.h, pos_ + Vec2(distance_to_person_, 0), Vec2(Random<double>(-ammunition_rate_, ammunition_rate_), -15), 0, bullet_visible_frame_, U"flieger"));
	}
	

	void explode_small(Vec2 pos_center, int radius)
	{
		bullet_list_.push_back(Bullet(explosion_image_, radius * 2, radius * 2, pos_center, Vec2(0, 0), damage_, explosion_visible_frame_,U"explosion"));
	}


	
};
#endif
