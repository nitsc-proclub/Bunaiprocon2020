#pragma once

// インクルードガード
#ifndef PERSON_HPP
#define PERSON_HPP

#include "ExtensionWeapons.hpp"

// ここにパーソンの基底クラスを記述する
class PersonBase
{
public:
	// コンストラクタ
	PersonBase() : PersonBase(nullptr, 0, Vec2(0, 0))
	{
	}
	
	PersonBase(const int hp, const Vec2 pos) : PersonBase(nullptr, hp, pos)
	{
	}

	PersonBase(WeaponBase* wp, const int hp, const Vec2 pos) : wp_(wp), hp_(hp), pos_(pos)
	{
	}

	// デストラクタ(未実装)
	~PersonBase()
	{
	}

	// 描画
	virtual void draw() const = 0;

	//////////////////////////////
	// アクセサー
	void set_weapon(WeaponBase* wp)
	{
		this->wp_ = wp;
	}

	WeaponBase* get_weapon() const
	{
		return this->wp_;
	}

	void set_hp(const int hp)
	{
		this->hp_ = hp;
	}

	int get_hp() const
	{
		return this->hp_;
	}

	void set_x(const int x)
	{
		this->pos_.x = x;
	}

	int get_x() const
	{
		return this->pos_.x;
	}

	void set_y(const int y)
	{
		this->pos_.y = y;
	}

	int get_y() const
	{
		return this->pos_.y;
	}

	void set_pos(const Vec2 pos)
	{
		pos_ = pos;
	}

	Vec2 get_pos() const
	{
		return pos_;
	}

private:
	WeaponBase* wp_;
	int hp_;
	Vec2 pos_;
};

#endif
