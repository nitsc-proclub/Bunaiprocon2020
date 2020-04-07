#include"EventMgr.h"

Array<EventInfo*> BackEvents;
Array<EventInfo*> NomalEvents;
Array<EventInfo*> ForeEvents;
unsigned int CullentFrame;

Array<EventInfo*> BackAddQueue;
Array<EventInfo*> NomalAddQueue;
Array<EventInfo*> ForeAddQueue;

void prgEvents(Array<EventInfo*>* events)
{
	for (int i = 0; i < events->size(); i++)
	{
		EventInfo* ev = (*events)[i];
		int length = ev->callCnt - 1;
		if ((int)(CullentFrame - ev->startFrame) == length)
		{
			if (ev->finishedFunc != nullptr)
			{
				(ev->finishedFunc)(*ev);
			}
			ev->~EventInfo();
			events->remove_at(i);
			i--;
			continue;
		}
		if (ev->startFrame <= CullentFrame)
		{
			double per = (double)(CullentFrame - ev->startFrame) / length;
			bool result = false;
			switch (ev->type)
			{
			case Function:
				result = ev->function(per);
				break;
			case Class:
				result = ev->handler->RunEvent(per);
				break;
			}
			if (result == false)
			{
				if (ev->finishedFunc != nullptr)
				{
					(ev->finishedFunc)(*ev);
				}
				ev->~EventInfo();
				events->remove_at(i);
				i--;
				continue;
			}
		}
	}
}

void addEvents(Array<EventInfo*>* events, Array<EventInfo*>* queue)
{
	for (auto ev : *queue)
	{
		events->push_back(ev);
	}
	queue->clear();
}

void Event::Init()
{
	CullentFrame = 0;
}

/// <summary>
/// イベントを新しく作る
/// </summary>
/// <param name="func">コールバック関数</param>
/// <param name="startFrame">開始フレーム(現在のフレームとの相対位置)</param>
/// <param name="callCnt">呼び出す回数(0で無限)</param>
/// <param name="type">イベントの呼び出す優先度</param>
	/// <param name="finished">イベント終了後に呼び出す関数</param>
void Event::New(std::function<bool(double)> func, int startFrame, int callCnt, EventPriority type, std::function<void(EventInfo)> finished)
{
	EventInfo* ev = new EventInfo();
	ev->type = Function;
	ev->function = func;
	ev->startFrame = CullentFrame + startFrame;
	ev->callCnt = callCnt;
	ev->finishedFunc = finished;
	switch (type)
	{
	case Background:
		BackAddQueue.push_back(ev);
		break;
	case Nomal:
		NomalAddQueue.push_back(ev);
		break;
	case Foreground:
		ForeAddQueue.push_back(ev);
		break;
	}
}

/// <summary>
/// イベントを新しく作る
/// </summary>
/// <param name="handler">イベントを受け取るクラス</param>
/// <param name="startFrame">開始フレーム(現在のフレームとの相対位置)</param>
/// <param name="callCnt">呼び出す回数(0で無限)</param>
/// <param name="type">イベントの呼び出す優先度</param>
	/// <param name="finished">イベント終了後に呼び出す関数</param>
void Event::New(std::shared_ptr<IEvent> handler, int startFrame, int callCnt, EventPriority type, std::function<void(EventInfo)> finished)
{
	EventInfo* ev = new EventInfo();
	ev->type = Class;
	ev->handler = handler;
	ev->startFrame = CullentFrame + startFrame;
	ev->callCnt = callCnt;
	ev->finishedFunc = finished;
	switch (type)
	{
	case Background:
		BackAddQueue.push_back(ev);
		break;
	case Nomal:
		NomalAddQueue.push_back(ev);
		break;
	case Foreground:
		ForeAddQueue.push_back(ev);
		break;
	}
}

/// <summary>
/// イベントを新しく作る(簡易版)
/// </summary>
/// <param name="func">コールバック関数</param>
/// <param name="type">イベントの呼び出す優先度</param>
	/// <param name="finished">イベント終了後に呼び出す関数</param>
void Event::New(std::function<bool(double)> func, EventPriority type, std::function<void(EventInfo)> finished)
{
	New(func, 0, 1, type, finished);
}

/// <summary>
/// イベントを新しく作る(簡易版)
/// </summary>
/// <param name="handler">イベントを受け取るクラス</param>
/// <param name="type">イベントの呼び出す優先度</param>
	/// <param name="finished">イベント終了後に呼び出す関数</param>
void Event::New(std::shared_ptr<IEvent> handler, EventPriority type, std::function<void(EventInfo)> finished)
{
	New(handler, 0, 1, type, finished);
}

/// <summary>
/// 毎フレームに呼び出す処理
/// </summary>
void Event::Loop()
{
	addEvents(&BackEvents, &BackAddQueue);
	addEvents(&NomalEvents, &NomalAddQueue);
	addEvents(&ForeEvents, &ForeAddQueue);
	prgEvents(&BackEvents);
	prgEvents(&NomalEvents);
	prgEvents(&ForeEvents);
	CullentFrame++;
}

int Event::GetEventCnt(EventPriority type)
{
	switch (type)
	{
	case Background:
		return BackEvents.size();
	case Nomal:
		return NomalEvents.size();
	case Foreground:
		return ForeEvents.size();
	}
	return 0;
}
