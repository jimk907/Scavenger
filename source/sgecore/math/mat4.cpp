#include "mat4.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "sge_math.h"


namespace sge
{

	mat4::mat4()
	{
		identity();
	}
	mat4::mat4(real *f)
	{
		set(f);
	}

	mat4::mat4(real scale)
	{
		set(scale);
	}

	mat4::mat4(real xx, real xy, real xz, real xw,
			   real yx, real yy, real yz, real yw,
			   real zx, real zy, real zz, real zw,
			   real wx, real wy, real wz, real ww)
	{
		set(xx, xy, xz, xw,
			yx, yy, yz, yw,
			zx, zy, zz, zw,
			wx, wy, wz, ww);
	}

	mat4::mat4(const mat4 &copy)
	{
		set(copy);
	}

	mat4& mat4::clear()
	{
		for (auto i = 0; i < 16; i++) {
			data[i] = static_cast<real>(0.0);
		}
		return *this;
	}

	mat4& mat4::identity()
	{
		clear();
		data[0] = static_cast<real>(1.0);
		data[5] = static_cast<real>(1.0);
		data[10] = static_cast<real>(1.0);
		data[15] = static_cast<real>(1.0);
		return *this;
	}

	mat4& mat4::transpose()
	{
		real s(data[4]); data[4] = data[1]; data[1] = s;

		s = data[8];  data[8] = data[2];  data[2] = s;
		s = data[12]; data[12] = data[3];  data[3] = s;
		s = data[9];  data[9] = data[6];  data[6] = s;
		s = data[13]; data[13] = data[7];  data[7] = s;
		s = data[14]; data[14] = data[11]; data[11] = s;
		return *this;
	}

	mat4& mat4::set(real *f)
	{
		for (auto i = 0; i < 16; i++)
			data[i] = f[i];
		return *this;
	}

	mat4& mat4::set(real scale)
	{
		data[0] = scale; data[4] = static_cast<real>(0.0);  data[8] = static_cast<real>(0.0);   data[12] = static_cast<real>(0.0);
		data[1] = static_cast<real>(0.0);  data[5] = scale; data[9] = static_cast<real>(0.0);   data[13] = static_cast<real>(0.0);
		data[2] = static_cast<real>(0.0);  data[6] = static_cast<real>(0.0);  data[10] = scale; data[14] = static_cast<real>(0.0);
		data[3] = static_cast<real>(0.0);  data[7] = static_cast<real>(0.0);  data[11] = static_cast<real>(0.0);  data[15] = static_cast<real>(1.0);
		return *this;
	}

	mat4& mat4::set(real xx, real xy, real xz, real xw,
					real yx, real yy, real yz, real yw,
					real zx, real zy, real zz, real zw,
					real wx, real wy, real wz, real ww)
	{
		data[0] = xx; data[4] = yx; data[8] = zx; data[12] = wx;
		data[1] = xy; data[5] = yy; data[9] = zy; data[13] = wy;
		data[2] = xz; data[6] = yz; data[10] = zz; data[14] = wz;
		data[3] = xw; data[7] = yw; data[11] = zw; data[15] = ww;
		return *this;
	}

	mat4& mat4::set(const mat4 &copy)
	{
		for (auto i = 0; i < 16; i++)
			data[i] = copy[i];
		return *this;
	}

	mat4& mat4::set(const vec3 &xaxis, const vec3 &yaxis, const vec3 &zaxis)
	{
		for (int i = 0; i < 3; i++) {
			data[i] = xaxis[i];
			data[i + 4] = xaxis[i];
			data[i + 8] = xaxis[i];
		}
		return *this;
	}

	mat4& mat4::orthographic(real left, real right, real bottom, real top, real znear, real zfar)
	{
		real x = right - left;	// width
		real y = top - bottom;	// height
		real z = zfar - znear;	// depth

		data[0] = 2 / x; data[4] = 0;     data[8] = 0;     data[12] = -(right + left) / x;
		data[1] = 0;     data[5] = 2 / y; data[9] = 0;     data[13] = -(top + bottom) / y;
		data[2] = 0;     data[6] = 0;     data[10] = -2 / z; data[14] = -(zfar + znear) / z;
		data[3] = 0;     data[7] = 0;     data[11] = 0;      data[15] = 1;
		return *this;
	}

