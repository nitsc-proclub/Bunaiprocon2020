#pragma once
#include"Shared.h"

class MainScene
{
private:
	enum SubScene
	{
		Action, Transition, End
	};

	const int GuideHeight = 24;
	const Rect GuideRect = Rect(0, Scene::Height() - GuideHeight, Scene::Width(), GuideHeight);
	const Rect MainRect = Rect(0, 0, Scene::Width(), Scene::Height() - GuideHeight);
	const int SkillHeight = 90;
	const Rect SkillRect = Rect(MainRect.bl() - Point(0, SkillHeight), Size(MainRect.w, SkillHeight));
	const Size GridDrawSize = Size(500, 500);
	Rect GridRect = Rect(MainRect.center().asPoint() - GridDrawSize / 2, GridDrawSize);
	Size GridSize = Size(5, 5);

	Vec2 GetNodeDrawPos(Rect rect, Point pos);
	void DrawSkillIcon(Rect rect, int guageSize, std::shared_ptr<ISkill> skill);
	void DrawGrid(Rect drawArea, Grid<NodeState> nodeStates, HighlightColor col);
	void GameEnd();
	void ChangeTeamTurn();
	void ChangeTurn();
	void SubScene_Transition();
	void SubScene_Action();
	SubScene CullentScene;
	bool IsSkillSelecting = false;
	bool IsNear = false;
	bool IsContinue;
	int SkillCursor = 0;
	Stopwatch interval;
	String PlayGuide;
	Font UIFont;
	Font UISubFont;
protected:
	Image image = Image(U"example/siv3d-kun.png");
	int Turn;
	int TeamTurn;
	int MaxTurn;

	MainScene();

	bool Loop();
public:
	static Array<TeamState> TeamStates;
};

