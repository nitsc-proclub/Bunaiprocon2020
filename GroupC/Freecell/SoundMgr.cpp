#include "SoundMgr.h"
#include"EventMgr.h"

static bool IsBGMReady = true;
static String PlayingBGM;

String Sound::GetPlayingBGM()
{
	return PlayingBGM;
}

/// <summary>
/// �����t�@�C����ǉ�����
/// </summary>
/// <param name="name">�����t�@�C���̖��O</param>
/// <param name="path">�����t�@�C���̃p�X</param>
/// <returns>����������</returns>
bool Sound::New(String name, String path)
{
	return AudioAsset::Register(name, path, AssetParameter::LoadAsync());
}

/// <summary>
/// BGM���Đ����Ă��邩
/// </summary>
bool Sound::IsBGMPlaying()
{
	if (PlayingBGM.isEmpty())
	{
		return false;
	}
	if (IsBGMReady)
	{
		auto asset = AudioAsset(PlayingBGM);
		if (!asset.isPlaying())
		{
			PlayingBGM = U"";
			return false;
		}
	}
	return true;
}

/// <summary>
/// BGM���~�߂�
/// </summary>
/// <param name="fadeoutSec">�t�F�[�h�A�E�g�b��</param>
/// <returns>����������</returns>
bool Sound::StopBGM(int fadeoutSec)
{
	if (!IsBGMPlaying())
	{
		return false;
	}
	auto asset = AudioAsset(PlayingBGM);
	asset.stop(SecondsF(fadeoutSec));
	IsBGMReady = true;
	PlayingBGM = U"";
	return true;
}

/// <summary>
/// BGM���Đ�����
/// </summary>
/// <param name="name">BGM�̖��O</param>
/// <param name="loop">���[�v���邩</param>
/// <param name="fadeinSec">�t�F�[�h�C���b��</param>
/// <param name="fadeoutSec">�O�ɍĐ����Ă���BGM������ꍇ�A�t�F�[�h�A�E�g�b��</param>
	/// <param name="vol">����(0.0~1.0)</param>
/// <returns>����������</returns>
bool Sound::PlayBGM(String name, bool loop, int fadeinSec, int fadeoutSec, double vol)
{
	if (IsBGMPlaying())
	{
		StopBGM(fadeoutSec);
	}
	if (!AudioAsset::IsRegistered(name))
	{
		return false;
	}
	if (AudioAsset::IsReady(name))
	{
		auto asset = AudioAsset(name);
		asset.setVolume(vol);
		asset.setLoop(true);
		asset.play(SecondsF(fadeinSec));
		IsBGMReady = true;
	}
	else
	{
		Event::New([name, loop, fadeinSec, vol](double per)
			{
				if (name != PlayingBGM)
				{
					return false;
				}
				if (AudioAsset::IsReady(name))
				{
					auto asset = AudioAsset(name);
					asset.setVolume(vol);
					asset.setLoop(loop);
					asset.play(SecondsF(fadeinSec));
					IsBGMReady = true;
					return false;
				}
				return true;
			}
		, 0, 0);
		IsBGMReady = false;
	}
	PlayingBGM = name;
	return true;
}

/// <summary>
/// SE���Đ�����
/// </summary>
/// <param name="name">SE�̖��O</param>
	/// <param name="vol">����(0.0~1.0)</param>
/// <returns>����������</returns>
bool Sound::PlaySE(String name, double vol)
{
	if (!AudioAsset::IsRegistered(name))
	{
		return false;
	}
	auto asset = AudioAsset(name);
	asset.setVolume(vol);
	return asset.play();
}
