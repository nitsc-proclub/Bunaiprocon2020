#include"MainScene.h"
#include"CutInTextEffect.h"
#include"LineFadeEffect.h"
#include"LineBackEffect.h"
#include"TestSkill.h"
#include"ResultWindow.h"

Array<TeamState> MainScene::TeamStates;

Vec2 MainScene::GetNodeDrawPos(Rect rect, Point pos)
{
	return Vec2(rect.x + pos.x * rect.w / (GridSize.x - 1), rect.y + pos.y * rect.h / (GridSize.y - 1));
}

void MainScene::DrawSkillIcon(Rect rect, int guageSize, std::shared_ptr<ISkill> skill)
{
	double per = (double)skill->GuageCnt / skill->GuageMax;
	Color guageCol = skill->GuageCnt == skill->GuageMax ? Palette::Skyblue : Palette::Orange;
	Rect outside(rect.x - guageSize, rect.y - guageSize, rect.w + guageSize * 2, rect.h + guageSize * 2);
	RasterizerState rasterizer = RasterizerState::Default2D;
	rasterizer.scissorEnable = true;
	ScopedRenderStates2D r(rasterizer);

	Graphics2D::SetScissorRect(outside);
	outside.draw(Color(Palette::Gray, 200));
	Circle(outside.center(), Max(outside.w, outside.h) * 0.8).drawPie(315_deg, Math::Pi * 2 * per, guageCol);
	rect.draw(Palette::White).drawFrame(1, Palette::Black);
	skill->SkillImage.draw(rect.pos);
}

void MainScene::DrawGrid(Rect drawArea, Grid<NodeState> nodeStates, HighlightColor col)
{
	Color hori = col == HighlightColor::Horizontal ? Color(30, 100, 255)/*光るなら*/ : Color(190, 205, 255, 80)/*光らないなら*/;
	Color vert = col == HighlightColor::Vertical ? Color(255, 0, 0) : Color(232, 155, 145, 91);
	for (int x = 0; x < nodeStates.width(); x++)
	{
		for (int y = 0; y < nodeStates.height(); y++)
		{
			auto state = nodeStates.at(y, x);
			auto drawPos = GetNodeDrawPos(drawArea, Point(x, y));
			if (state.Right)
			{
				Line(drawPos + Vec2(4, 0), GetNodeDrawPos(drawArea, Point(x + 1, y)) + Vec2(-4, 0)).draw(4, hori);
			}
			if (state.Bottom)
			{
				Line(drawPos + Vec2(0, 4), GetNodeDrawPos(drawArea, Point(x, y + 1)) + Vec2(0, -4)).draw(4, vert);
			}
		}
	}
}

void MainScene::GameEnd()
{
	Event::New(std::shared_ptr<IEvent>(new CutInTextEffect(U"ゲーム終了", UIFont)), 0, 300, Foreground,
		[this](EventInfo info)
		{
			Event::New(std::shared_ptr<IEvent>(new ResultWindow()), 0, 0);
			IsContinue = false;
		});
	CullentScene = SubScene::End;
	Sound::StopBGM(0.1);
	Sound::PlaySE(U"SEWhistle");
}

void MainScene::ChangeTeamTurn()
{
	auto state = &TeamStates[TeamTurn];
	switch (state->MovDirection)
	{
	case MoveDirection::Up:
		state->Pos += Point(0, -1);
		TeamStates[!TeamTurn].Highlight = HighlightColor::Vertical;
		break;
	case MoveDirection::Down:
		state->Pos += Point(0, 1);
		TeamStates[!TeamTurn].Highlight = HighlightColor::Vertical;
		break;
	case MoveDirection::Left:
		state->Pos += Point(-1, 0);
		TeamStates[!TeamTurn].Highlight = HighlightColor::Horizontal;
		break;
	case MoveDirection::Right:
		state->Pos += Point(1, 0);
		TeamStates[!TeamTurn].Highlight = HighlightColor::Horizontal;
		break;
	}
	state->MovDirection = MoveDirection::Unspecified;
	TeamTurn = !TeamTurn;
	CullentScene = SubScene::Transition;
	SkillCursor = 0;
	if (!TeamTurn)
	{
		ChangeTurn();
	}
	Sound::PlaySE(U"SEBell");
}

