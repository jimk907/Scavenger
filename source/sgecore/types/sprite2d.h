#pragma once

#include "sge_defines.h"
#include "vertex2d.h"




namespace sge
{

	class Sprite2d
	{
	public:
		Sprite2d();
		~Sprite2d() {}
		Sprite2d(const f32* xyRect, const f32* uvRect, u32 texid, f32 depth, const float* color, bool invert = false, u32 colors = 1);
		Sprite2d(const f32* center, const f32* size, const f32* uvRect, u32 texid, f32 depth, const float* color, bool invert = false, int colors = 1);

		Vertex2d v01; // upper left
		Vertex2d v00; // lower left
		Vertex2d v10; // lower right;
		Vertex2d v11; // upper right;

		u32    texture_id;
		f32    depth;

	};



} // namespace sge