	mat4& mat4::perspective(real fovy, real aspect, real znear, real zfar)
	{
		real scale = znear * static_cast<real>(tan(0.5 * fovy * DEGREES)); // calc the 1/2 height of the frustum near plane
		real left = -scale * aspect;
		real right = scale * aspect;
		real top = scale;
		real bottom = -scale;
		return setFrustum(left, right, bottom, top, znear, zfar);
	}

	mat4& mat4::setFrustum(real left, real right, real bottom, real top, real znear, real zfar)
	{
		real x = right - left;	 // width
		real y = top - bottom; // height
		real z = zfar - znear;	 // depth
		real n2 = znear * static_cast<real>(2.0);	     // precalc a value

		data[0] = n2 / x; data[4] = 0;      data[8] = (right + left) / x;  data[12] = 0;
		data[1] = 0;      data[5] = n2 / y; data[9] = (top + bottom) / y;  data[13] = 0;
		data[2] = 0;      data[6] = 0;      data[10] = -(zfar + znear) / z; data[14] = static_cast<real>(-2) * (zfar * znear) / z;
		data[3] = 0;      data[7] = 0;      data[11] = -1;                  data[15] = 0;
		return *this;
	}

	mat4& mat4::translate(real x, real y, real z)
	{
		data[0] += data[3] * x; data[4] += data[7] * x; data[8] += data[11] * x; data[12] += data[15] * x;
		data[1] += data[3] * y; data[5] += data[7] * y; data[9] += data[11] * y; data[13] += data[15] * y;
		data[2] += data[3] * z; data[6] += data[7] * z; data[10] += data[11] * z; data[14] += data[15] * z;
		return *this;
	}

	mat4& mat4::translate(const vec3& vec)
	{
		return translate(vec.x, vec.y, vec.z);
	}

	mat4& mat4::scale(real s)
	{
		return scale(s, s, s);
	}

	mat4& mat4::scale(real x, real y, real z)
	{
		data[0] *= x; data[4] *= x; data[8] *= x; data[12] *= x;
		data[1] *= y; data[5] *= y; data[9] *= y; data[13] *= y;
		data[2] *= z; data[6] *= z; data[10] *= z; data[14] *= z;
		return *this;
	}

	mat4& mat4::rotate_x(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		real m1 = data[1], m2 = data[2],
			m5  = data[5], m6 = data[6],
			m9  = data[9], m10 = data[10],
			m13 = data[13], m14 = data[14];

		data[1] = m1 * c + m2 * -s;
		data[2] = m1 * s + m2 * c;
		data[5] = m5 * c + m6 * -s;
		data[6] = m5 * s + m6 * c;
		data[9] = m9 * c + m10 * -s;
		data[10] = m9 * s + m10 * c;
		data[13] = m13 * c + m14 * -s;
		data[14] = m13 * s + m14 * c;
		return *this;
	}

	mat4& mat4::rotate_y(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		real m0 = data[0], m2 = data[2],
			m4 = data[4], m6 = data[6],
			m8 = data[8], m10 = data[10],
			m12 = data[12], m14 = data[14];

		data[0] = m0 * c + m2 * s;
		data[2] = m0 * -s + m2 * c;
		data[4] = m4 * c + m6 * s;
		data[6] = m4 * -s + m6 * c;
		data[8] = m8 * c + m10 * s;
		data[10] = m8 * -s + m10 * c;
		data[12] = m12 * c + m14 * s;
		data[14] = m12 * -s + m14 * c;
		return *this;
	}

	mat4& mat4::rotate_z(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		real m0 = data[0], m1 = data[1],
			m4 = data[4], m5 = data[5],
			m8 = data[8], m9 = data[9],
			m12 = data[12], m13 = data[13];

		data[0] = m0 * c + m1 * -s;
		data[1] = m0 * s + m1 * c;
		data[4] = m4 * c + m5 * -s;
		data[5] = m4 * s + m5 * c;
		data[8] = m8 * c + m9 * -s;
		data[9] = m8 * s + m9 * c;
		data[12] = m12 * c + m13 * -s;
		data[13] = m12 * s + m13 * c;
		return *this;
	}

