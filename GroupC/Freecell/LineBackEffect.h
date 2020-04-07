#pragma once
#include"Shared.h"

/// <summary>
/// ������ʉ��ւƐi��ł����G�t�F�N�g
/// </summary>
class LineBackEffect :
	public IEvent
{
private:
	struct LineInfo
	{
		Line3D Line;
		Vec3 MovLen;
	};

	float near = 0.1;
	float far = 100;
	//�������e�s��
	Mat4x4 mat;
	Array<LineInfo> lineinfo;
public:
	/// <summary>
	/// ������ʉ��ւƐi��ł����G�t�F�N�g
	/// </summary>
	/// <param name="rectCnt">���̐�</param>
	/// <param name="maxMovLen">�����ړ�����ő勗��</param>
	/// <param name="fov">����p</param>
	LineBackEffect(int lineCnt, double maxMovLen = 10, double fov = 45_deg)
	{
		auto scRect = Scene::Rect();
		scRect.pos -= scRect.center().asPoint();
		mat = Mat4x4::PerspectiveFovLH_ZO(fov, scRect.w / scRect.h, near, far);
		lineinfo = Array<LineInfo>(lineCnt);
		for (int i = 0; i < lineCnt; i++)
		{
			LineInfo info;
			Vec2 pos = RandomVec2(scRect) / scRect.size;
			info.Line = Line3D(Vec3(pos, 0.1), Vec3(pos, 0.6));
			info.MovLen = Vec3(0, 0, Random(0.1, maxMovLen));
			lineinfo[i] = info;
		}
	}

	bool RunEvent(double per)
	{
		for (const auto info : lineinfo)
		{
			Line3D line = info.Line;
			line.end += info.MovLen * per;
			line.begin += info.MovLen * per;
			
			line.draw(mat, Palette::White);
		}
		return true;
	}
};

