#pragma once

#include "sge_defines.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
//#ifndef _LIMITS_
//#include <limits>
//#endif
//#ifndef _CSTDLIB_
//#include <cstdlib>
//#endif
//#include <math.h>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"
#include "plane.h"
#include "quat.h"

namespace sge
{

	// fwd declarations
	//class vec2;
	//class vec3;
	//class vec4;

	// Return the minimum of two values.
	template <typename T>
	T Min(T a, T b)
	{
		return a < b ? a : b;
	}

	// Return the maximum of two values.
	template <typename T>
	T Max(T a, T b)
	{
		return a > b ? a : b;
	}

	// Swap two values.
	template <typename T>
	void Swap(T *a, T *b)
	{
		T x(*a);
		*a = *b;
		*b = x;
	}

	// Returns a value norm between two extents.
	// return: (v-min)/(max-min)
	real Norm(real value, real min, real mnax);

	// Perform a linear interpolation between two values.
	real Lerp(real norm, real min, real max);

	// Perform a linear interpolation between two vectors.
	vec3 Lerp(real norm, vec3 min, vec3 max);

	// Perform a linear interpolation between two vec4's.
	vec4 Lerp(real norm, vec4 min, vec4 max);

	// Interpolate percent of rotation between two vectors.
	vec3 Slerp(real norm, vec3 min, vec3 max);
	vec3 Lerp(real norm, vec3 min, vec3 max);

	// Interpolate percent of rotation between two vectors.
	vec3  Nlerp(real norm, vec3 min, vec3 max);

	// Maps a value from one range to another range.
	real Map(real value, real srcMin, real srcMax, real dstMin, real dstMax);

	// Returns a value clamped between two limits.
	real Clamp(real value, real min, real max);

	// Returns the distance between two 2-D points(x,y).
	real DistanceXY(real x0, real y0, real x1, real y1);

	// Returns the distance between two 3-D points(x,y,z).
	real DistanceXYZ(real x0, real y0, real z0, real x1, real y1, real z1);

	// Returns true if a value is between two values (inclusive).
	bool InRange(real value, real min, real max);

	// Returns true if two ranges overlap (inclusive).
	bool RangeInteresect(real min0, real max0, real min1, real max1);

	// Returns a realing point random number between static_cast<real>(0.0) - static_cast<real>(1.0).
	real Randomf();

	// Returns a realing point random number between min and max values.
	real Random(real min, real max);

	// Returns a realing point random number between static_cast<real>(0.0) and max.
	real Random(real max);

	// Returns an integer random number between min and max.
	int Random(int min, int max);

	// Returns an integer random number between 0 and max.
	int Random(int max);

	// Returns a random vector bewteen vec3 min & max.
	vec3 Random(const vec3& min, const vec3& max);

	// Returns a random vector bewteen vec4 min & max.
	vec4 Random(const vec4& min, const vec4& max);

	// see: http://www.redditmirror.cc/cache/websites/mjolnirstudios.com_7yjlc/mjolnirstudios.com/IanBullard/files/79ffbca75a75720f066d491e9ea935a0-10.html
	// Implements a fast random number generator class suitable for most game applications.
	class Frand
	{
		// Default constructor.
		Frand() : high(0), low(0)
		{
			seed(0xDEADBEEF);
		}

		// Returns a random u32.
		unsigned int rand()
		{
			high = (high << 16) + (high >> 16);
			high += low;
			low += high;
			return high;
		}

		// Set the seed to 'val'.
		void seed(unsigned int val)
		{
			high = val;
			low = high ^ 0x49616E42;
		}

		// Set the seed to hi, lo.
		void seed(unsigned int hi, unsigned int lo)
		{
			high = hi;
			low = lo;
		}
	private:
		unsigned int high;
		unsigned int low;
	};

	// Return degrees to readians.
	real DegToRad(real deg);

	// Return radians to degrees.
	real RadToDeg(real rad);

	// Return fast real to u32 (does rounding).
	inline unsigned int f_to_uint(real f)
	{
		f += 1 << 23;
		return (unsigned int)f & 0x7fffff;
	}

	// these definitions are used by the audio importer
	#pragma pack(push)
	#pragma pack(2)
	typedef unsigned char tDouble80[10];
	#pragma pack(pop)

	typedef struct {
		unsigned __int64 mantissa : 64;
		unsigned int exponent : 15;
		unsigned int sign : 1;
	} tDouble80Struct;

	inline double convertDouble80(const tDouble80& val)
	{
		assert(10 == sizeof(tDouble80));

		const tDouble80Struct* valStruct = reinterpret_cast<const tDouble80Struct*>(&val);

		const unsigned int mask_exponent = (1 << 15) - 1;
		const unsigned __int64 mantissa_high_highestbit = unsigned __int64(1) << 63;
		const unsigned __int64 mask_mantissa = 9223372036854775807Ui64; // (unsigned __int64(1) << 63) - 1;

		if (mask_exponent == valStruct->exponent) {

			if (0 == valStruct->mantissa) {
				return (0 != valStruct->sign) ? -std::numeric_limits<double>::infinity() : std::numeric_limits<double>::infinity();
			}

			// highest mantissa bit set means quiet NaN
			return (0 != (mantissa_high_highestbit & valStruct->mantissa)) ? std::numeric_limits<double>::quiet_NaN() : std::numeric_limits<double>::signaling_NaN();
		}

		// 80 bit realing point value according to the IEEE-754 specification and 
		// the Standard Apple Numeric Environment specification:
		// 1 bit sign, 15 bit exponent, 1 bit normalization indication, 63 bit mantissa

		const double sign(valStruct->sign ? -1 : 1);


		//If the highest bit of the mantissa is set, then this is a normalized number.
		unsigned __int64 mantissa = valStruct->mantissa;
		double normalizeCorrection = (mantissa & mantissa_high_highestbit) != 0 ? 1 : 0;
		mantissa &= mask_mantissa;

		//value = (-1) ^ s * (normalizeCorrection + m / 2 ^ 63) * 2 ^ (e - 16383)
		return (sign * (normalizeCorrection + double(mantissa) / mantissa_high_highestbit) * pow(2.0, int(valStruct->exponent) - 16383));
	}

} // namespace sge