void MainScene::ChangeTurn()
{
	IsSkillSelecting = false;
	for (int j = 0; j < TeamStates.size(); j++)
	{
		auto state = &TeamStates[j];
		for (int i = 0; i < state->Skills.size(); i++)
		{
			auto skill = state->Skills[i];
			skill->GuageCnt = Min(skill->GuageCnt + 1, skill->GuageMax);
			if (skill->IsRun)
			{
				skill->Run(&TeamStates, j);
				skill->GuageCnt = 0;
				skill->IsRun = false;
			}
		}
	}
	bool IsNearOld = IsNear;
	double distance = TeamStates[0].Pos.distanceFrom(TeamStates[1].Pos);
	IsNear = distance <= 1.5;
	if (IsNear != IsNearOld)
	{
		if (IsNear)
		{
			Sound::PlayBGM(U"BGMGood", true, 1, 1, 0.8);
		}
		else
		{
			Sound::PlayBGM(U"BGMIdle1", true, 1, 1, 0.8);
		}
	}
	if (distance == 0)
	{
		GameEnd();
		return;
	}
	if (Turn == MaxTurn)
	{
		GameEnd();
		return;
	}
	Turn++;
}

void MainScene::SubScene_Transition()
{
	PlayGuide = U"[Select]進む";
	auto controller = ControllerCfgs[TeamTurn];
	auto rect = UIFont(U"{}Pの番です"_fmt(TeamTurn + 1)).drawAt(MainRect.center());
	UISubFont(U"[Select]を押してください").draw(Arg::topCenter = rect.bottomCenter() + Vec2(0, 3));

	if (controller.Select.down())
	{
		CullentScene = SubScene::Action;
	}
}

void MainScene::SubScene_Action()
{
	auto state = &TeamStates[TeamTurn];
	auto controller = ControllerCfgs[TeamTurn];

	if (IsSkillSelecting)
	{
		if (controller.Cancel.down())
		{
			IsSkillSelecting = false;
		}
		else
		{
			if (controller.L.down())
			{
				if (SkillCursor == 0)
				{
					Sound::PlaySE(U"SEBeep");
				}
				else
				{
					SkillCursor--;
				}
			}
			if (controller.R.down())
			{
				if (SkillCursor == state->Skills.size() - 1)
				{
					Sound::PlaySE(U"SEBeep");
				}
				else
				{
					SkillCursor++;
				}
			}
			if (controller.Select.down())
			{
				auto skill = state->Skills[SkillCursor];
				if (skill->GuageCnt == skill->GuageMax)
				{
					skill->IsRun = !skill->IsRun;
				}
			}
		}
		PlayGuide = U"[L/R]スキル選択　[Cancel]戻る　[Select]スキル切替";
	}
	else
	{
		PlayGuide = U"[╋]移動　[L/R]スキル選択";
		if (controller.L.down() || controller.R.down())
		{
			IsSkillSelecting = true;
		}

		if (controller.PreviousPov != controller.Pov)
		{
			switch (controller.Pov)
			{
			case Controller::PovDirection::Up:
				//上
				if (state->Pos.y <= 0)
				{
					Sound::PlaySE(U"SEBeep");
					break;
				}
				if (state->NodeStates.at(state->Pos + Point(0, -1)).Bottom)
				{
					state->MovDirection = Up;
				}
				else
				{
					Sound::PlaySE(U"SEBeep");
				}
				break;
			case Controller::PovDirection::Down:
				//下
				if (state->NodeStates.at(state->Pos).Bottom)
				{
					state->MovDirection = Down;
				}
				else
				{
					Sound::PlaySE(U"SEBeep");
				}
				break;
			case Controller::PovDirection::Right:
				//右
				if (state->NodeStates.at(state->Pos).Right)
				{
					state->MovDirection = Right;
				}
				else
				{
					Sound::PlaySE(U"SEBeep");
				}
				break;
			case Controller::PovDirection::Left:
				//左
				if (state->Pos.x <= 0)
				{
					Sound::PlaySE(U"SEBeep");
					break;
				}
				if (state->NodeStates.at(state->Pos + Point(-1, 0)).Right)
				{
					state->MovDirection = Left;
				}
				else
				{
					Sound::PlaySE(U"SEBeep");
				}
				break;
			}
		}
		if (state->MovDirection != MoveDirection::Unspecified)
		{
			PlayGuide += U"　[Select]確定";
			if (controller.Select.down())
			{
				ChangeTeamTurn();
				return;
			}
		}
	}

	auto drawPos = GetNodeDrawPos(GridRect, state->Pos);
	DrawGrid(GridRect, state->NodeStates, state->Highlight);

	double deg = 0;
	switch (state->MovDirection)
	{
	case Up:
		deg = 0;
		break;
	case Right:
		deg = 90_deg;
		break;
	case Down:
		deg = 180_deg;
		break;
	case Left:
		deg = 270_deg;
		break;
	}
	if (state->MovDirection != Unspecified)
	{
		Line(drawPos, OffsetCircular(drawPos, 50, deg)).drawArrow(10, Vec2(10, 10));
	}
	Circle(drawPos, 20).draw(Palette::Lightyellow);

	if (IsSkillSelecting)
	{
		SkillRect.draw(Color(Palette::White, 100));
	}

	double startX = -(double)(state->Skills.size() - 1) * 80.0 / 2;
	for (int i = 0; i < state->Skills.size(); i++)
	{
		Rect skill(Arg::center = (SkillRect.center() + Vec2(startX + i * 80, 0.0)).asPoint(), 50);
		Rect forcus(skill.x - 12, skill.y - 12, skill.w + 12 * 2, skill.h + 12 * 2);
		DrawSkillIcon(skill, 6, state->Skills[i]);
		if (state->Skills[i]->IsRun)
		{
			forcus.drawFrame(3, Palette::Pink);
		}
		if (IsSkillSelecting)
		{
			if (i == SkillCursor)
			{
				forcus.drawFrame(3, Color(Palette::Red, 255 * Periodic::Triangle0_1(1s)));
			}
		}
	}
}

