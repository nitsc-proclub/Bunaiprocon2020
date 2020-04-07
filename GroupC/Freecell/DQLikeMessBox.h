#pragma once
#include"Shared.h"

class DQLikeMessBox :
	public IEvent
{
private:
	//Font
	static int fontPx;
	static std::unique_ptr<Font> font;
	//�X�^�C��
	static std::unique_ptr<Texture> arrow;
	int maxcol = 23;//��
	int maxrow = 3;//�s
	int rowspace = -1;//�s��px
	int nameXpos = 15;//���O�\����x���W
	Size mainPadding = Size(12, 8);//���C���\���̋�
	Size namePadding = Size(5, 3);//���O�\���̋�
	//�ݒ�l
	Image mainImage;
	DynamicTexture mainTexture;
	RoundRect mainRect;
	RoundRect nameRect;
	Polygon messboxPoly;
	Array<String> rows;
	String Name;
	int cullentCol;//�r���̗�
	int cullentRow;//�r���̍s
	int cullentDrawCol;//�r���̕`�悷���
	int cullentDrawRow;//�r���̕`�悷��s
	bool waitKeyFlg;//�L�[���͑҂��t���O
	bool textEnd;//�e�L�X�g�I���t���O
public:
	DQLikeMessBox(String txt, String name = U"")
	{
		if (!font)
		{
			font = std::unique_ptr<Font>(new Font(fontPx, Typeface::Medium));
		}
		if (!arrow)
		{
			arrow = std::unique_ptr<Texture>(new Texture(Icon(0xf0d7, 20)));
		}
		rows = txt.split('\n');

		Name = name;
		auto scSize = Scene::Size();
		mainRect = RoundRect(0, 0, mainPadding.x * 2 + fontPx * maxcol, mainPadding.y * 2 + font->height() * maxrow + rowspace * (maxrow - 1), 5);
		mainRect.x = (scSize.x - mainRect.w) / 2;
		mainRect.y = scSize.y - mainRect.h - 20;
		messboxPoly = mainRect.asPolygon();

		if (Name.length() > 0)
		{
			nameRect = RoundRect(mainRect.x + nameXpos, mainRect.y - fontPx - namePadding.y - 3, namePadding.x * 2 + fontPx * Name.size(), namePadding.y * 2 + font->height() + 3, 5);
			messboxPoly.append(nameRect.asPolygon());
		}

		mainImage = Image(mainRect.w - mainPadding.x * 2, mainRect.h - mainPadding.y * 2);

		cullentCol = 0;
		cullentRow = 0;
		waitKeyFlg = false;
		textEnd = false;
	}

	bool RunEvent(double per)
	{
		bool isContinue = true;
		bool enterDown = KeyEnter.down();
		messboxPoly.draw(Color(Palette::Black, 180)).drawFrame(3, Palette::Black).drawFrame(2, Palette::White);

		if (waitKeyFlg)
		{
			if (enterDown)
			{
				waitKeyFlg = false;
				if (textEnd)
				{
					isContinue = false;
				}
			}	
			arrow->draw(Vec2(mainRect.x + (mainRect.w - arrow->width()) / 2,
				mainRect.y + mainRect.h - arrow->height() - (mainPadding.y - arrow->height()) / 2), Palette::White);
		}
		else
		{
			do
			{
				auto row = rows[cullentRow];
				if (row.length() != 0)
				{
					auto chr = row[cullentCol];
					switch (chr)
					{
					case '@':
						waitKeyFlg = true;
						break;
					default:
						(*font)(chr).overwrite(mainImage, fontPx * cullentDrawCol, (font->height() + rowspace) * cullentDrawRow, Palette::White);
						mainTexture.fill(mainImage);
						cullentDrawCol++;
						break;
					}
				}
				cullentCol++;
				if (cullentCol >= row.length())
				{
					cullentCol = 0;
					cullentDrawCol = 0;
					cullentRow++;
					cullentDrawRow++;
					if (cullentRow >= rows.size())
					{
						waitKeyFlg = true;
						textEnd = true;
					}
					else if (cullentDrawRow >= maxrow)
					{
						Image tmp(mainImage);
						mainImage.fill(Color(0, 0, 0, 0));
						tmp.overwrite(mainImage, 0, -font->height() - rowspace);
						cullentDrawRow = 2;
					}
				}
			} while (enterDown && !waitKeyFlg);
		}

		if (Name.length() > 0)
		{
			(*font)(Name).draw(Vec2(nameRect.x + namePadding.x, nameRect.y + namePadding.y), Palette::White);
		}
		mainTexture.draw(mainRect.x + mainPadding.x, mainRect.y + mainPadding.y);

		return isContinue;
	}
};

int DQLikeMessBox::fontPx = 16;
std::unique_ptr<Font> DQLikeMessBox::font;
std::unique_ptr<Texture> DQLikeMessBox::arrow;