#pragma once
#include "vec3.h"



namespace sge
{


	class mat4;


	class quat
	{
	public:
		union {
			struct {
				real w;
				real x;
				real y;
				real z;
			};
			real data[4];
		};
	public:
		quat();
		quat(real w, real x, real y, real z);
		quat(real *v);
		quat(const quat &other);
		quat(const vec3 &v, real w);
		quat(real angle, const vec3 &axis);
		quat(real yaw, real pitch, real roll);
		quat(const mat4 &m);
		~quat();

		quat &clear();
		quat &set(real w, real x, real y, real z);
		quat &set(real *v);
		quat &set(const quat &other);
		quat &set(const vec3 &v, real w);
		quat &set(real angle, const vec3 &axis);
		quat &set(real yaw, real pitch, real roll);
		quat &set(const mat4 &m);

		quat &operator=(const quat &rhs);
		quat &operator+=(const quat &rhs);
		quat &operator-=(const quat &rhs);
		quat &operator*=(const quat &rhs);
		quat &operator/=(const quat &rhs);
		quat &operator*(real s);
		quat &operator-();
		quat &invert();

		quat operator+(const quat &rhs) const;
		quat operator-(const quat &rhs) const;
		quat operator*(const quat &rhs) const;
		quat operator/(const quat &rhs) const;
		quat operator*(real s) const;
		quat operator-() const;

		bool operator==(const quat &rhs) const;
		bool operator!=(const quat &rhs) const;

		quat inverse() const;
		quat scale(real scale) const;
		quat unitize() const;
		quat normalize() const;
		quat slerp(real pct, const quat &q2) const;
		quat lerp(real pct, const quat &q2) const;

		mat4 mat4x4() const;
		vec3 operator*(const vec3 rhs);

		inline quat conjugate() const { return quat(vec3(-x, -y, -z), w); }
		inline vec3 complex() const { return vec3(x, y, z); }
		inline real operator[](unsigned int n) { return data[n]; }
		inline real norm() const { return x * x + y * y + z * z + w * w; }
		inline real magnitude() const { return SQRT(x*x + y * y + z * z + w * w); }
		inline real dot(const quat &q) const { return w * q.w + x * q.x + y * q.y + z * q.z; }
		inline void identity() { x = static_cast<real>(0.0); y = static_cast<real>(0.0); z = static_cast<real>(0.0); w = static_cast<real>(1.0); }

		friend inline std::ostream& operator << (std::ostream& output, const quat& q)
		{
			output << "[" << q.w << ", " << "(" << q.x << ", " << q.y << ", " << q.z << ")]";
			return output;
		}

	};


} // namespace sge

