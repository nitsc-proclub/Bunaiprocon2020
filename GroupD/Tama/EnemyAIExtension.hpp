#pragma once

// インクルードガード
#ifndef ENEMY_AI_EXTENSION_HPP
#define ENEMY_AI_EXTENSION_HPP

#include <Siv3D.hpp>
#include "EnemyWeaponExtension.hpp"
#include "EnemyAI.hpp"

class EnemyAIDown : public EnemyAIBase
{
public:

	EnemyAIDown() : EnemyAIBase(nullptr)
	{
	}


	EnemyAIDown(WeaponBase* wp) :EnemyAIBase(wp)
	{
		direction_ = Vec2(Random<int>(-5, 5), 10).setLength(6);
	}

	Vec2 update(Vec2 last_pos) override
	{
		Vec2 next_pos = last_pos += direction_;
		get_weapon()->update(next_pos);
		return next_pos;
	}


private:
	Vec2 direction_;
};


class EnemyAIRandomPolygon : public EnemyAIBase
{
public:

	EnemyAIRandomPolygon() : EnemyAIBase(nullptr)
	{
	}


	EnemyAIRandomPolygon(WeaponBase* wp) :EnemyAIBase(wp)
	{
		direction_ = Vec2(Random<int>(-2, 2), 4);
		range_ = Rect(10 ,1 , 780, 580);
	}

	Vec2 update(Vec2 last_pos) override
	{
		Vec2 next_pos = last_pos + direction_;
		if (!range_.intersects(last_pos.asPoint()))
		{
			direction_ = Vec2(Random<int>(-5, 5), Random<int>(-5, 5)).setLength(6);
			last_pos += direction_ * 2;
		}
		get_weapon()->update(next_pos);
		return next_pos;
	}


private:
	Vec2 direction_;
	Rect range_;
};


#endif