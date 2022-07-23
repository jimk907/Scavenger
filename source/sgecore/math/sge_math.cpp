#include "sge_defines.h"
#include "sge_math.h"
#include "vec3.h"
#include "vec4.h"

namespace sge
{

	real Min(real a, real b) { return (a < b) ? a : b; }

	real Max(real a, real b) { return (a > b) ? a : b; }

	real Norm(real value, real min, real max) { return (value - min) / (max - min); }

	real Lerp(real norm, real min, real max) { return (max - min) * norm + min; }

	vec3 Lerp(real norm, vec3 min, vec3 max) { return (max - min) * norm + min; }

	vec4 Lerp(real norm, vec4 min, vec4 max) { return (max - min) * norm + min; }

	vec3 Slerp(real norm, vec3 min, vec3 max)
	{
		// https://keithmaggio.wordpress.com/2011/02/15/math-magician-lerp-slerp-and-nlerp/
		real dot = min.dot(max);
		real theta = ACOS(dot) * norm;
		vec3  vec(max - min * dot);
		vec.normalize();
		return (min * COS(theta)) + (vec * SIN(theta));
	}

	vec3 Nlerp(real norm, vec3 min, vec3 max) { return ((max - min) * norm + min).normalize(); }

	real Map(real value, real srcMin, real srcMax, real dstMin, real dstMax) { return Lerp(Norm(value, srcMin, srcMax), dstMin, dstMax); }

	real Clamp(real value, real min, real max) { return Min(Max(value, Min(min, max)), Max(min, max)); }

	real DistanceXY(real x0, real y0, real x1, real y1)
	{
		real dx = x1 - x0;
		real dy = y1 - y0;
		return static_cast<real>(SQRT(dx * dx + dy * dy));
	}

	real DistanceXYZ(real x0, real y0, real z0, real x1, real y1, real z1)
	{
		real dx = x1 - x0;
		real dy = y1 - y0;
		real dz = z1 - z0;
		return static_cast<real>(SQRT(dx * dx + dy * dy + dz * dz));
	}

	bool InRange(real value, real min, real max)
	{
		return value >= Min(min, max) && value <= Max(min, max);
	}

	bool RangeInteresect(real min0, real max0, real min1, real max1)
	{
		return Max(min0, max0) >= Min(min1, max1) &&
			Min(min0, max0) <= Max(min1, max1);
	}

	real Randomf()
	{
		return static_cast<real>(std::rand()) / (RAND_MAX + static_cast<real>(1.0));
	}

	real Random(real min, real max)
	{
		return min + (max - min) * Randomf();
	}

	real Random(real max)
	{
		return max * Randomf();
	}

	int Random(int min, int max)
	{
		return min + static_cast<int>((max - min) * Randomf());
	}

	int Random(int max)
	{
		return static_cast<int>(max * Randomf());
	}

	vec3 Random(const vec3& min, const vec3& max)
	{
		return vec3(Random(min.x, max.x),
					Random(min.y, max.y),
					Random(min.z, max.z));
	}

	vec4 Random(const vec4& min, const vec4& max)
	{
		return vec4(Random(min.x, max.x),
					Random(min.y, max.y),
					Random(min.z, max.z),
					Random(min.w, max.w));
	}

	real DegToRad(real deg)
	{
		return deg / static_cast<real>(180.0) * R_PI;
	}

	real RadToDeg(real rad)
	{
		return rad * static_cast<real>(180.0) / R_PI;
	}

} // namespace sge
