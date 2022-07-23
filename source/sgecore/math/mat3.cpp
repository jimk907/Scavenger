#include "mat3.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "sge_math.h"

namespace sge
{

	mat3::mat3()
	{
		identity();
	}
	mat3::mat3(real *f)
	{
		set(f);
	}

	mat3::mat3(real scale)
	{
		set(scale);
	}

	mat3::mat3(real xx, real xy, real xz,
			   real yx, real yy, real yz,
			   real zx, real zy, real zz)
	{
		set(xx, xy, xz,
			yx, yy, yz,
			zx, zy, zz);
	}

	mat3::mat3(const mat4 &copy)
	{
		data[0] = copy.data[0];
		data[1] = copy.data[1];
		data[2] = copy.data[2];
		data[3] = copy.data[4];
		data[4] = copy.data[5];
		data[5] = copy.data[6];
		data[6] = copy.data[8];
		data[7] = copy.data[9];
		data[8] = copy.data[10];
	}

	mat3::mat3(const mat3 &copy)
	{
		set(copy);
	}

	mat3& mat3::clear()
	{
		for (auto i = 0; i < 9; i++) {
			data[i] = static_cast<real>(0.0);
		}
		return *this;
	}

	mat3& mat3::identity()
	{
		clear();
		data[0] = static_cast<real>(1.0);
		data[4] = static_cast<real>(1.0);
		data[8] = static_cast<real>(1.0);
		return *this;
	}

	mat3& mat3::transpose()
	{
		real s(data[3]); data[3] = data[1]; data[1] = s;
		s = data[6]; data[6] = data[2]; data[2] = s;
		s = data[7]; data[7] = data[5]; data[5] = s;
		return *this;
	}

	mat3& mat3::set(real *f)
	{
		for (auto i = 0; i < 9; i++)
			data[i] = f[i];
		return *this;
	}

	mat3& mat3::set(real scale)
	{
		data[0] = scale; data[3] = static_cast<real>(0.0);  data[6] = static_cast<real>(0.0);
		data[1] = static_cast<real>(0.0);  data[4] = scale; data[7] = static_cast<real>(0.0);
		data[2] = static_cast<real>(0.0);  data[5] = static_cast<real>(0.0);  data[8] = scale;
		return *this;
	}

	mat3& mat3::set(real xx, real xy, real xz,
					real yx, real yy, real yz,
					real zx, real zy, real zz)
	{
		data[0] = xx; data[3] = yx; data[6] = zx;
		data[1] = xy; data[4] = yy; data[7] = zy;
		data[2] = xz; data[5] = yz; data[8] = zz;
		return *this;
	}

	mat3& mat3::set(const mat3 &copy)
	{
		for (auto i = 0; i < 9; i++)
			data[i] = copy[i];
		return *this;
	}

	mat3& mat3::set(const mat4 &copy)
	{
		data[0] = copy.data[0];
		data[1] = copy.data[1];
		data[2] = copy.data[2];
		data[3] = copy.data[4];
		data[4] = copy.data[5];
		data[5] = copy.data[6];
		data[6] = copy.data[8];
		data[7] = copy.data[9];
		data[8] = copy.data[10];
		return *this;
	}

	mat3& mat3::set(const vec3 &xaxis, const vec3 &yaxis, const vec3 &zaxis)
	{
		for (int i = 0; i < 3; i++) {
			data[i] = xaxis[i];
			data[i + 3] = xaxis[i];
			data[i + 6] = xaxis[i];
		}
		return *this;
	}

	mat3& mat3::scale(real s)
	{
		return scale(s, s, s);
	}

	mat3& mat3::scale(real x, real y, real z)
	{
		data[0] *= x; data[3] *= x; data[6] *= x;
		data[1] *= y; data[4] *= y; data[7] *= y;
		data[2] *= z; data[5] *= z; data[8] *= z;
		return *this;
	}

	mat3& mat3::rotate_x(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		real m1 = data[1], m2 = data[2],
			m4 = data[5], m5 = data[6],
			m7 = data[7], m8 = data[8];

		data[1] = m1 * c + m2 * -s;
		data[2] = m1 * s + m2 * c;
		data[4] = m4 * c + m5 * -s;
		data[5] = m4 * s + m5 * c;
		data[7] = m7 * c + m8 * -s;
		data[8] = m7 * s + m8 * c;
		return *this;
	}

	mat3& mat3::rotate_y(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		real m0 = data[0], m2 = data[2],
			m3 = data[3], m5 = data[5],
			m6 = data[6], m8 = data[8];

		data[0] = m0 * c + m2 * s;
		data[2] = m0 * -s + m2 * c;
		data[3] = m3 * c + m5 * s;
		data[5] = m3 * -s + m5 * c;
		data[6] = m6 * c + m8 * s;
		data[8] = m6 * -s + m8 * c;
		return *this;
	}

	mat3& mat3::rotate_z(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		real m0 = data[0], m1 = data[1],
			m3 = data[3], m4 = data[4],
			m6 = data[6], m7 = data[7];

		data[0] = m0 * c + m1 * -s;
		data[1] = m0 * s + m1 * c;
		data[3] = m3 * c + m4 * -s;
		data[4] = m3 * s + m4 * c;
		data[6] = m6 * c + m7 * -s;
		data[7] = m6 * s + m7 * c;
		return *this;
	}

