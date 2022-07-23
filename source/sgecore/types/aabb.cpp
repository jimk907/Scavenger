#include "aabb.h"
#include "math/mat4.h"
#include "math/plane.h"


namespace sge
{

	AABB::AABB()
		: min(FLT_MAX)
		, max(-FLT_MAX)
		, mid(0.0f)
		, radius(0.0f)
	{
	}

	AABB::AABB(const vec3 &mn, const vec3 &mx)
		: min(mn)
		, max(mx)
		, mid(0.0f)
		, radius(0.0f)
	{
	}

	AABB::AABB(const vec3 *pts, unsigned int count)
		: AABB()
	{
		for (unsigned int i = 0; i < count; i++)
			insert(pts[i]);
		set_radius();
	}

	vec3 AABB::center() const
	{
		return (max + min) / 2;
	}

	void AABB::insert(const vec3 &v)
	{
		if (v.x > max.x)	max.x = v.x;
		if (v.x < min.x)	min.x = v.x;
		if (v.y > max.y)	max.y = v.y;
		if (v.y < min.y)	min.y = v.y;
		if (v.z > max.z)	max.z = v.z;
		if (v.z < min.z)	min.z = v.z;
		set_radius();
	}

	void AABB::insert(const vec3 *pt, unsigned int count)
	{
		for (unsigned int i = 0; i < count; i++)
			insert(pt[i]);
		set_radius();
	}

	void AABB::insert(const AABB &bb)
	{
		insert(bb.min);
		insert(bb.max);
		set_radius();
	}

	void AABB::insert(const AABB *bb)
	{
		insert(bb->min);
		insert(bb->max);
		set_radius();
	}

	bool AABB::is_point_inside(const vec3 &pt)
	{
		return (pt.x >= min.x && pt.y >= min.y && pt.z >= min.z &&
				pt.x <= max.x && pt.y <= max.y && pt.z <= max.z);
	}

	bool AABB::is_aabb_inside(const AABB& box)
	{
		if (fabs(mid.x - box.mid.x) > (radius + box.radius)) return false;
		if (fabs(mid.y - box.mid.y) > (radius + box.radius)) return false;
		if (fabs(mid.z - box.mid.z) > (radius + box.radius)) return false;
		return true;
	}

	int AABB::intersects_plane(const Plane &plane) const
	{
		vec3 v1;
		vec3 v2;
		v2.x = (plane.a >= 0.0f) ? min.x : max.x;
		v2.y = (plane.b >= 0.0f) ? min.y : max.y;
		v2.z = (plane.c >= 0.0f) ? min.z : max.z;
		v1.x = (plane.a >= 0.0f) ? max.x : min.x;
		v1.y = (plane.b >= 0.0f) ? max.y : min.y;
		v1.z = (plane.c >= 0.0f) ? max.z : min.z;
		float dist(plane.distance(v2));
		if (dist > 0.0f)
		{
			return Plane::JGE_INFRONT_PLANE;
		}
		dist = plane.distance(v1);
		return dist < 0.0f ? Plane::JGE_BEHIND_PLANE : Plane::JGE_COPLANAR;
	}

	void AABB::transform(mat4 transf)
	{
		min *= transf;
		max *= transf;
	}

	AABB AABB::get_transform(mat4 transf)
	{
		return AABB(min * transf, max * transf);
	}

	AABB2D AABB::get_aabb2d_xy()
	{
		return AABB2D(vec2(min.x, min.y), vec2(max.x, max.y));
	}

	AABB2D AABB::get_aabb2d_xz()
	{
		return AABB2D(vec2(min.x, min.z), vec2(max.x, max.z));
	}

	void AABB::set_radius()
	{
		vec3 diag = max + min;
		mid = diag / 2.0f;
		radius = diag.length() / 2.0f;
	}

} // namespace sge

