#pragma once
#include<Siv3D.hpp>

namespace Sound
{
	/// <summary>
	/// �Đ�����BGM���擾
	/// </summary>
	String GetPlayingBGM();
	/// <summary>
	/// �����t�@�C����ǉ�����
	/// </summary>
	/// <param name="name">�����t�@�C���̖��O</param>
	/// <param name="path">�����t�@�C���̃p�X</param>
	/// <returns>����������</returns>
	bool New(String name, String path);
	/// <summary>
	/// BGM���Đ����Ă��邩
	/// </summary>
	bool IsBGMPlaying();
	/// <summary>
	/// BGM���~�߂�
	/// </summary>
	/// <param name="fadeoutSec">�t�F�[�h�A�E�g�b��</param>
	/// <returns>����������</returns>
	bool StopBGM(int fadeoutSec = 0);
	/// <summary>
	/// BGM���Đ�����
	/// </summary>
	/// <param name="name">BGM�̖��O</param>
	/// <param name="loop">���[�v���邩</param>
	/// <param name="fadeinSec">�t�F�[�h�C���b��</param>
	/// <param name="fadeoutSec">�O�ɍĐ����Ă���BGM������ꍇ�A�t�F�[�h�A�E�g�b��</param>
	/// <param name="vol">����(0.0~1.0)</param>
	/// <returns>����������</returns>
	bool PlayBGM(String name, bool loop = true, int fadeinSec = 0, int fadeoutSec = 0, double vol = 1);
	/// <summary>
	/// SE���Đ�����
	/// </summary>
	/// <param name="name">SE�̖��O</param>
	/// <param name="vol">����(0.0~1.0)</param>
	/// <returns>����������</returns>
	bool PlaySE(String name, double vol = 1);
}
