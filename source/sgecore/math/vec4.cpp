#include "vec4.h"
#include "vec3.h"
#include "mat4.h"

namespace sge
{


	vec4::vec4()
		: x(0)
		, y(0)
		, z(0)
		, w(0)
	{
	}

	vec4::vec4(real *f)
		: x(f[0])
		, y(f[1])
		, z(f[2])
		, w(f[3])
	{
	}

	vec4::vec4(real f)
		: x(f)
		, y(f)
		, z(f)
		, w(f)
	{
	}

	vec4::vec4(real x, real y, real z, real w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{
	}

	vec4::vec4(vec3 v, real a)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(a)
	{
	}

	vec4::vec4(real *f, real a)
		: x(f[0])
		, y(f[1])
		, z(f[2])
		, w(a)
	{
	}

	vec4::vec4(const vec4 &copy)
		: x(copy.x)
		, y(copy.y)
		, z(copy.z)
		, w(copy.w)
	{
	}


	vec4& vec4::clear()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
		return *this;
	}

	vec4& vec4::set(real *f)
	{
		x = f[0];
		y = f[1];
		z = f[2];
		w = f[3];
		return *this;
	}

	vec4& vec4::set(real f)
	{
		x = f;
		y = f;
		z = f;
		w = f;
		return *this;
	}

	vec4& vec4::set(real x, real y, real z, real w)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
		return *this;
	}


	vec4 vec4::operator-() const
	{
		return vec4(-x, -y, -z, -w);
	}

	vec4 vec4::operator-(const vec4 &rhs) const
	{
		return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.y);
	}

	vec4 vec4::operator+(const vec4 &rhs) const
	{
		return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	vec4 vec4::operator*(const vec4 &rhs) const
	{
		return vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
	}

	vec4 vec4::operator*(const mat4 &rhs) const
	{
		return vec4((x * rhs.data[0]) + (y * rhs.data[4]) + (z * rhs.data[8]) + (w * rhs.data[12]),
					(x * rhs.data[1]) + (y * rhs.data[5]) + (z * rhs.data[9]) + (w * rhs.data[13]),
					(x * rhs.data[2]) + (y * rhs.data[6]) + (z * rhs.data[10]) + (w * rhs.data[14]),
					(x * rhs.data[3]) + (y * rhs.data[7]) + (z * rhs.data[11]) + (w * rhs.data[15]));
	}

	vec4 vec4::operator*(real rhs) const
	{
		return vec4(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	vec4 vec4::operator/(real rhs) const
	{
		if (rhs == 0)
			return vec4(x, y, z, w);
		return vec4(x / rhs, y / rhs, z / rhs, w / rhs);
	}


	vec4 vec4::operator*(real v)
	{
		return vec4(
			data[0] * v,
			data[1] * v,
			data[2] * v,
			data[3] * v);
	}

	real vec4::operator[](unsigned int i) const
	{
		assert(i >= 0 && i < 4);
		return data[i];
	}

	real vec4::operator[](int i) const
	{
		assert(i >= 0 && i < 4);
		return data[i];
	}

	real &vec4::operator[](unsigned int i)
	{
		assert(i >= 0 && i < 4);
		return *(&data[i]);
	}


} // namespace sge
