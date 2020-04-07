#include "SoundMgr.h"
#include"EventMgr.h"

static bool IsBGMReady = true;
static String PlayingBGM;

String Sound::GetPlayingBGM()
{
	return PlayingBGM;
}

/// <summary>
/// 音声ファイルを追加する
/// </summary>
/// <param name="name">音声ファイルの名前</param>
/// <param name="path">音声ファイルのパス</param>
/// <returns>成功したか</returns>
bool Sound::New(String name, String path)
{
	return AudioAsset::Register(name, path, AssetParameter::LoadAsync());
}

/// <summary>
/// BGMを再生しているか
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
/// BGMを止める
/// </summary>
/// <param name="fadeoutSec">フェードアウト秒数</param>
/// <returns>成功したか</returns>
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
/// BGMを再生する
/// </summary>
/// <param name="name">BGMの名前</param>
/// <param name="loop">ループするか</param>
/// <param name="fadeinSec">フェードイン秒数</param>
/// <param name="fadeoutSec">前に再生しているBGMがある場合、フェードアウト秒数</param>
	/// <param name="vol">音量(0.0~1.0)</param>
/// <returns>成功したか</returns>
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
/// SEを再生する
/// </summary>
/// <param name="name">SEの名前</param>
	/// <param name="vol">音量(0.0~1.0)</param>
/// <returns>成功したか</returns>
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
