#pragma once
#include"Shared.h"

class ResultScene
{
private:
	Font font = Font(40);
	Array<Color> playerColors = { Color(Palette::Dodgerblue,220),Color(Palette::Pink,220) };
public:
	ResultScene();
	void Loop();
};