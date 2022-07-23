#pragma once
#include "sge_defines.h"
#include <iostream>


namespace sge
{

	// fwd declarations
	class vec2;
	class vec3;
	class vec4;


	// Implements a 4x4 matrix class.
	// This is a column-major matrix:
	// 
	//          Element indices     ----   Axis  ----     
	//                               X    Y    Z    W
	//   mat4 = | 0, 4,  8, 12 |  | x.x, y.x, z.x, w.x |  
	//          | 1, 5,  9, 13 |  | x.y, y.y, z.y, w.y |  
	//          | 2, 6, 10, 14 |  | x.y, y.y, z.y, w.y |  
	//          | 3, 7, 11, 15 |  | x.y, y.y, z.y, w.y |
	//
	//          Scaling and translation:
	//          | sx  .  .  tx |  sx, sy, sx = scaling data
	//          | .   sy .  ty |  tx, ty, tz = translation data
	//          | .   .  sz tz |
	//          | .   .  .  .  |
	// 
	class mat4
	{
	public:
		mat4();
		mat4(real *f);
		mat4(real scale);
		mat4(real xx, real xy, real xz, real xw,
			 real yx, real yy, real yz, real yw,
			 real zx, real zy, real zz, real zw,
			 real wx, real wy, real wz, real ww);
		mat4(const mat4 &copy);

		mat4& clear();
		mat4& identity();
		mat4& transpose();
		mat4& set(real *f);
		mat4& set(real scale);
		mat4& set(real xx, real xy, real xz, real xw,
				  real yx, real yy, real yz, real yw,
				  real zx, real zy, real zz, real zw,
				  real wx, real wy, real wz, real ww);
		mat4& set(const mat4 &copy);
		mat4& set(const vec3 &xaxis, const vec3 &yaxis, const vec3 &zaxis);
		mat4& orthographic(real left, real right, real bottom, real top, real znear, real zfar);
		mat4& perspective(real fovy, real aspect, real znear, real zfar);
		mat4& setFrustum(real left, real right, real bottom, real top, real znear, real zfar);
		mat4& translate(real x, real y, real z);
		mat4& translate(const vec3& t);
		mat4& scale(real s);
		mat4& scale(real x, real y, real z);
		mat4& spin(real deg, const vec3 axis);
		mat4& rotate_x(real deg);
		mat4& rotate_y(real deg);
		mat4& rotate_z(real deg);
		mat4& rotate_yxz(real ydeg, real xdeg, real zdef);
		mat4& rotate(real deg, const vec3& axis);
		mat4& rotate(real deg, real x, real y, real z);
		mat4& set_rotate_x(real deg);
		mat4& set_rotate_y(real deg);
		mat4& set_rotate_z(real deg);
		mat4& lookat(const vec3& eye, const vec3& target, const vec3& up);

		vec2 operator*(const vec2&) const;
		vec3 operator*(const vec3&) const;
		vec4 operator*(const vec4&) const;
		mat4 operator*(const mat4&) const;

		mat4& operator=(const mat4&);
		mat4& operator=(const real* rhs);
		mat4& operator*=(const mat4&);

		mat4& column(int i, const vec3& vec);
		mat4& column_x(const vec3& vec);
		mat4& column_y(const vec3& vec);
		mat4& column_z(const vec3& vec);
		mat4& set_translation(const vec3& vec);
		mat4& set_translation(real *f);
		mat4& set_translation(real f);

		mat4& invert();

		vec3  axis_x();
		vec3  axis_y();
		vec3  axis_z();
		vec3  translation();

		real determinant();

		real const& operator[](unsigned int i) const;
		//real const& operator[](int i) const;

		real &operator[](unsigned int i);

		vec3 column(unsigned int n) const;
		vec3 row(unsigned int n) const;

		friend inline std::ostream& operator << (std::ostream& output, const mat4& m)
		{
			char buffer[64];
			snprintf(buffer, 64, "(%7.4f, %7.4f, %7.4f, %7.4f)", m[0], m[4], m[8], m[12]);
			output << buffer << std::endl;
			snprintf(buffer, 64, "(%7.4f, %7.4f, %7.4f, %7.4f)", m[1], m[5], m[9], m[13]);
			output << buffer << std::endl;
			snprintf(buffer, 64, "(%7.4f, %7.4f, %7.4f, %7.4f)", m[2], m[6], m[10], m[14]);
			output << buffer << std::endl;
			snprintf(buffer, 64, "(%7.4f, %7.4f, %7.4f, %7.4f)", m[3], m[7], m[11], m[15]);
			output << buffer << std::endl;
			return output;
		}

		union {
			real data[16];
			real row_cols[4][4];
		};
	};



} // namespace sge

