#pragma once
#include<Siv3D.hpp>

enum HighlightColor {
	/// <summary>
	/// ‚È‚µ
	/// </summary>
	None,
	/// <summary>
	/// …•½•ûŒü
	/// </summary>
	Horizontal,
	/// <summary>
	/// ‚’¼•ûŒü
	/// </summary>
	Vertical
};

struct NodeState
{
	bool Right;
	bool Bottom;
};

enum MoveDirection
{
	/// <summary>
	/// –¢w’è
	/// </summary>
	Unspecified,
	/// <summary>
	/// ã
	/// </summary>
	Up,
	/// <summary>
	/// ‰E
	/// </summary>
	Right,
	/// <summary>
	/// ‰º
	/// </summary>
	Down,
	/// <summary>
	/// ¶
	/// </summary>
	Left
};

struct TeamState;

class ISkill
{
public:
	Texture SkillImage;
	int GuageCnt = 0;
	int GuageMax = 1;
	bool IsRun = false;
	virtual void Init(Array<TeamState>* teamStates, int myTeam) {};
	virtual void Run(Array<TeamState>* teamStates, int myTeam) {};
};

struct TeamState
{
	TeamState(Size GridSize, Point StartPos, Array<std::shared_ptr<ISkill>> skills)
	{
		NodeStates = Grid<NodeState>(GridSize);
		for (int x = 0; x < GridSize.x; x++)
		{
			for (int y = 0; y < GridSize.y; y++)
			{
				NodeState state;
				state.Right = (x != GridSize.x - 1);
				state.Bottom = (y != GridSize.y - 1);
				NodeStates[Point(x, y)] = state;
			}
		}
		Highlight = None;
		Pos = StartPos;
		MovDirection = Unspecified;
		Skills = skills;
	}
	HighlightColor Highlight;
	Grid<NodeState> NodeStates;
	MoveDirection MovDirection;
	Array<std::shared_ptr<ISkill>> Skills;
	Point Pos;
};

extern String Title;