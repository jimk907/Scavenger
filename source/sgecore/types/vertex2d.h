#pragma once

#include "sge_defines.h"


namespace sge
{
	class vec4;
	class vec2;

	class Vertex2d
	{
#define FLOAT2UBYTE(f) static_cast<ubyte>(f * 255.999)
	public:
		Vertex2d();
		Vertex2d(const f32* pos, const f32* texcoord, const f32* color, u32 colors = 1);
		Vertex2d(const vec2& pos, const f32* texcoord, const f32* color, u32 colors = 1);
		~Vertex2d() {}

		f32   xy[2];
		f32   uv[2];
		float color[4];

		void SetPos(const f32 x, const f32 y);
		void SetPos(const vec2& pos);
		void SetUV(const f32 s, const f32 t);
		void SetColor(const f32 r, const f32 g, const f32 b, const f32 a);
		void SetColor(const vec4& v);
		void SetColor(const f32* color, u32 colors);
		//void SetColor(const float *color, u32 colors);
		//void SetColor(const float r, const float b, const float g, const float a);
		void Reset();
	};

} // namespace sge

