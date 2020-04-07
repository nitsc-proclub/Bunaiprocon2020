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
/// �C�x���g��V�������
/// </summary>
/// <param name="func">�R�[���o�b�N�֐�</param>
/// <param name="startFrame">�J�n�t���[��(���݂̃t���[���Ƃ̑��Έʒu)</param>
/// <param name="callCnt">�Ăяo����(0�Ŗ���)</param>
/// <param name="type">�C�x���g�̌Ăяo���D��x</param>
	/// <param name="finished">�C�x���g�I����ɌĂяo���֐�</param>
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
/// �C�x���g��V�������
/// </summary>
/// <param name="handler">�C�x���g���󂯎��N���X</param>
/// <param name="startFrame">�J�n�t���[��(���݂̃t���[���Ƃ̑��Έʒu)</param>
/// <param name="callCnt">�Ăяo����(0�Ŗ���)</param>
/// <param name="type">�C�x���g�̌Ăяo���D��x</param>
	/// <param name="finished">�C�x���g�I����ɌĂяo���֐�</param>
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
/// �C�x���g��V�������(�ȈՔ�)
/// </summary>
/// <param name="func">�R�[���o�b�N�֐�</param>
/// <param name="type">�C�x���g�̌Ăяo���D��x</param>
	/// <param name="finished">�C�x���g�I����ɌĂяo���֐�</param>
void Event::New(std::function<bool(double)> func, EventPriority type, std::function<void(EventInfo)> finished)
{
	New(func, 0, 1, type, finished);
}

/// <summary>
/// �C�x���g��V�������(�ȈՔ�)
/// </summary>
/// <param name="handler">�C�x���g���󂯎��N���X</param>
/// <param name="type">�C�x���g�̌Ăяo���D��x</param>
	/// <param name="finished">�C�x���g�I����ɌĂяo���֐�</param>
void Event::New(std::shared_ptr<IEvent> handler, EventPriority type, std::function<void(EventInfo)> finished)
{
	New(handler, 0, 1, type, finished);
}

/// <summary>
/// ���t���[���ɌĂяo������
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
