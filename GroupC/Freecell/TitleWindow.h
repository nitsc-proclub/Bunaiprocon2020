#pragma once
#include"Shared.h"
#include"TitleScene.h"

class TitleWindow :public IEvent, public TitleScene
{
private:
	Font font = Font(50, Typeface::Bold);
	std::shared_ptr<Texture> iconConfig = std::shared_ptr<Texture>(new Texture(Icon(0xf013, 20)));
public:
	bool RunEvent(double per);
};