	mat3& mat3::rotate_yxz(real y, real x, real z)
	{
		mat3 xm, ym, zm;
		ym.rotate(y, static_cast<real>(0.0), static_cast<real>(1.0), static_cast<real>(0.0));
		ym.rotate(x, static_cast<real>(1.0), static_cast<real>(0.0), static_cast<real>(0.0));
		ym.rotate(z, static_cast<real>(0.0), static_cast<real>(0.0), static_cast<real>(1.0));
		*this = ym;
		return *this;
	}

	mat3& mat3::spin(real deg, const vec3 axis)
	{
		real degrees = deg * DEGREES;

		real x(axis.x);
		real y(axis.y);
		real z(axis.z);
		real c(COS(degrees));
		real s(SIN(degrees));
		real nc(static_cast<real>(1.0) - c);
		real xs(x * s);
		real ys(y * s);
		real zs(z * s);
		real xy(x * y);
		real xz(x * z);
		real yz(y * z);

		data[0] = (x * x) * nc + c;
		data[1] = xy * nc + zs;
		data[2] = xz * nc - ys;

		data[3] = xy * nc - zs;
		data[4] = (y * y) * nc + c;
		data[5] = yz * nc + xs;

		data[6] = xz * nc + ys;
		data[7] = yz * nc - xs;
		data[8] = (z * z) * nc + c;
		return *this;
	}

	mat3& mat3::rotate(real angle, const vec3& axis)
	{
		return spin(angle, axis); // rotate(angle, axis.x, axis.y, axis.z);
	}

	mat3& mat3::rotate(real angle, real x, real y, real z)
	{
		vec3 v(x, y, z);
		return spin(angle, v);
	}


	mat3& mat3::set_rotate_x(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		data[0] = static_cast<real>(1.0);
		data[1] = static_cast<real>(0.0);
		data[2] = static_cast<real>(0.0);

		data[3] = static_cast<real>(0.0);
		data[4] = c;
		data[5] = s;

		data[6] = static_cast<real>(0.0);
		data[7] = -s;
		data[8] = c;
		return *this;
	}

	mat3& mat3::set_rotate_y(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		data[0] = c;
		data[1] = static_cast<real>(0.0);
		data[2] = -s;

		data[3] = static_cast<real>(0.0);
		data[4] = static_cast<real>(0.0);
		data[5] = static_cast<real>(0.0);

		data[6] = s;
		data[7] = static_cast<real>(0.0);
		data[8] = c;
		return *this;
	}

	mat3& mat3::set_rotate_z(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		data[0] = c;
		data[1] = s;
		data[2] = static_cast<real>(0.0);

		data[3] = -s;
		data[4] = c;
		data[5] = static_cast<real>(0.0);

		data[6] = static_cast<real>(0.0);
		data[7] = static_cast<real>(0.0);
		data[8] = static_cast<real>(0.0);
		return *this;
	}

	vec2 mat3::operator*(const vec2& vec) const
	{
		return vec2(data[0] * vec.x + data[3] * vec.y,
					data[1] * vec.x + data[4] * vec.y);
	}

	vec3 mat3::operator*(const vec3& vec) const
	{
		return vec3(data[0] * vec.x + data[3] * vec.y + data[6] * vec.z,
					data[1] * vec.x + data[4] * vec.y + data[7] * vec.z,
					data[2] * vec.x + data[5] * vec.y + data[8] * vec.z);
	}

	mat3 mat3::operator*(const mat3& rhs) const
	{
		return mat3(data[0] * rhs[0] + data[3] * rhs[1] + data[6] * rhs[2],
					data[1] * rhs[0] + data[4] * rhs[1] + data[7] * rhs[2],
					data[2] * rhs[0] + data[5] * rhs[1] + data[8] * rhs[2],
					data[0] * rhs[3] + data[3] * rhs[4] + data[6] * rhs[5],
					data[1] * rhs[3] + data[4] * rhs[4] + data[7] * rhs[5],
					data[2] * rhs[3] + data[5] * rhs[4] + data[8] * rhs[5],
					data[0] * rhs[6] + data[3] * rhs[7] + data[6] * rhs[8],
					data[1] * rhs[6] + data[4] * rhs[7] + data[7] * rhs[8],
					data[2] * rhs[6] + data[5] * rhs[7] + data[8] * rhs[8]);
	}

	mat3& mat3::operator=(const mat3& rhs)
	{
		for (int i = 0; i < 9; i++) {
			data[i] = rhs.data[i];
		}
		return *this;
	}

	mat3& mat3::operator=(const real* rhs)
	{
		for (int i = 0; i < 9; i++) {
			data[i] = rhs[i];
		}
		return *this;
	}

