#pragma once

#include "Common.h"


class Title : public MyApp::Scene
{
private:

public:

    const Font font = Font(40);

    Title(const InitData& init) : IScene(init)
    {
        // �V�[���ǂݍ��ݎ��Ɉ�x�������s�����


    }

    // ���t���[�� updateAndDraw() �ŌĂ΂��
    void update() override
    {
        if (KeySpace.up())
        {
            // ���̃V�[�P���X�ƁA�t�F�[�h�C���E�A�E�g�̎��ԁi�~���b�j
            changeScene(State::Game);
        }
        // ���̃V�[�P���X�ƁA�t�F�[�h�C���E�A�E�g�̎��ԁi�~���b�j    
    }




    // ���t���[�� update() �̎��ɌĂ΂��
    void draw() const override
    {
        TextureAsset(U"Title").scaled(3.5).drawAt(300, 300);
        //�@���S���W(X,Y)�@���̕��@�@�O�p�̕��@�@����
        Line(150, 460, 150, 502)
            .drawArrow(10, Vec2(20, 20), Palette::White);

        Line(174, 423, 218, 423)
            .drawArrow(10, Vec2(20, 20), Palette::White);

        Line(126, 423, 82, 423)
            .drawArrow(10, Vec2(20, 20), Palette::White);

        Line(150, 400, 150, 358)
            .drawArrow(10, Vec2(20, 20), Palette::White);

        font(U"�E�E�E�ړ��L�[").draw(249, 395);

        font(U"Z�L�[�E�E�E�e").draw(370, 520);

        font(U"Space�L�[�ŃX�^�[�g").draw(220, 300);

    }
}; 
