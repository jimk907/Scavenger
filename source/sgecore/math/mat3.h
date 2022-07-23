#pragma once

#include "sge_defines.h"
#include <iostream>


namespace sge
{

	class vec2;
	class vec3;
	class vec4;
	class mat4;


	class mat3
	{
	public:
		real data[9];	       
							
		mat3();
		mat3(real *f);
		mat3(real scale);
		mat3(real xx, real xy, real xz,
			 real yx, real yy, real yz,
			 real zx, real zy, real zz);
		mat3(const mat3 &copy);
		mat3(const mat4 &copy);

		mat3& clear();
		mat3& identity();
		mat3& transpose();
		mat3& set(real *f);
		mat3& set(real scale);
		mat3& set(real xx, real xy, real xz,
				  real yx, real yy, real yz,
				  real zx, real zy, real zz);
		mat3& set(const mat3 &copy);
		mat3& set(const mat4 &copy);
		mat3& set(const vec3 &xaxis, const vec3 &yaxis, const vec3 &zaxis);
		mat3& scale(real s);
		mat3& scale(real x, real y, real z);
		mat3& spin(real deg, const vec3 axis);
		mat3& rotate_x(real deg);
		mat3& rotate_y(real deg);
		mat3& rotate_z(real deg);
		mat3& rotate_yxz(real y, real x, real z);
		mat3& rotate(real deg, const vec3& axis);
		mat3& rotate(real deg, real x, real y, real z);
		mat3& set_rotate_x(real deg);
		mat3& set_rotate_y(real deg);
		mat3& set_rotate_z(real deg);
		mat3& column(int i, const vec3& vec);
		mat3& column_x(const vec3& vec);
		mat3& column_y(const vec3& vec);
		mat3& column_z(const vec3& vec);

		mat3& operator=(const mat3& rhs);
		mat3& operator=(const real* rhs);
		mat3& operator*=(const mat3& rhs);
		mat3& invert();

		vec2 operator*(const vec2&) const;
		vec3 operator*(const vec3&) const;
		mat3 operator*(const mat3&) const;

		vec3  axis_x();
		vec3  axis_y();
		vec3  axis_z();

		real determinant();

		real const operator[](unsigned int i) const;
		//real const operator[](int i) const;

		real &operator[](unsigned int i);
		vec3 column(unsigned int n) const;
		vec3 row(unsigned int n) const;

		friend inline std::ostream& operator << (std::ostream& output, const mat3& m)
		{
			char buffer[64];
			snprintf(buffer, 64, "(%7.4f, %7.4f, %7.4f)", m[0], m[3], m[6]);
			output << buffer << std::endl;
			snprintf(buffer, 64, "(%7.4f, %7.4f, %7.4f)", m[1], m[4], m[7]);
			output << buffer << std::endl;
			snprintf(buffer, 64, "(%7.4f, %7.4f, %7.4f)", m[2], m[5], m[8]);
			output << buffer << std::endl;
			return output;
		}

	};



} // namespace sge

