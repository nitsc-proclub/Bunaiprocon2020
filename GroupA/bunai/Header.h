#pragma once

#include "Common.h"


class Title : public MyApp::Scene
{
private:

public:

    const Font font = Font(40);

    Title(const InitData& init) : IScene(init)
    {
        // シーン読み込み時に一度だけ実行される


    }

    // 毎フレーム updateAndDraw() で呼ばれる
    void update() override
    {
        if (KeySpace.up())
        {
            // 次のシーケンスと、フェードイン・アウトの時間（ミリ秒）
            changeScene(State::Game);
        }
        // 次のシーケンスと、フェードイン・アウトの時間（ミリ秒）    
    }




    // 毎フレーム update() の次に呼ばれる
    void draw() const override
    {
        TextureAsset(U"Title").scaled(3.5).drawAt(300, 300);
        //　中心座標(X,Y)　線の幅　　三角の幅　　高さ
        Line(150, 460, 150, 502)
            .drawArrow(10, Vec2(20, 20), Palette::White);

        Line(174, 423, 218, 423)
            .drawArrow(10, Vec2(20, 20), Palette::White);

        Line(126, 423, 82, 423)
            .drawArrow(10, Vec2(20, 20), Palette::White);

        Line(150, 400, 150, 358)
            .drawArrow(10, Vec2(20, 20), Palette::White);

        font(U"・・・移動キー").draw(249, 395);

        font(U"Zキー・・・弾").draw(370, 520);

        font(U"Spaceキーでスタート").draw(220, 300);

    }
}; 
