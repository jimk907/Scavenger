#include "vec3.h"
#include "vec2.h"
#include "mat4.h"
#include "sge_math.h"


namespace sge
{

	vec3::~vec3()
	{
	}

	vec3::vec3()
		: x(static_cast<real>(0.0))
		, y(static_cast<real>(0.0))
		, z(static_cast<real>(0.0))
	{
	}

	vec3::vec3(real f)
		: x(f)
		, y(f)
		, z(f)
	{
	}

	vec3::vec3(real x, real y, real z)
		: x(x)
		, y(y)
		, z(z)
	{
	}

	vec3::vec3(real *v)
		: x(v[0])
		, y(v[1])
		, z(v[2])
	{
	}

	vec3::vec3(const vec3 &other)
		: x(other.x)
		, y(other.y)
		, z(other.z)
	{
	}

	vec3::vec3(const vec2&  other)
		: x(other.x)
		, y(other.y)
		, z(static_cast<real>(0.0))
	{
	}

	void vec3::clear()
	{
		x = static_cast<real>(0.0);
		y = static_cast<real>(0.0);
		z = static_cast<real>(0.0);
	}

	void vec3::set(real x, real y, real z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void vec3::set(real *v)
	{
		x = v[0];
		y = v[1];
		z = v[2];
	}

	void vec3::set(const vec3 &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	void vec3::set(const vec2&  other)
	{
		x = other.x;
		y = other.y;
		z = static_cast<real>(0.0);
	}

	real vec3::operator[](unsigned int i) const
	{
		assert(i >= 0 && i < 3);
		return data[i];
	}

	real vec3::operator[](int i) const
	{
		assert(i >= 0 && i < 3);
		return data[i];
	}

	real &vec3::operator[](unsigned int i)
	{
		assert(i >= 0 && i < 3);
		return *(&data[i]);
	}

	vec3 vec3::operator-() const
	{
		return vec3(-x, -y, -z);
	}

	vec3 vec3::operator-(const vec3 &rhs) const
	{
		return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	vec3 vec3::operator+(const vec3 &rhs) const
	{
		return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	vec3 vec3::operator*(const vec3 &rhs) const
	{
		return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	vec3 vec3::operator*(const mat4 &rhs) const
	{
		return vec3((x * rhs.data[0]) + (y * rhs.data[4]) + (z * rhs.data[8]),
			(x * rhs.data[1]) + (y * rhs.data[5]) + (z * rhs.data[9]),
					(x * rhs.data[2]) + (y * rhs.data[6]) + (z * rhs.data[10]));
	}

	vec3 vec3::operator*(real rhs) const
	{
		return vec3(x * rhs, y * rhs, z * rhs);
	}

	//vec3 operator*(const vec3 &lhs, const vec3 &rhs)
	//{
	//	return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	//}

	vec3 operator*(real lhs, const vec3 &rhs)
	{
		return rhs * lhs;
	}

	vec3 vec3::operator/(real rhs) const
	{
		if (rhs == 0)
			return vec3(x, y, z);
		return vec3(x / rhs, y / rhs, z / rhs);
	}

	vec3& vec3::operator-()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	vec3& vec3::operator=(const vec3 &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	vec3& vec3::operator+=(const vec3 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	vec3& vec3::operator-=(const vec3 &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	vec3& vec3::operator*=(const vec3 &rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	vec3& vec3::operator*=(const mat4 &rhs)
	{
		real xn = (x * rhs.data[0]) + (y * rhs.data[4]) + (z * rhs.data[8]);
		real yn = (x * rhs.data[1]) + (y * rhs.data[5]) + (z * rhs.data[9]);
		real zn = (x * rhs.data[2]) + (y * rhs.data[6]) + (z * rhs.data[10]);
		x = xn; y = yn; z = zn;
		return *this;
	}

	vec3& vec3::operator+=(real  rhs)
	{
		x += rhs;
		y += rhs;
		z *= rhs;
		return *this;
	}

	bool vec3::operator==(const vec3 &rhs) const
	{
		real d(x - rhs.x);
		real e(x - rhs.x);
		real f(x - rhs.x);

		return (d > -EPSILON && d < EPSILON &&
				e > -EPSILON && e < EPSILON &&
				f > -EPSILON && f < EPSILON);
	}

	bool vec3::operator!=(const vec3 &rhs) const
	{
		return !(*this == rhs);
	}

	real vec3::length() const
	{
		return static_cast<real>(SQRT(x*x + y * y + z * z));
	}

	real vec3::dot(const vec3 &rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	real vec3::distance(const vec3 &rhs) const
	{
		real dx(x - rhs.x);
		real dy(y - rhs.y);
		real dz(z - rhs.z);

		return static_cast<real>(SQRT(dx * dx + dy * dy + dz * dz));
	}

	vec3  vec3::crossed(const vec3 &rhs) const
	{
		return vec3(
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x
		);
	}

	vec3& vec3::cross(const vec3 &rhs)
	{
		real xn = y * rhs.z - z * rhs.y;
		real yn = z * rhs.x - x * rhs.z;
		real zn = x * rhs.y - y * rhs.x;
		x = xn; y = yn; z = zn;
		return *this;
	}

	vec3  vec3::normalized() const
	{
		real f = length();
		if (f == static_cast<real>(0.0))
			f = static_cast<real>(1.0);
		else
			f = static_cast<real>(1.0) / f;
		return vec3(x * f, y * f, z * f);
	}

	vec3& vec3::normalize()
	{
		real f = length();
		if (f == static_cast<real>(0.0))
			f = static_cast<real>(1.0);
		else
			f = static_cast<real>(1.0) / f;
		x *= f; y *= f; z *= f;
		return *this;
	}

	//vec3& vec3::minimize(const vec3 &a)
	//{
	//	sge::Min(x, a.x);
	//	sge::Min(y, a.y);
	//	sge::Min(z, a.z);
	//	return *this;
	//}
	//
	//vec3& vec3::maximize(const vec3 &a)
	//{
	//	sge::Max(x, a.x);
	//	sge::Max(y, a.y);
	//	sge::Max(z, a.z);
	//	return *this;
	//}
	//
	//vec3& vec3::clamp(const vec3 &a, const vec3 &b)
	//{
	//	sge::Clamp(x, a.x, b.x);
	//	sge::Clamp(y, a.y, b.y);
	//	sge::Clamp(z, a.z, b.z);
	//	return *this;
	//}

	vec3 vec3::lerp(const vec3& start, const vec3& end, real percent)
	{
		return vec3(end - start) * percent + start;
	}

	//vec3 vec3::slerp(const vec3& start, const vec3& end, real percent)
	//{
	//	real dot = sge::Clamp(start.dot(end), static_cast<real>(-1.0), static_cast<real>(1.0));
	//	real theta = static_cast<real>(acos(dot)) * percent;
	//	vec3 ortho(end - start * dot);
	//	ortho.normalize();
	//	return ((start * static_cast<real>(cos(theta))) + (ortho * static_cast<real>(sin(theta))));
	//}

	vec3 vec3::nlerp(const vec3& start, const vec3& end, real percent)
	{
		return (lerp(start, end, percent)).normalize();
	}

	//vec3 vec3::clamp(const vec3& vec, real min, real max)
	//{
	//	return vec3(sge::Clamp(vec.x, min, max),
	//				sge::Clamp(vec.y, min, max),
	//				sge::Clamp(vec.z, min, max));
	//}


	vec3 vec3::cross(const vec3 &a, const vec3 &b)
	{
		return vec3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	real vec3::dot(const vec3 &a, const vec3 &b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

} // namespace sge