	mat4& mat4::rotate_yxz(real y, real x, real z)
	{
		mat4 xm, ym, zm;
		ym.rotate(y, static_cast<real>(0.0), static_cast<real>(1.0), static_cast<real>(0.0));
		ym.rotate(x, static_cast<real>(1.0), static_cast<real>(0.0), static_cast<real>(0.0));
		ym.rotate(z, static_cast<real>(0.0), static_cast<real>(0.0), static_cast<real>(1.0));
		*this = ym;
		return *this;
	}

	mat4& mat4::spin(real deg, const vec3 axis)
	{
		real degrees = deg * DEGREES;

		real x = axis.x;
		real y = axis.y;
		real z = axis.z;
		real c = static_cast<real>(cos(degrees));
		real s = static_cast<real>(sin(degrees));

		data[0] = (x * x) * (static_cast<real>(1.0) - c) + c;
		data[1] = (x * y) * (static_cast<real>(1.0) - c) + (z * s);
		data[2] = (x * z) * (static_cast<real>(1.0) - c) - (y * s);
		data[3] = static_cast<real>(0.0);

		data[4] = (y * x) * (static_cast<real>(1.0) - c) - (z * s);
		data[5] = (y * y) * (static_cast<real>(1.0) - c) + c;
		data[6] = (y * z) * (static_cast<real>(1.0) - c) + (x * s);
		data[7] = static_cast<real>(0.0);

		data[8] = (z * x) * (static_cast<real>(1.0) - c) + (y * s);
		data[9] = (z * y) * (static_cast<real>(1.0) - c) - (x * s);
		data[10] = (z * z) * (static_cast<real>(1.0) - c) + c;
		data[11] = static_cast<real>(0.0);

		data[12] = static_cast<real>(0.0);
		data[13] = static_cast<real>(0.0);
		data[14] = static_cast<real>(0.0);
		data[15] = static_cast<real>(1.0);
		//return transpose(); 
		return *this;
	}

	mat4& mat4::rotate(real angle, const vec3& axis)
	{
		return rotate(angle, axis.x, axis.y, axis.z);
	}

	mat4& mat4::rotate(real angle, real x, real y, real z)
	{
		real c = static_cast<real>(cos(angle * DEGREES));
		real s = static_cast<real>(sin(angle * DEGREES));
		real c1 = static_cast<real>(1.0) - c;
		real m0 = data[0], m4 = data[4], m8 = data[8], m12 = data[12],
			m1 = data[1], m5 = data[5], m9 = data[9], m13 = data[13],
			m2 = data[2], m6 = data[6], m10 = data[10], m14 = data[14];
		real xy = x * y;
		real yz = y * z;
		real ys = y * s;
		real zs = z * s;
		real xs = x * s;

		//build rotation matrix
		real r0 = x * x  * c1 + c;
		real r1 = xy * c1 + zs;
		real r2 = x * z  * c1 - ys;
		real r4 = xy * c1 - zs;
		real r5 = y * y  * c1 + c;
		real r6 = yz * c1 + xs;
		real r8 = x * z  * c1 + ys;
		real r9 = yz * c1 - xs;
		real r10 = z * z  * c1 + c;

		// multiply rotation matrix
		data[0] = r0 * m0 + r4 * m1 + r8 * m2;
		data[1] = r1 * m0 + r5 * m1 + r9 * m2;
		data[2] = r2 * m0 + r6 * m1 + r10 * m2;
		data[4] = r0 * m4 + r4 * m5 + r8 * m6;
		data[5] = r1 * m4 + r5 * m5 + r9 * m6;
		data[6] = r2 * m4 + r6 * m5 + r10 * m6;
		data[8] = r0 * m8 + r4 * m9 + r8 * m10;
		data[9] = r1 * m8 + r5 * m9 + r9 * m10;
		data[10] = r2 * m8 + r6 * m9 + r10 * m10;
		data[12] = r0 * m12 + r4 * m13 + r8 * m14;
		data[13] = r1 * m12 + r5 * m13 + r9 * m14;
		data[14] = r2 * m12 + r6 * m13 + r10 * m14;
		return *this;
	}


