#include "vec2.h"
#include "sge_math.h"


namespace sge
{


	vec2::~vec2()
	{
	}

	vec2::vec2()
		: x(static_cast<real>(0.0))
		, y(static_cast<real>(0.0))
	{
	}

	vec2::vec2(real f)
		: x(f)
		, y(f)
	{
	}

	vec2::vec2(real x, real y)
		: x(x)
		, y(y)
	{
	}

	vec2::vec2(real *v)
		: x(v[0])
		, y(v[1])
	{
	}

	vec2::vec2(const vec2&  other)
		: x(other.x)
		, y(other.y)
	{
	}

	vec2::vec2(const vec2i&  other)
		: x(static_cast<real>(other.x))
		, y(static_cast<real>(other.y))
	{
	}

	void vec2::clear()
	{
		x = static_cast<real>(0.0);
		y = static_cast<real>(0.0);
	}

	void vec2::set(real x, real y)
	{
		this->x = x;
		this->y = y;
	}

	void vec2::set(real *v)
	{
		x = v[0];
		y = v[1];
	}

	void vec2::set(const vec2&  other)
	{
		x = other.x;
		y = other.y;
	}

	void vec2::set(const vec2i&  other)
	{
		x = static_cast<real>(other.x);
		y = static_cast<real>(other.y);
	}

	real &vec2::operator[](unsigned int i)
	{
		assert(i >= 0 && i < 2);
		return *(&data[i]);
	}

