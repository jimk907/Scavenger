#pragma once
#include "sge_defines.h"
#include <iostream>


namespace sge
{

	class vec2;
	class mat4;


	class vec3
	{
	public:
		~vec3();
		vec3();
		vec3(real f);
		vec3(real x, real y, real z);
		vec3(real *v);
		vec3(const vec3 &other);
		vec3(const vec2&  other);

		void clear();
		void set(real x, real y, real z);
		void set(real *v);
		void set(const vec3 &other);
		void set(const vec2&  other);

		real operator[](unsigned int i) const;
		real operator[](int i) const;

		real &operator[](unsigned int i);

		vec3 operator-() const;
		vec3 operator-(const vec3 &rhs) const;
		vec3 operator+(const vec3 &rhs) const;
		vec3 operator*(const vec3 &rhs) const;
		vec3 operator*(const mat4 &rhs) const;
		vec3 operator*(real rhs) const;
		vec3 operator/(real rhs) const;

		friend vec3 operator*(real lhs, const vec3 &rhs);

		// Negate this.
		vec3& operator-();
		vec3& operator=(const vec3 &rhs);
		vec3& operator+=(const vec3 &rhs);
		vec3& operator-=(const vec3 &rhs);
		vec3& operator*=(const vec3 &rhs);
		vec3& operator*=(const mat4 &rhs);
		vec3& operator+=(real  rhs);

		bool operator==(const vec3 &rhs) const;
		bool operator!=(const vec3 &rhs) const;

		real length() const;
		real dot(const vec3 &rhs) const;
		real distance(const vec3 &rhs) const;
		vec3 crossed(const vec3 &rhs) const;
		vec3& cross(const vec3 &rhs);
		vec3  normalized() const;
		vec3& normalize();

		vec3 lerp(const vec3 &start, const vec3 &end, real percent);
		vec3 nlerp(const vec3 &start, const vec3 &end, real percent);

		operator real*() { return data; }

		static vec3 cross(const vec3 &a, const vec3 &b);
		static real dot(const vec3 &a, const vec3 &b);

		friend inline std::ostream& operator << (std::ostream& output, const vec3& v)
		{
			char buffer[64];
			snprintf(buffer, 64, "(%7.4f, %7.4f, %7.4f)", v.x, v.y, v.z);
			output << buffer << std::endl;
			return output;
		}

		union {
			struct {
				real x;	 
				real y;	 
				real z;	 
			};
			real data[3];
		};
	};


} // namespace sge

