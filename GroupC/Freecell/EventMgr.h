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
	/// �C�x���g��V�������
	/// </summary>
	/// <param name="func">�R�[���o�b�N�֐�</param>
	/// <param name="startFrame">�J�n�t���[��(���݂̃t���[���Ƃ̑��Έʒu)</param>
	/// <param name="callCnt">�Ăяo����(0�Ŗ���)</param>
	/// <param name="type">�C�x���g�̌Ăяo���D��x</param>
	/// <param name="finished">�C�x���g�I����ɌĂяo���֐�</param>
	void New(std::function<bool(double)> func, int startFrame, int callCnt, EventPriority type = Nomal, std::function<void(EventInfo)> finished = nullptr);

	/// <summary>
	/// �C�x���g��V�������
	/// </summary>
	/// <param name="handler">�C�x���g���󂯎��N���X</param>
	/// <param name="startFrame">�J�n�t���[��(���݂̃t���[���Ƃ̑��Έʒu)</param>
	/// <param name="callCnt">�Ăяo����(0�Ŗ���)</param>
	/// <param name="type">�C�x���g�̌Ăяo���D��x</param>
	/// <param name="finished">�C�x���g�I����ɌĂяo���֐�</param>
	void New(std::shared_ptr<IEvent> handler, int startFrame, int callCnt, EventPriority type = Nomal, std::function<void(EventInfo)> finished = nullptr);

	/// <summary>
	/// �C�x���g��V�������(�ȈՔ�)
	/// </summary>
	/// <param name="func">�R�[���o�b�N�֐�</param>
	/// <param name="type">�C�x���g�̌Ăяo���D��x</param>
	/// <param name="finished">�C�x���g�I����ɌĂяo���֐�</param>
	void New(std::function<bool(double)> func, EventPriority type = Nomal, std::function<void(EventInfo)> finished = nullptr);

	/// <summary>
	/// �C�x���g��V�������(�ȈՔ�)
	/// </summary>
	/// <param name="handler">�C�x���g���󂯎��N���X</param>
	/// <param name="type">�C�x���g�̌Ăяo���D��x</param>
	/// <param name="finished">�C�x���g�I����ɌĂяo���֐�</param>
	void New(std::shared_ptr<IEvent> handler, EventPriority type = Nomal, std::function<void(EventInfo)> finished = nullptr);

	/// <summary>
	/// ���t���[���ɌĂяo������
	/// </summary>
	void Loop();

	/// <summary>
	/// �C�x���g�̐����擾
	/// </summary>
	int GetEventCnt(EventPriority type);
};
