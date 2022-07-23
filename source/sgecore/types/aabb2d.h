#pragma once

#define JGE_AABB_H

#include "sge_defines.h"
#include "math/vec2.h"


namespace sge
{

	class mat4;
	class Plane;

	struct AABB2D
	{
		AABB2D();
		AABB2D(const vec2& min, const vec2& max);
		AABB2D(const vec2* pts, unsigned int count);

		void insert(const vec2& pt);
		void insert(const vec2* pt, unsigned int count = 1);
		void insert(const AABB2D& bb);
		void insert(const AABB2D* bb);

		vec2 center() const;

		bool is_point_inside(const vec2& pt);
		bool is_aabb2d_inside(const AABB2D& box);

		int intersects_plane(const Plane& plane) const;

		//void transform(mat4 transform);

		//AABB2D get_transform(mat4 transform);

		vec2 min;
		vec2 max;
		vec2 mid;
		float radius;

	private:
		void set_radius();

	};


} // namespace sge


