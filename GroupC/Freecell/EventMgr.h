#pragma once
#include<Siv3D.hpp>

enum EventType { Function, Class };
class IEvent
{
public:
	virtual bool RunEvent(double per) = 0;
};
struct EventInfo
{
public:
	EventType type;
	std::function<bool(double)> function;
	std::shared_ptr<IEvent> handler;
	std::function<void(EventInfo)> finishedFunc;
	unsigned int startFrame;
	int callCnt;
	~EventInfo()
	{
		handler.~shared_ptr();
	}
};
enum EventPriority
{
	Background,
	Nomal,
	Foreground
};
namespace Event
{
	void Init();

	/// <summary>
	/// イベントを新しく作る
	/// </summary>
	/// <param name="func">コールバック関数</param>
	/// <param name="startFrame">開始フレーム(現在のフレームとの相対位置)</param>
	/// <param name="callCnt">呼び出す回数(0で無限)</param>
	/// <param name="type">イベントの呼び出す優先度</param>
	/// <param name="finished">イベント終了後に呼び出す関数</param>
	void New(std::function<bool(double)> func, int startFrame, int callCnt, EventPriority type = Nomal, std::function<void(EventInfo)> finished = nullptr);

	/// <summary>
	/// イベントを新しく作る
	/// </summary>
	/// <param name="handler">イベントを受け取るクラス</param>
	/// <param name="startFrame">開始フレーム(現在のフレームとの相対位置)</param>
	/// <param name="callCnt">呼び出す回数(0で無限)</param>
	/// <param name="type">イベントの呼び出す優先度</param>
	/// <param name="finished">イベント終了後に呼び出す関数</param>
	void New(std::shared_ptr<IEvent> handler, int startFrame, int callCnt, EventPriority type = Nomal, std::function<void(EventInfo)> finished = nullptr);

	/// <summary>
	/// イベントを新しく作る(簡易版)
	/// </summary>
	/// <param name="func">コールバック関数</param>
	/// <param name="type">イベントの呼び出す優先度</param>
	/// <param name="finished">イベント終了後に呼び出す関数</param>
	void New(std::function<bool(double)> func, EventPriority type = Nomal, std::function<void(EventInfo)> finished = nullptr);

	/// <summary>
	/// イベントを新しく作る(簡易版)
	/// </summary>
	/// <param name="handler">イベントを受け取るクラス</param>
	/// <param name="type">イベントの呼び出す優先度</param>
	/// <param name="finished">イベント終了後に呼び出す関数</param>
	void New(std::shared_ptr<IEvent> handler, EventPriority type = Nomal, std::function<void(EventInfo)> finished = nullptr);

	/// <summary>
	/// 毎フレームに呼び出す処理
	/// </summary>
	void Loop();

	/// <summary>
	/// イベントの数を取得
	/// </summary>
	int GetEventCnt(EventPriority type);
};
