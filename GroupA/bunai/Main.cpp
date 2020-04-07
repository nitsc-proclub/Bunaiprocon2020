
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Game.h"
# include "Title.h"
# include "Result.h"
# include "Common.h"

void Main()
{
	MyApp manager;

	manager
		.add<Title>(State::Title)
		.add<Game>(State::Game);

	manager.init(State::Title);
	FontAsset::Register(U"Result", 80);

	TextureAsset::Register(U"Title", U"example/Title.jpg");
	TextureAsset::Register(U"Sakujo", U"example/sakujo.png");
	TextureAsset::Register(U"Yaju", U"example/yaju.jpeg");
	TextureAsset::Register(U"Itsuka", U"example/itsuka.jpeg");
	TextureAsset::Register(U"Yaju#b", U"example/yaju#Bullets.jpg");


	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
};


