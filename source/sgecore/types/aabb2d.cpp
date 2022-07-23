#include "aabb2d.h"
#include "math/mat4.h"
#include "math/plane.h"

namespace sge
{

	AABB2D::AABB2D()
		: min(FLT_MAX)
		, max(-FLT_MAX)
		, mid(0.0f)
		, radius(0.0f)
	{
	}

	AABB2D::AABB2D(const vec2& mn, const vec2& mx)
		: min(mn)
		, max(mx)
		, mid(0.0f)
		, radius(0.0f)
	{
		vec2 diag = max + min;
		mid = diag / 2.0f;
		radius = diag.length() / 2.0f;
	}

	AABB2D::AABB2D(const vec2* pts, unsigned int count)
		: AABB2D()
	{
		for (unsigned int i = 0; i < count; i++)
			insert(pts[i]);
	}

	vec2 AABB2D::center() const
	{
		return (max + min) / 2;
	}

	void AABB2D::insert(const vec2& v)
	{
		if (v.x > max.x)	max.x = v.x;
		if (v.x < min.x)	min.x = v.x;
		if (v.y > max.y)	max.y = v.y;
		if (v.y < min.y)	min.y = v.y;
		set_radius();
	}

	void AABB2D::insert(const vec2* pt, unsigned int count)
	{
		for (unsigned int i = 0; i < count; i++)
			insert(pt[i]);
		set_radius();
	}

	void AABB2D::insert(const AABB2D& bb)
	{
		insert(bb.min);
		insert(bb.max);
		set_radius();
	}

	void AABB2D::insert(const AABB2D* bb)
	{
		insert(bb->min);
		insert(bb->max);
		set_radius();
	}

	bool AABB2D::is_point_inside(const vec2& pt)
	{
		return (pt.x >= min.x && pt.y >= min.y && 
			pt.x <= max.x && pt.y <= max.y);
	}

	bool AABB2D::is_aabb2d_inside(const AABB2D& box)
	{
		if (fabs(mid.x - box.mid.x) > (radius + box.radius)) return false;
		if (fabs(mid.y - box.mid.y) > (radius + box.radius)) return false;
		return true;
	}

	int AABB2D::intersects_plane(const Plane& plane) const
	{
		vec2 v1;
		vec2 v2;
		v2.x = (plane.a >= 0.0f) ? min.x : max.x;
		v2.y = (plane.b >= 0.0f) ? min.y : max.y;
		v1.x = (plane.a >= 0.0f) ? max.x : min.x;
		v1.y = (plane.b >= 0.0f) ? max.y : min.y;
		float dist(plane.distance(v2));
		if (dist > 0.0f)
		{
			return Plane::JGE_INFRONT_PLANE;
		}
		dist = plane.distance(v1);
		return dist < 0.0f ? Plane::JGE_BEHIND_PLANE : Plane::JGE_COPLANAR;
	}

	//void AABB2D::transform(mat4 transf)
	//{
	//	min *= transf;
	//	max *= transf;
	//}
	//
	//AABB2D AABB2D::get_transform(mat4 transf)
	//{
	//	return AABB2D(min * transf, max * transf);
	//}


	void AABB2D::set_radius()
	{
		vec2 diag = max + min;
		mid = diag / 2.0f;
		radius = diag.length() / 2.0f;
	}

} // namespace sge

