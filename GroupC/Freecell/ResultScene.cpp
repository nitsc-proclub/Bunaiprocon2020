#include"ResultScene.h"
#include"MainScene.h"

Vec2 GetNodeDrawPos(Rect rect, Size gridSize, Point pos)
{
	return Vec2(rect.x + pos.x * rect.w / (gridSize.x - 1), rect.y + pos.y * rect.h / (gridSize.y - 1));
}

void DrawGrid(Rect drawArea, Grid<NodeState> nodeStates)
{
	Color hori = Color(30, 100, 255)/*Œõ‚é‚È‚ç*/;
	Color vert = Color(255, 0, 0);
	for (int x = 0; x < nodeStates.width(); x++)
	{
		for (int y = 0; y < nodeStates.height(); y++)
		{
			auto state = nodeStates.at(y, x);
			auto drawPos = GetNodeDrawPos(drawArea, nodeStates.size(), Point(x, y));
			if (state.Right)
			{
				Line(drawPos + Vec2(4, 0), GetNodeDrawPos(drawArea, nodeStates.size(), Point(x + 1, y)) + Vec2(-4, 0)).draw(4, hori);
			}
			if (state.Bottom)
			{
				Line(drawPos + Vec2(0, 4), GetNodeDrawPos(drawArea, nodeStates.size(), Point(x, y + 1)) + Vec2(0, -4)).draw(4, vert);
			}
		}
	}
}


ResultScene::ResultScene()
{
	Controller::CanShowSoftKey = false;
	Sound::PlayBGM(U"BGMBad2", true, 0, 0, 0.8);
}

void ResultScene::Loop()
{
	Rect gridRect(Arg::center = Scene::Center(), 500);
	bool isSamePos = MainScene::TeamStates[0].Pos == MainScene::TeamStates[1].Pos;
	if (isSamePos)
	{
		font(U"2P(‹S)‚ÌŸ‚¿!").draw(Arg::topCenter = Scene::Rect().topCenter() + Vec2(0, 20), playerColors[1]);
	}
	else
	{
		font(U"1P(l)‚ÌŸ‚¿!").draw(Arg::topCenter = Scene::Rect().topCenter() + Vec2(0, 20), playerColors[0]);
	}
	DrawGrid(gridRect, MainScene::TeamStates[0].NodeStates);
	if (isSamePos)
	{
		auto pos = GetNodeDrawPos(gridRect, MainScene::TeamStates[0].NodeStates.size(), MainScene::TeamStates[0].Pos);
		Circle(pos, 20).draw(Palette::White);
		font(U"1PE2P").draw(Arg::bottomLeft = pos + Vec2(20, -20), Palette::White);
	}
	else
	{
		for (int i = 0; i < MainScene::TeamStates.size(); i++)
		{
			auto pos = GetNodeDrawPos(gridRect, MainScene::TeamStates[0].NodeStates.size(), MainScene::TeamStates[i].Pos);
			Circle(pos, 20).draw(playerColors[i]);
			font(U"{}P"_fmt(i + 1)).draw(Arg::bottomLeft = pos + Vec2(20, -20), playerColors[i]);
		}
	}
}