	vec2&  vec2::operator=(const vec2&  rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	vec2&  vec2::operator+=(const vec2&  rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	vec2&  vec2::operator-=(const vec2&  rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	vec2&  vec2::operator*=(const vec2&  rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	vec2&  vec2::operator/=(const vec2&  rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	vec2&  vec2::operator*=(real s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	vec2&  vec2::operator/=(real s)
	{
		x /= s;
		y /= s;
		return *this;
	}

	vec2&  vec2::operator-()
	{
		x = -x;
		y = -y;
		return *this;
	}

	vec2 vec2::operator*(real s)
	{
		return vec2(x * s,
					y * s);
	}

	vec2 vec2::operator/(real s)
	{
		return vec2(x / s,
					y / s);
	}

	vec2 vec2::operator+(const vec2&  rhs) const
	{
		return vec2(x + rhs.x,
					y + rhs.y);
	}

	vec2 vec2::operator-(const vec2&  rhs) const
	{
		return vec2(x - rhs.x,
					y - rhs.y);
	}

	vec2 vec2::operator*(const vec2&  rhs) const
	{
		return vec2(x * rhs.x,
					y * rhs.y);
	}

	vec2 vec2::operator/(const vec2&  rhs) const
	{
		return vec2(x / rhs.x,
					y / rhs.y);
	}

	bool vec2::operator==(const vec2&  rhs) const
	{
		//real d = length() - rhs.length(); // not accurate!
		real d = x - rhs.x;
		real e = y - rhs.y;
		return ((d > -EPSILON && d < EPSILON) &&
			(e > -EPSILON && e < EPSILON));
	}

	bool vec2::operator!=(const vec2&  rhs) const
	{
		return !(*this == rhs);
	}

	real vec2::length() const
	{
		return static_cast<real>(SQRT(x*x + y * y));
	}

	real vec2::dot(const vec2&  rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	real vec2::distance(const vec2&  rhs) const
	{
		real dx(x - rhs.x);
		real dy(y - rhs.y);

		return static_cast<real>(SQRT(dx * dx + dy * dy));
	}

	vec2 vec2::normalized() const
	{
		real f = length();
		if (f == static_cast<real>(0.0))
			f = static_cast<real>(1.0);
		else
			f = static_cast<real>(1.0) / f;
		return vec2(x * f, y * f);
	}

	vec2& vec2::normalize()
	{
		real f = length();
		if (f == static_cast<real>(0.0))
			f = static_cast<real>(1.0);
		else
			f = static_cast<real>(1.0) / f;
		x *= f; y *= f;
		return *this;
	}

	//vec2& vec2::minimize(const vec2&  a)
	//{
	//	sge::Min(x, a.x);
	//	sge::Min(y, a.y);
	//	return *this;
	//}
	//
	//vec2& vec2::maximize(const vec2&  a)
	//{
	//	sge::Max(x, a.x);
	//	sge::Max(y, a.y);
	//	return *this;
	//}
	//
	//vec2& vec2::clamp(const vec2&  a, const vec2&  b)
	//{
	//	sge::Clamp(x, a.x, b.x);
	//	sge::Clamp(y, a.y, b.y);
	//	return *this;
	//}

	//void vec2::set_angle_len(real angle, real len)
	//{
	//	real mag(len);
	//	real rad(angle * DEGREES);
	//	if (mag == static_cast<real>(0.0)) 
	//		mag = length();
	//	x = COS(rad) * mag;
	//	y = SIN(rad) * mag;
	//
	//}
	//
	//real vec2::get_angle() const
	//{
	//	return static_cast<real>(atan2(y, x)) / DEGREES;
	//}
	//
	//real vec2::get_angle(const vec2&  other) const
	//{
	//	return static_cast<real>(atan2(y - other.x, x - other.y)) / DEGREES;
	//}

	std::string vec2::log_text() const
	{
		std::string msg = "x = " + std::to_string(x) + "; y = " + std::to_string(y);
		return msg;
	}

	//////////////////////////// ** vec2i ** //////////////////////////////////////


	vec2i::~vec2i()
	{
	}

	vec2i::vec2i()
		: x(0)
		, y(0)
	{
	}

	vec2i::vec2i(i32 x, i32 y)
	{
		this->x = x;
		this->y = y;
	}

	vec2i::vec2i(i32 x)
	{
		this->x = x;
		this->y = x;
	}

	vec2i::vec2i(i32 *v)
	{
		x = v[0];
		y = v[1];
	}

	vec2i::vec2i(const vec2i&  other)
	{
		x = other.x;
		y = other.y;
	}

	vec2i::vec2i(const vec2&  other)
	{
		x = static_cast<i32>(other.x);
		y = static_cast<i32>(other.y);
	}

	void vec2i::clear()
	{
		x = 0;
		y = 0;
	}

	void vec2i::set(i32 x)
	{
		this->x = x;
		this->y = x;
	}

	void vec2i::set(i32 x, i32 y)
	{
		this->x = x;
		this->y = y;
	}

	void vec2i::set(i32 *v)
	{
		x = v[0];
		y = v[1];
	}

	void vec2i::set(const vec2&  other)
	{
		x = static_cast<i32>(other.x);
		y = static_cast<i32>(other.y);
	}

	void vec2i::set(const vec2i&  other)
	{
		x = other.x;
		y = other.y;
	}

	i32 &vec2i::operator[](u8 i)
	{
		assert(i >= 0 && i < 2);
		return *(&data[i]);
	}

	vec2i&  vec2i::operator=(const vec2i&  rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	vec2i&  vec2i::operator+=(const vec2i&  rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	vec2i&  vec2i::operator-=(const vec2i&  rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	vec2i&  vec2i::operator*=(const vec2i&  rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	vec2i&  vec2i::operator/=(const vec2i&  rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	vec2i&  vec2i::operator*=(i32 s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	vec2i&  vec2i::operator/=(i32 s)
	{
		x /= s;
		y /= s;
		return *this;
	}

	vec2i&  vec2i::operator-()
	{
		x = -x;
		y = -y;
		return *this;
	}

	vec2i vec2i::operator*(i32 s)
	{
		return vec2i(x * s,
					 y * s);
	}

	vec2i vec2i::operator/(i32 s)
	{
		return vec2i(x / s,
					 y / s);
	}

	vec2i vec2i::operator+(const vec2i&  rhs) const
	{
		return vec2i(x + rhs.x,
					 y + rhs.y);
	}

	vec2i vec2i::operator-(const vec2i&  rhs) const
	{
		return vec2i(x - rhs.x,
					 y - rhs.y);
	}

	vec2i vec2i::operator*(const vec2i&  rhs) const
	{
		return vec2i(x * rhs.x,
					 y * rhs.y);
	}

	vec2i vec2i::operator/(const vec2i&  rhs) const
	{
		return vec2i(x / rhs.x,
					 y / rhs.y);
	}

	bool vec2i::operator==(const vec2i&  rhs) const
	{
		real d = (real)(x - rhs.x);
		real e = (real)(y - rhs.y);
		return ((d > -EPSILON && d < EPSILON) &&
			(e > -EPSILON && e < EPSILON));
	}

	bool vec2i::operator!=(const vec2i&  rhs) const
	{
		return !(*this == rhs);
	}

	i32 vec2i::length() const
	{
		return i32(SQRT(f32(x * x + y * y)));
	}

	i32 vec2i::dot(const vec2i&  rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	i32 vec2i::distance(const vec2i&  rhs) const
	{
		i32 dx(x - rhs.x);
		i32 dy(y - rhs.y);

		return i32(SQRT(f32(dx * dx + dy * dy)));
	}

	vec2i vec2i::normalized() const
	{
		real f = static_cast<real>(length());
		if (f == static_cast<real>(0.0))
			f = static_cast<real>(1.0);
		else
			f = static_cast<real>(1.0) / f;
		return vec2i(static_cast<i32>(static_cast<real>(x) * f), static_cast<i32>(static_cast<real>(y) * f));
	}

	vec2i& vec2i::normalize()
	{
		real f = static_cast<real>(length());
		if (f == static_cast<real>(0.0))
			f = static_cast<real>(1.0);
		else
			f = static_cast<real>(1.0) / f;
		x = static_cast<i32>(x * f);
		y = static_cast<i32>(y * f);
		return *this;
	}

	//void vec2i::set_angle_len(real angle, i32 len)
	//{
	//	real mag(static_cast<real>(len));
	//	real rad(angle * DEGREES);
	//	if (mag == static_cast<real>(0.0)) mag = static_cast<real>(length());
	//	x = static_cast<i32>(cos(rad) * mag);
	//	y = static_cast<i32>(sin(rad) * mag);
	//}
	//
	//real vec2i::get_angle() const
	//{
	//	return static_cast<real>(atan2(static_cast<real>(y), static_cast<real>(x))) / DEGREES;
	//}

	vec2i::vec2i(const POINT& pt)
	{
		x = pt.x;
		y = pt.y;
	}

	vec2i& vec2i::operator=(const POINT& pt)
	{
		x = pt.x;
		y = pt.y;
		return *this;
	}

	std::string vec2i::log_text() const
	{
		std::string msg = "x = " + std::to_string(x) + "; y = " + std::to_string(y);
		return msg;
	}



} // namespace sge