	mat3& mat3::operator*=(const mat3& rhs)
	{
		real m00 = data[0] * rhs.data[0] + data[3] * rhs.data[1] + data[6] * rhs.data[2];
		real m01 = data[1] * rhs.data[0] + data[4] * rhs.data[1] + data[7] * rhs.data[2];
		real m02 = data[2] * rhs.data[0] + data[5] * rhs.data[1] + data[8] * rhs.data[2];
		real m03 = data[0] * rhs.data[3] + data[3] * rhs.data[4] + data[6] * rhs.data[5];
		real m04 = data[1] * rhs.data[3] + data[4] * rhs.data[4] + data[7] * rhs.data[5];
		real m05 = data[2] * rhs.data[3] + data[5] * rhs.data[4] + data[8] * rhs.data[5];
		real m06 = data[0] * rhs.data[6] + data[3] * rhs.data[7] + data[6] * rhs.data[8];
		real m07 = data[1] * rhs.data[6] + data[4] * rhs.data[7] + data[7] * rhs.data[8];
		real m08 = data[2] * rhs.data[6] + data[5] * rhs.data[7] + data[8] * rhs.data[8];

		data[0] = m00; data[3] = m03; data[6] = m06;
		data[1] = m01; data[4] = m04; data[7] = m07;
		data[2] = m02; data[5] = m05; data[8] = m08;
		return *this;
	}


	mat3& mat3::column(int i, const vec3& vec)
	{
		// CAUTION
		// no range check!
		int n(i * 3);
		data[n] = vec.x;
		data[n + 1] = vec.y;
		data[n + 2] = vec.z;
		return *this;
	}

	mat3& mat3::column_x(const vec3& vec)
	{
		data[0] = vec.x;
		data[1] = vec.y;
		data[2] = vec.z;
		return *this;
	}

	mat3& mat3::column_y(const vec3& vec)
	{
		data[3] = vec.x;
		data[4] = vec.y;
		data[5] = vec.z;
		return *this;
	}

	mat3& mat3::column_z(const vec3& vec)
	{
		data[6] = vec.x;
		data[7] = vec.y;
		data[8] = vec.z;
		return *this;
	}

	vec3 mat3::axis_x() { return vec3(&data[0]); }
	vec3 mat3::axis_y() { return vec3(&data[4]); }
	vec3 mat3::axis_z() { return vec3(&data[8]); }

	real mat3::determinant()
	{
		return data[0] * (data[4] * data[8] - data[5] * data[7]) -
			data[1] * (data[3] * data[8] - data[5] * data[6]) +
			data[2] * (data[3] * data[7] - data[4] * data[6]);
	}

	mat3& mat3::invert()
	{
		real determinant;
		real tmp[9];

		tmp[0] = data[4] * data[8] - data[5] * data[7];
		tmp[1] = data[2] * data[7] - data[1] * data[8];
		tmp[2] = data[1] * data[5] - data[2] * data[4];
		tmp[3] = data[5] * data[6] - data[3] * data[8];
		tmp[4] = data[0] * data[8] - data[2] * data[6];
		tmp[5] = data[2] * data[3] - data[0] * data[5];
		tmp[6] = data[3] * data[7] - data[4] * data[6];
		tmp[7] = data[1] * data[6] - data[0] * data[7];
		tmp[8] = data[0] * data[4] - data[1] * data[3];

		// check determinant if it is 0
		determinant = data[0] * tmp[0] + data[1] * tmp[3] + data[2] * tmp[6];
		if (static_cast<real>(abs(determinant)) <= EPSILON)
		{
			return identity(); // cannot invert, make it identity matrix
		}

		// divide by the determinant
		real invDeterminant(static_cast<real>(1.0) / determinant);
		data[0] = invDeterminant * tmp[0];
		data[1] = invDeterminant * tmp[1];
		data[2] = invDeterminant * tmp[2];
		data[3] = invDeterminant * tmp[3];
		data[4] = invDeterminant * tmp[4];
		data[5] = invDeterminant * tmp[5];
		data[6] = invDeterminant * tmp[6];
		data[7] = invDeterminant * tmp[7];
		data[8] = invDeterminant * tmp[8];
		return *this;
	}

	real const mat3::operator[](unsigned int i) const
	{
		//if (i < 0 || i>8)
		//	return static_cast<real>(0.0);
		assert(i < 9);
		return data[i];
	}

	//real const mat3::operator[](int i) const
	//{
	//	// todo; in debug should log this
	//	//if (i < 0 || i>8)
	//	//	return static_cast<real>(0.0);
	//	assert(i < 9);
	//	return data[i];
	//}

	real &mat3::operator[](unsigned int i)
	{
		// todo: in debug should log this
		if (i < 0 || i > 8) {
			//return static_cast<real>(0.0);
		}
		return *(&data[i]);
	}

	vec3 mat3::column(unsigned int n) const
	{
		if (n < 0 || n > 2)
			return vec3(static_cast<real>(0.0));
		unsigned int e(n * 3);
		return vec3(data[e], data[e + 1], data[e + 2]);
	}

	vec3 mat3::row(unsigned int n) const
	{
		if (n < 0 || n > 2)
			return vec3(static_cast<real>(0.0));
		return vec3(data[n], data[n + 3], data[n + 6]);
	}



} // namespace sge
