#pragma once

// �C���N���[�h�K�[�h
#ifndef USER_HPP
#define USER_HPP

#include "Person.hpp"

// �����Ƀp�[�\������h���������[�U�[�̃N���X���L�q����
class User : public PersonBase
{
public:
	User() : User(nullptr, 0, Vec2(0, 0), 0)
	{
	}

	User(WeaponBase* wp, const int hp, const Vec2 pos, const int item): PersonBase(wp, hp, pos), item_(item)
	{
	}

	// �f�X�g���N�^(������)
	~User()
	{
	}

	void draw() const override final
	{
		// �������ł������܂�
		ClearPrint();
		Print(this->get_hp());
		Print(this->get_weapon());
		Print(this->get_x());
		Print(this->get_y());
		Print(this->get_item());
		
	}

	///////////////////////
	// �A�N�Z�T�[
	void set_item(const int item)
	{
		this->item_ = item;
	}

	int get_item() const
	{
		return this->item_;
	}

private:
	int item_;
};

#endif
