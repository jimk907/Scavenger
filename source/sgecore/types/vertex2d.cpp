#include "vertex2d.h"
#include "math/vec4.h"
#include "math/vec2.h"


namespace sge
{

	Vertex2d::Vertex2d()
	{
		Reset();
	}

	Vertex2d::Vertex2d(const f32* pos, const f32* texcoord, const f32* color, u32 colors)
	{
		SetPos(pos[0], pos[1]);
		SetUV(texcoord[0], texcoord[1]);
		SetColor(color, colors);
	}

	Vertex2d::Vertex2d(const vec2& pos, const f32* texcoord, const f32* color, u32 colors)
	{
		SetPos(pos.x, pos.y);
		SetUV(texcoord[0], texcoord[1]);
		SetColor(color, colors);
	}

	void Vertex2d::SetPos(const f32 x, const f32 y)
	{
		xy[0] = x;
		xy[1] = y;
	}

	void Vertex2d::SetPos(const vec2& pos)
	{
		xy[0] = pos.x;
		xy[1] = pos.y;
	}

	void Vertex2d::SetUV(const f32 s, const f32 t)
	{
		uv[0] = s;
		uv[1] = t;
	}

	void Vertex2d::SetColor(const f32 r, const f32 g, const f32 b, const f32 a)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
		color[3] = a;
	}
	void Vertex2d::SetColor(const vec4& v)
	{
		color[0] = v.x;
		color[1] = v.y;
		color[2] = v.z;
		color[3] = v.w;
	}
	void Vertex2d::SetColor(const f32* c, u32 colors)
	{
		u32 mx(colors);
		if (mx == 1) {
			SetColor(c[0], c[0], c[0], c[0]);
			return;
		}
		if (mx > 4) mx = 4;
		for (u32 i = 0; i < mx; i++)
			color[i] = c[i];
	}

	//void Vertex2d::SetColor(const float *c, u32 colors)
	//{
	//	u32 mx(colors);
	//	if (mx == 1) {
	//		SetColor(c[0], c[0], c[0], c[0]);
	//		return;
	//	}
	//	if (mx > 4) mx = 4;
	//	for (u32 i = 0; i < mx; i++)
	//		color[i] = c[i];
	//}

	//void Vertex2d::SetColor(const float r, const float b, const float g, const float a)
	//{
	//	color[0] = r;
	//	color[1] = g;
	//	color[2] = b;
	//	color[3] = a;
	//}

	void Vertex2d::Reset()
	{
		SetPos(0.0f, 0.0f);
		SetUV(0.0f, 0.0f);
		SetColor(float(0), float(0), float(0), float(1));
	}

} // nmaespace sge