MainScene::MainScene()
{
	IsContinue = true;
	CullentScene = SubScene::Transition;
	TeamStates = {
		TeamState(GridSize,Point(0,4),{std::shared_ptr<ISkill>(new TestSkill()),std::shared_ptr<ISkill>(new TestSkill())}),
		TeamState(GridSize,Point(4,0),{std::shared_ptr<ISkill>(new TestSkill()),std::shared_ptr<ISkill>(new TestSkill())}) };
	interval = Stopwatch(true);
	UIFont = Font(24);
	UISubFont = Font(16);
	MaxTurn = 15;
	Sound::PlayBGM(U"BGMIdle1", true, 0, 0, 0.8);
	Sound::PlaySE(U"SEBell");
}

bool MainScene::Loop()
{
	switch (CullentScene)
	{
	case MainScene::Action:
		SubScene_Action();
		break;
	case MainScene::Transition:
		SubScene_Transition();
		break;
	}
	UIFont(U"ターン：{}/{}"_fmt(Turn, MaxTurn)).draw(MainRect.pos + Vec2(5, 25));
	if (CullentScene != End)
	{
		UIFont(U"{}P({})の番"_fmt(TeamTurn + 1, TeamTurn ? U"鬼" : U"人")).draw(MainRect.pos + Vec2(5, 25 + 30 * 1));
		if (IsNear)
		{
			UIFont(U"接近中!!").draw(MainRect.pos + Vec2(5, 25 + 30 * 2), Palette::Lightpink);
		}
		UISubFont(PlayGuide).draw(Arg::rightCenter = GuideRect.rightCenter() - Point(5, 0), Palette::Whitesmoke);
		if (IsNear)
		{
			if (interval.sF() >= 0.1)
			{
				Event::New(std::shared_ptr<IEvent>(new LineBackEffect(7)), 0, 60, Background);
				interval.restart();
			}
		}
		else
		{
			if (interval.sF() >= 1)
			{
				Event::New(std::shared_ptr<IEvent>(new LineFadeEffect(2)), 0, 420, Background);
				interval.restart();
			}
		}
	}
	return IsContinue;
}

