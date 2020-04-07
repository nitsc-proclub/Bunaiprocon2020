#pragma once
class Constant
{
public:
	static const int windowWidth = 960; //�E�B���h�E�̕�
	static const int windowHeight = 540; //�E�B���h�E�̍���

	static const int buildingHeight = windowHeight * 4/5; //�r���̍���
	static const int groundHeight = windowHeight * 1/36; //�n�ʂ̍���
	static const int humanHeight = windowHeight / 4; //�l�Ԃ̍���
	static const int humanWidth = humanHeight / 2; //�l�Ԃ̕�
	static const int creatureWidth = humanWidth; //�������̕�
	static const int creatureHeight = creatureWidth * 36 / 98; //�������̍���
	static const int walletWidth = humanWidth/1.5; //���z�̕�
	static const int walletHeight = walletWidth * 42/54; //���z�̍���
	static const int playerSpeed = 10; //�v���C���[�̈ړ��X�s�[�h
	static const int scrollSpeed = 1; //�X�N���[���X�s�[�h
	static const int creatureSpeed = scrollSpeed + 1; //�������̈ړ��X�s�[�h
	static const int buddhaSpeed = scrollSpeed;
	static const int moneySpeedY = 3;
	static const int moneySpeedX = 3;
};

