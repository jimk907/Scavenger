#pragma once

#define JGE_AABB_H

#include "sge_defines.h"
#include "math/vec3.h"
#include "aabb2d.h"


namespace sge
{

	class mat4;
	class Plane;

	struct AABB
	{
		AABB();
		AABB(const vec3& min, const vec3& max);
		AABB(const vec3* pts, unsigned int count);

		void insert(const vec3& pt);
		void insert(const vec3* pt, unsigned int count = 1);
		void insert(const AABB& bb);
		void insert(const AABB* bb);

		vec3 center() const;

		bool is_point_inside(const vec3& pt);
		bool is_aabb_inside(const AABB& box);

		int intersects_plane(const Plane& plane) const;

		void transform(mat4 transform);

		AABB get_transform(mat4 transform);

		AABB2D get_aabb2d_xy();
		AABB2D get_aabb2d_xz();

		vec3 min;	               // Minimum extent
		vec3 max;                  // Maximum extent
		vec3 mid;
		float radius;

	private:
		void set_radius();

	};


} // namespace sge


