#include "sprite2d.h"

namespace sge
{

	Sprite2d::Sprite2d()
		: v00()
		, v01()
		, v10()
		, v11()
		, texture_id(0)
		, depth(0.0f)
	{
	}

	Sprite2d::Sprite2d(const f32* xyRect, const f32* uvRect, u32 texid, f32 dist, const float* color, bool invert, u32 colors)
	{
		f32 x2 = xyRect[0] + xyRect[2];
		f32 y2 = xyRect[1] + xyRect[3];

		f32 y3 = xyRect[1] - xyRect[3];

		texture_id = texid;
		depth = dist;

		if (!invert) {
			v00.SetPos(xyRect[0], xyRect[1]);
			v10.SetPos(x2, xyRect[1]);
			v11.SetPos(x2, y2);
			v01.SetPos(xyRect[0], y2);

			v00.SetUV(uvRect[0], uvRect[1]);
			v10.SetUV(uvRect[0] + uvRect[2], uvRect[1]);
			v11.SetUV(uvRect[0] + uvRect[2], uvRect[1] + uvRect[3]);
			v01.SetUV(uvRect[0], uvRect[1] + uvRect[3]);
		}
		else {
			v00.SetPos(xyRect[0], y3);
			v10.SetPos(x2, y3);
			v11.SetPos(x2, xyRect[1]);
			v01.SetPos(xyRect[0], xyRect[1]);

			v00.SetUV(uvRect[0], uvRect[1] + uvRect[3]);
			v10.SetUV(uvRect[0] + uvRect[2], uvRect[1] + uvRect[3]);
			v11.SetUV(uvRect[0] + uvRect[2], uvRect[1]);
			v01.SetUV(uvRect[0], uvRect[1]);
		}

		if (colors == 1) {
			for (int i = 0; i < 4; i++)
			{
				v00.color[i] = color[i];
				v10.color[i] = color[i];
				v11.color[i] = color[i];
				v01.color[i] = color[i];
			}
			return;
		}

		if (colors == 2) {
			for (int i = 0; i < 4; i++)
			{
				v00.color[i] = color[i];
				v10.color[i] = color[i + 4];
			}
			return;
		}

		if (colors == 3) {
			for (int i = 0; i < 4; i++)
			{
				v00.color[i] = color[i];
				v10.color[i] = color[i + 4];
				v11.color[i] = color[i + 8];
			}
			return;
		}

		if (colors == 4) {
			for (int i = 0; i < 4; i++)
			{
				v00.color[i] = color[i];
				v10.color[i] = color[i + 4];
				v11.color[i] = color[i + 8];
				v01.color[i] = color[i + 12];
			}
			return;
		}

	}

	Sprite2d::Sprite2d(const f32* center, const f32* size, const f32* uvRect, u32 texid, f32 dist, const float* color, bool invert, int colors)
	{
		f32 half_x = size[0] / 2.f;
		f32 half_y = size[1] / 2.f;
		f32 x1 = center[0] - half_x;
		f32 x2 = x1 + size[0];
		f32 y1 = center[1] - half_y;
		f32 y2 = y1 + size[1];
		texture_id = texid;
		depth = dist;


		v00.SetPos(x1, y1);
		v10.SetPos(x2, y1);
		v11.SetPos(x2, y2);
		v01.SetPos(x1, y2);

		if (!invert) {
			v00.SetUV(uvRect[0], uvRect[1]);
			v10.SetUV(uvRect[0] + uvRect[2], uvRect[1]);
			v11.SetUV(uvRect[0] + uvRect[2], uvRect[1] + uvRect[3]);
			v01.SetUV(uvRect[0], uvRect[1] + uvRect[3]);
		}
		else {
			v00.SetUV(uvRect[0], uvRect[1] + uvRect[3]);
			v10.SetUV(uvRect[0] + uvRect[2], uvRect[1] + uvRect[3]);
			v11.SetUV(uvRect[0] + uvRect[2], uvRect[1]);
			v01.SetUV(uvRect[0], uvRect[1]);
		}

		if (colors == 1) {
			for (int i = 0; i < 4; i++)
			{
				v00.color[i] = color[i];
				v10.color[i] = color[i];
				v11.color[i] = color[i];
				v01.color[i] = color[i];
			}
			return;
		}

		if (colors == 2) {
			for (int i = 0; i < 4; i++)
			{
				v00.color[i] = color[i];
				v10.color[i] = color[i + 4];
			}
			return;
		}

		if (colors == 3) {
			for (int i = 0; i < 4; i++)
			{
				v00.color[i] = color[i];
				v10.color[i] = color[i + 4];
				v11.color[i] = color[i + 8];
			}
			return;
		}

		if (colors == 4) {
			for (int i = 0; i < 4; i++)
			{
				v00.color[i] = color[i];
				v10.color[i] = color[i + 4];
				v11.color[i] = color[i + 8];
				v01.color[i] = color[i + 12];
			}
			return;
		}
	}


} // namespace sge
