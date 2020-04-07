#pragma once

// インクルードガード
#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <Siv3D.hpp>
#include "Bullet.hpp"


class WeaponBase
{
public:
	WeaponBase()
	{
		
	}

	virtual void update(Vec2 gum_pos) = 0;
	virtual void draw() const = 0;
	virtual Array<Bullet>& getBullets() = 0;

private:
	virtual void shot() = 0;

};

#endif