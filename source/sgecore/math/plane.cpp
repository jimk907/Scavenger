#include "plane.h"
#include "sge_math.h"


namespace sge
{


Plane::Plane()
	: a(static_cast<real>(0.0))
	, b(static_cast<real>(0.0))
	, c(static_cast<real>(0.0))
	, d(static_cast<real>(0.0))
{
}

Plane::Plane(const real a, const real b, const real c, const real d)
	: a(a)
	, b(b)
	, c(c)
	, d(d)
{
}

Plane::Plane(const Plane &other)
	: a(other.a)
	, b(other.b)
	, c(other.c)
	, d(other.d)
{
}



//  Constructor from 3 points on the plane
//	This assumes a right-hand winding order
//  (compatible with Opengl convention)
//    For RHS:         For LHS:
//         p2           p1--p2
//         |             |
//     p0--p1           p0
//   Front Facing      Rear Facing
//  Normal come out   Normal goes in
//   toward viewer   away from viewer
//
Plane::Plane(const vec3 &p1, const vec3 &p2, const vec3 &p3)
	: a(static_cast<real>(0.0))
	, b(static_cast<real>(0.0))
	, c(static_cast<real>(0.0))
	, d(static_cast<real>(0.0))
{
	set(p1, p2, p3);
}

Plane::Plane(const vec3 &normal, real dist)
	: a(normal.x)
	, b(normal.y)
	, c(normal.z)
	, d(dist)
{
}

void Plane::set(const real fa, const real fb, const real fc, const real fd)
{
	a = fa;
	b = fb;
	c = fc;
	d = fd;
}

void Plane::set(const Plane &other)
{
	a = other.a;
	b = other.b;
	c = other.c;
	d = other.d;
}

void Plane::set(const vec3 &p0, const vec3 &p1, const vec3 &p2)
{
	vec3 v = p1 - p0;
	vec3 u = p2 - p0;
	vec3 n = vec3::cross(v, u); // normal
	n.normalize();
	a = n.x;
	b = n.y;
	c = n.z;
	d = -n.dot(p0);
}

void Plane::set(const vec3 &normal, real dist)
{
	a = normal.x;
	b = normal.y;
	c = normal.z;
	d = dist;
}

void Plane::reset()
{
	a = b = c = d = static_cast<real>(0.0);
}

void Plane::normalize()
{
	real len = a * a + b * b + c * c;
	if (len < EPSILON)
		reset();
	else {
		len = static_cast<real>(1.0) / static_cast<real>(SQRT(len));
		a *= len;
		b *= len;
		c *= len;
		d *= len;
	}
}


real Plane::distance(const vec3 &pt) const
{
	return a * pt.x + b * pt.y + c * pt.z + d;
}

bool Plane::is_behind(const vec3 &pt) const
{
	return (distance(pt) < 0);
}


} // namespace sge

