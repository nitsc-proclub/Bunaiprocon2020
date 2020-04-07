#pragma once

// �C���N���[�h�K�[�h
#ifndef ENEMY_AI_HPP
#define ENEMY_AI_HPP

#include <Siv3D.hpp>
#include "Weapon.hpp"

class EnemyAIBase
{
public:

	EnemyAIBase() : EnemyAIBase(nullptr)
	{
	}

	
	EnemyAIBase(WeaponBase* wp) : wp_(wp)
	{
	}

	virtual Vec2 update(Vec2 last_pos) = 0;

	//////////////////////////////
	// �A�N�Z�T�[
	void set_weapon(WeaponBase* wp)
	{
		this->wp_ = wp;
	}

	WeaponBase* get_weapon() const
	{
		return this->wp_;
	}

private:
	WeaponBase* wp_;
};

#endif