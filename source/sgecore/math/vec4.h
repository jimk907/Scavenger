#pragma once
#include "sge_defines.h"



namespace sge
{

// fwd declarations
class vec3;
class mat4;

class vec4
{
public:
	vec4();
	vec4(real *f);
	vec4(real f);
	vec4(real x, real y, real z, real w);
	vec4(vec3 v, real w);
	vec4(real *v, real w);
	vec4(const vec4 &copy);

	vec4& clear();
	vec4& set(real *f);
	vec4& set(real f);
	vec4& set(real x, real y, real z, real w);

	vec4 operator-() const;
	vec4 operator-(const vec4 &rhs) const;
	vec4 operator+(const vec4 &rhs) const;
	vec4 operator*(const vec4 &rhs) const;
	vec4 operator*(const mat4 &rhs) const;
	vec4 operator*(real rhs) const;
	vec4 operator/(real rhs) const;

	vec4 operator*(real v);

	real operator[](unsigned int i) const;
	real operator[](int i) const;

	real &operator[](unsigned int i);

	operator real*() { return data; }

	union {
		struct {
			real x;	
			real y;	
			real z;	
			real w;	
		};
		real data[4];
	};
};


} // namespace sge