	mat4& mat4::set_rotate_x(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		data[0] = static_cast<real>(1.0);
		data[1] = static_cast<real>(0.0);
		data[2] = static_cast<real>(0.0);
		data[3] = static_cast<real>(0.0);
		data[4] = static_cast<real>(0.0);
		data[5] = c;
		data[6] = s;
		data[7] = static_cast<real>(0.0);
		data[8] = static_cast<real>(0.0);
		data[9] = -s;
		data[10] = c;
		data[11] = static_cast<real>(0.0);
		return *this;
	}

	mat4& mat4::set_rotate_y(real angle)
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
		data[6] = static_cast<real>(0.0);
		data[7] = static_cast<real>(0.0);
		data[8] = s;
		data[9] = static_cast<real>(0.0);
		data[10] = c;
		data[11] = static_cast<real>(0.0);
		return *this;
	}

	mat4& mat4::set_rotate_z(real angle)
	{
		real radians = angle * DEGREES;
		real c = static_cast<real>(cos(radians));
		real s = static_cast<real>(sin(radians));

		data[0] = c;
		data[1] = s;
		data[2] = static_cast<real>(0.0);
		data[3] = static_cast<real>(0.0);
		data[4] = -s;
		data[5] = c;
		data[6] = static_cast<real>(0.0);
		data[7] = static_cast<real>(0.0);
		data[8] = static_cast<real>(0.0);
		data[9] = static_cast<real>(0.0);
		data[10] = static_cast<real>(0.0);
		data[11] = static_cast<real>(0.0);
		return *this;
	}

	mat4& mat4::lookat(const vec3& eye, const vec3& target, const vec3& up)
	{
		vec3 world_up(real(0.0), real(1.0), real(0.0));
		if (up.x || up.y || up.z)
			world_up = up;

		vec3 f((target - eye).normalized());
		vec3 r(f.crossed(world_up));
		vec3 u(r.crossed(f));

		f32 x(-r.dot(eye));
		f32 y(-u.dot(eye));
		f32 z(f.dot(eye));

		data[0] = r.x;
		data[4] = r.y;
		data[8] = r.z;
		data[1] = u.x;
		data[5] = u.y;
		data[9] = u.z;
		data[2] = -f.x;
		data[6] = -f.y;
		data[10] = -f.z;
		data[12] = x;
		data[13] = y;
		data[14] = z;
		data[3] = 0.0f;
		data[7] = 0.0f;
		data[11] = 0.0f;
		data[15] = 1.0f;

		return *this;
	}

	vec2 mat4::operator*(const vec2& vec) const
	{
		return vec2(data[0] * vec.x + data[4] * vec.y,
					data[1] * vec.x + data[5] * vec.y);
	}

	vec3 mat4::operator*(const vec3& vec) const
	{
		return vec3(data[0] * vec.x + data[4] * vec.y + data[8] * vec.z,
					data[1] * vec.x + data[5] * vec.y + data[9] * vec.z,
					data[2] * vec.x + data[6] * vec.y + data[10] * vec.z);
	}

	vec4 mat4::operator*(const vec4& vec) const
	{
		return vec4(data[0] * vec.x + data[4] * vec.y + data[8] * vec.z + data[12] * vec.w,
					data[1] * vec.x + data[5] * vec.y + data[9] * vec.z + data[13] * vec.w,
					data[2] * vec.x + data[6] * vec.y + data[10] * vec.z + data[14] * vec.w,
					data[3] * vec.x + data[7] * vec.y + data[11] * vec.z + data[15] * vec.w);
	}

	mat4 mat4::operator*(const mat4& mat) const
	{
		return mat4(
			data[0] * mat.data[0] + data[4] * mat.data[1] + data[8] * mat.data[2] + data[12] * mat.data[3],
			data[1] * mat.data[0] + data[5] * mat.data[1] + data[9] * mat.data[2] + data[13] * mat.data[3],
			data[2] * mat.data[0] + data[6] * mat.data[1] + data[10] * mat.data[2] + data[14] * mat.data[3],
			data[3] * mat.data[0] + data[7] * mat.data[1] + data[11] * mat.data[2] + data[15] * mat.data[3],
			data[0] * mat.data[4] + data[4] * mat.data[5] + data[8] * mat.data[6] + data[12] * mat.data[7],
			data[1] * mat.data[4] + data[5] * mat.data[5] + data[9] * mat.data[6] + data[13] * mat.data[7],
			data[2] * mat.data[4] + data[6] * mat.data[5] + data[10] * mat.data[6] + data[14] * mat.data[7],
			data[3] * mat.data[4] + data[7] * mat.data[5] + data[11] * mat.data[6] + data[15] * mat.data[7],
			data[0] * mat.data[8] + data[4] * mat.data[9] + data[8] * mat.data[10] + data[12] * mat.data[11],
			data[1] * mat.data[8] + data[5] * mat.data[9] + data[9] * mat.data[10] + data[13] * mat.data[11],
			data[2] * mat.data[8] + data[6] * mat.data[9] + data[10] * mat.data[10] + data[14] * mat.data[11],
			data[3] * mat.data[8] + data[7] * mat.data[9] + data[11] * mat.data[10] + data[15] * mat.data[11],
			data[0] * mat.data[12] + data[4] * mat.data[13] + data[8] * mat.data[14] + data[12] * mat.data[15],
			data[1] * mat.data[12] + data[5] * mat.data[13] + data[9] * mat.data[14] + data[13] * mat.data[15],
			data[2] * mat.data[12] + data[6] * mat.data[13] + data[10] * mat.data[14] + data[14] * mat.data[15],
			data[3] * mat.data[12] + data[7] * mat.data[13] + data[11] * mat.data[14] + data[15] * mat.data[15]);
	}

	mat4& mat4::operator=(const mat4& rhs)
	{
		for (int i = 0; i < 16; i++) {
			data[i] = rhs.data[i];
		}
		return *this;
	}

	mat4& mat4::operator=(const real* rhs)
	{
		for (int i = 0; i < 16; i++) {
			data[i] = rhs[i];
		}
		return *this;
	}

	mat4& mat4::operator*=(const mat4& rhs)
	{
		real m00 = data[0] * rhs.data[0] + data[4] * rhs.data[1] + data[8] * rhs.data[2] + data[12] * rhs.data[3];
		real m01 = data[1] * rhs.data[0] + data[5] * rhs.data[1] + data[9] * rhs.data[2] + data[13] * rhs.data[3];
		real m02 = data[2] * rhs.data[0] + data[6] * rhs.data[1] + data[10] * rhs.data[2] + data[14] * rhs.data[3];
		real m03 = data[3] * rhs.data[0] + data[7] * rhs.data[1] + data[11] * rhs.data[2] + data[15] * rhs.data[3];
		real m04 = data[0] * rhs.data[4] + data[4] * rhs.data[5] + data[8] * rhs.data[6] + data[12] * rhs.data[7];
		real m05 = data[1] * rhs.data[4] + data[5] * rhs.data[5] + data[9] * rhs.data[6] + data[13] * rhs.data[7];
		real m06 = data[2] * rhs.data[4] + data[6] * rhs.data[5] + data[10] * rhs.data[6] + data[14] * rhs.data[7];
		real m07 = data[3] * rhs.data[4] + data[7] * rhs.data[5] + data[11] * rhs.data[6] + data[15] * rhs.data[7];
		real m08 = data[0] * rhs.data[8] + data[4] * rhs.data[9] + data[8] * rhs.data[10] + data[12] * rhs.data[11];
		real m09 = data[1] * rhs.data[8] + data[5] * rhs.data[9] + data[9] * rhs.data[10] + data[13] * rhs.data[11];
		real m10 = data[2] * rhs.data[8] + data[6] * rhs.data[9] + data[10] * rhs.data[10] + data[14] * rhs.data[11];
		real m11 = data[3] * rhs.data[8] + data[7] * rhs.data[9] + data[11] * rhs.data[10] + data[15] * rhs.data[11];
		real m12 = data[0] * rhs.data[12] + data[4] * rhs.data[13] + data[8] * rhs.data[14] + data[12] * rhs.data[15];
		real m13 = data[1] * rhs.data[12] + data[5] * rhs.data[13] + data[9] * rhs.data[14] + data[13] * rhs.data[15];
		real m14 = data[2] * rhs.data[12] + data[6] * rhs.data[13] + data[10] * rhs.data[14] + data[14] * rhs.data[15];
		real m15 = data[3] * rhs.data[12] + data[7] * rhs.data[13] + data[11] * rhs.data[14] + data[15] * rhs.data[15];

		data[0] = m00; data[4] = m04; data[8] = m08; data[12] = m12;
		data[1] = m01; data[5] = m05; data[9] = m09; data[13] = m13;
		data[2] = m02; data[6] = m06; data[10] = m10; data[14] = m14;
		data[3] = m03; data[7] = m07; data[11] = m11; data[15] = m15;
		return *this;
	}


	mat4& mat4::column(int i, const vec3& vec)
	{
		// CAUTION
		// no range check!
		int n(i * 4);
		data[n] = vec.x;
		data[n + 1] = vec.y;
		data[n + 2] = vec.z;
		return *this;
	}

	mat4& mat4::column_x(const vec3& vec)
	{
		data[0] = vec.x;
		data[1] = vec.y;
		data[2] = vec.z;
		return *this;
	}

	mat4& mat4::column_y(const vec3& vec)
	{
		data[4] = vec.x;
		data[5] = vec.y;
		data[6] = vec.z;
		return *this;
	}

	mat4& mat4::column_z(const vec3& vec)
	{
		data[8] = vec.x;
		data[9] = vec.y;
		data[10] = vec.z;
		return *this;
	}

	mat4& mat4::set_translation(const vec3& vec)
	{
		data[12] = vec.x;
		data[13] = vec.y;
		data[14] = vec.z;
		return *this;
	}

	mat4& mat4::set_translation(real *f)
	{
		data[12] = f[0];
		data[13] = f[1];
		data[14] = f[2];
		return *this;
	}

	mat4& mat4::set_translation(real f)
	{
		data[12] = f;
		data[13] = f;
		data[14] = f;
		return *this;
	}

	vec3 mat4::axis_x() { return vec3(&data[0]); }
	vec3 mat4::axis_y() { return vec3(&data[4]); }
	vec3 mat4::axis_z() { return vec3(&data[8]); }
	vec3 mat4::translation() { return vec3(&data[12]); }

	real mat4::determinant()
	{
		return (data[0] * data[5] - data[1] * data[4])*(data[10] * data[15] - data[11] * data[14]) - (data[0] * data[6] - data[2] * data[4])*(data[9] * data[15] - data[11] * data[13]) +
			(data[0] * data[7] - data[3] * data[4])*(data[9] * data[14] - data[10] * data[13]) + (data[1] * data[6] - data[2] * data[5])*(data[8] * data[15] - data[11] * data[12]) -
			(data[1] * data[7] - data[3] * data[5])*(data[8] * data[14] - data[10] * data[12]) + (data[2] * data[7] - data[3] * data[6])*(data[8] * data[13] - data[9] * data[12]);
	}

	mat4& mat4::invert()
	{
		real det = determinant();
		if (det) {
			// Calculate the inverse of the matrix using Cramers rule
			det = static_cast<real>(1.0) / det;
			set(det*(data[5] * (data[10] * data[15] - data[11] * data[14]) + data[6] * (data[11] * data[13] - data[9] * data[15]) + data[7] * (data[9] * data[14] - data[10] * data[13])), // 0   0
				det*(data[9] * (data[2] * data[15] - data[3] * data[14]) + data[10] * (data[3] * data[13] - data[1] * data[15]) + data[11] * (data[1] * data[14] - data[2] * data[13])),   // 1   4
				det*(data[13] * (data[2] * data[7] - data[3] * data[6]) + data[14] * (data[3] * data[5] - data[1] * data[7]) + data[15] * (data[1] * data[6] - data[2] * data[5])),        // 2   8
				det*(data[1] * (data[7] * data[10] - data[6] * data[11]) + data[2] * (data[5] * data[11] - data[7] * data[9]) + data[3] * (data[6] * data[9] - data[5] * data[10])),       // 3   12
				det*(data[6] * (data[8] * data[15] - data[11] * data[12]) + data[7] * (data[10] * data[12] - data[8] * data[14]) + data[4] * (data[11] * data[14] - data[10] * data[15])), // 4   1
				det*(data[10] * (data[0] * data[15] - data[3] * data[12]) + data[11] * (data[2] * data[12] - data[0] * data[14]) + data[8] * (data[3] * data[14] - data[2] * data[15])),   // 5   5
				det*(data[14] * (data[0] * data[7] - data[3] * data[4]) + data[15] * (data[2] * data[4] - data[0] * data[6]) + data[12] * (data[3] * data[6] - data[2] * data[7])),        // 6   9
				det*(data[2] * (data[7] * data[8] - data[4] * data[11]) + data[3] * (data[4] * data[10] - data[6] * data[8]) + data[0] * (data[6] * data[11] - data[7] * data[10])),       // 7   13
				det*(data[7] * (data[8] * data[13] - data[9] * data[12]) + data[4] * (data[9] * data[15] - data[11] * data[13]) + data[5] * (data[11] * data[12] - data[8] * data[15])),   // 8   2
				det*(data[11] * (data[0] * data[13] - data[1] * data[12]) + data[8] * (data[1] * data[15] - data[3] * data[13]) + data[9] * (data[3] * data[12] - data[0] * data[15])),    // 9   6
				det*(data[15] * (data[0] * data[5] - data[1] * data[4]) + data[12] * (data[1] * data[7] - data[3] * data[5]) + data[13] * (data[3] * data[4] - data[0] * data[7])),        // 10  10
				det*(data[3] * (data[5] * data[8] - data[4] * data[9]) + data[0] * (data[7] * data[9] - data[5] * data[11]) + data[1] * (data[4] * data[11] - data[7] * data[8])),         // 11  14
				det*(data[4] * (data[10] * data[13] - data[9] * data[14]) + data[5] * (data[8] * data[14] - data[10] * data[12]) + data[6] * (data[9] * data[12] - data[8] * data[13])),   // 12  3
				det*(data[8] * (data[2] * data[13] - data[1] * data[14]) + data[9] * (data[0] * data[14] - data[2] * data[12]) + data[10] * (data[1] * data[12] - data[0] * data[13])),    // 13  7
				det*(data[12] * (data[2] * data[5] - data[1] * data[6]) + data[13] * (data[0] * data[6] - data[2] * data[4]) + data[14] * (data[1] * data[4] - data[0] * data[5])),        // 14  11
				det*(data[0] * (data[5] * data[10] - data[6] * data[9]) + data[1] * (data[6] * data[8] - data[4] * data[10]) + data[2] * (data[4] * data[9] - data[5] * data[8])));        // 15  15

		}
		return *this;
	}

	real const& mat4::operator[](unsigned int i) const
	{
		//if (i < 0 || i>15)
		//	return static_cast<real>(0.0);
		assert(i < 16);
		return data[i];
	}

	//real const& mat4::operator[](int i) const
	//{
	//	// todo; in debug should log this
	//	//if (i < 0 || i>15) {
	//	//	return static_cast<real>(0.0);
	//	//}
	//	assert(i < 16);
	//	return data[i];
	//}

	real &mat4::operator[](unsigned int i)
	{
		// todo: in debug should log this
		//if (i < 0 || i>15)
		//	return dummy;
		return *(&data[i]);
	}

	vec3 mat4::column(unsigned int n) const
	{
		if (n < 0 || n > 3)
			return vec3();
		unsigned int e(n * 4);
		return vec3(data[e], data[e + 1], data[e + 2]);
	}

	vec3 mat4::row(unsigned int n) const
	{
		if (n < 0 || n > 3)
			return vec3();
		return vec3(data[n], data[n + 4], data[n + 8]);
	}



} // namespace sge
