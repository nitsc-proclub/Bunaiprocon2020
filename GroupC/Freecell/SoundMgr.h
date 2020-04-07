#pragma once
#include<Siv3D.hpp>

namespace Sound
{
	/// <summary>
	/// 再生中のBGMを取得
	/// </summary>
	String GetPlayingBGM();
	/// <summary>
	/// 音声ファイルを追加する
	/// </summary>
	/// <param name="name">音声ファイルの名前</param>
	/// <param name="path">音声ファイルのパス</param>
	/// <returns>成功したか</returns>
	bool New(String name, String path);
	/// <summary>
	/// BGMを再生しているか
	/// </summary>
	bool IsBGMPlaying();
	/// <summary>
	/// BGMを止める
	/// </summary>
	/// <param name="fadeoutSec">フェードアウト秒数</param>
	/// <returns>成功したか</returns>
	bool StopBGM(int fadeoutSec = 0);
	/// <summary>
	/// BGMを再生する
	/// </summary>
	/// <param name="name">BGMの名前</param>
	/// <param name="loop">ループするか</param>
	/// <param name="fadeinSec">フェードイン秒数</param>
	/// <param name="fadeoutSec">前に再生しているBGMがある場合、フェードアウト秒数</param>
	/// <param name="vol">音量(0.0~1.0)</param>
	/// <returns>成功したか</returns>
	bool PlayBGM(String name, bool loop = true, int fadeinSec = 0, int fadeoutSec = 0, double vol = 1);
	/// <summary>
	/// SEを再生する
	/// </summary>
	/// <param name="name">SEの名前</param>
	/// <param name="vol">音量(0.0~1.0)</param>
	/// <returns>成功したか</returns>
	bool PlaySE(String name, double vol = 1);
}
