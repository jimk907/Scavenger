#pragma once
#include "sge_defines.h"


namespace sge
{

	// fwd decelarations
	class vec2i;


	class vec2
	{
	public:
		~vec2();
		vec2();
		vec2(real f);
		vec2(real x, real y);
		vec2(real *v);
		vec2(const vec2&  other);
		vec2(const vec2i&  other);

		void clear();
		void set(real x, real y);
		void set(real *v);
		void set(const vec2&  other);
		void set(const vec2i&  other);

		real& operator[](unsigned int i);

		vec2&  operator=(const vec2&  rhs);
		vec2&  operator+=(const vec2&  rhs);
		vec2&  operator-=(const vec2&  rhs);
		vec2&  operator*=(const vec2&  rhs);
		vec2&  operator/=(const vec2&  rhs);
		vec2&  operator-();
		vec2&  operator*=(real s);
		vec2&  operator/=(real s);

		vec2 operator*(real s);
		vec2 operator/(real s);
		vec2 operator+(const vec2&  rhs) const;
		vec2 operator-(const vec2&  rhs) const;
		vec2 operator*(const vec2&  rhs) const;
		vec2 operator/(const vec2&  rhs) const;

		bool operator==(const vec2&  rhs) const;
		bool operator!=(const vec2&  rhs) const;

		real length() const;
		real dot(const vec2&  rhs) const;
		real distance(const vec2&  rhs) const;
		vec2  normalized() const;
		vec2& normalize();

		std::string log_text() const;

		inline operator real*() { return data; }

		union {
			struct {
				real x;	
				real y;	
			};
			real data[2];
		};
	};



	// Implements a 2-component integer vector class.
	class vec2i
	{
	public:
		~vec2i();
		vec2i();
		vec2i(i32 x, i32 y);
		vec2i(i32 x);
		vec2i(i32 *v);
		vec2i(const vec2i&  other);
		vec2i(const vec2&  other);

		void clear();
		void set(i32 x);
		void set(i32 x, i32 y);
		void set(i32 *v);
		void set(const vec2i&  other);
		void set(const vec2&  other);

		i32 &operator[](u8 i);

		vec2i&  operator=(const vec2i&  rhs);
		vec2i&  operator+=(const vec2i&  rhs);
		vec2i&  operator-=(const vec2i&  rhs);
		vec2i&  operator*=(const vec2i&  rhs);
		vec2i&  operator/=(const vec2i&  rhs);
		vec2i&  operator-();
		vec2i&  operator*=(i32 s);
		vec2i&  operator/=(i32 s);

		vec2i operator*(i32 s);
		vec2i operator/(i32 s);
		vec2i operator+(const vec2i&  rhs) const;
		vec2i operator-(const vec2i&  rhs) const;
		vec2i operator*(const vec2i&  rhs) const;
		vec2i operator/(const vec2i&  rhs) const;

		bool operator==(const vec2i&  rhs) const;
		bool operator!=(const vec2i&  rhs) const;

		i32    length() const;
		i32    dot(const vec2i&  rhs) const;
		i32    distance(const vec2i&  rhs) const;
		vec2i  normalized() const;
		vec2i& normalize();

		//void  set_angle_len(real angle, i32 len = 0);
		//real get_angle() const;


		//=========== WIN32 Specific ===============//
	#ifdef _WIN32
		vec2i(const POINT& pt);
		vec2i& operator=(const POINT& pt);
	#endif

		std::string log_text() const;

		union {
			struct {
				i32 x;	
				i32 y;	
			};
			i32 data[2];
		};
	};

} // namespace sge

