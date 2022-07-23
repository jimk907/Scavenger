#include "quat.h"
#include "mat4.h"
#include "sge_math.h"


namespace sge
{

	quat::quat()
		: w(static_cast<real>(1.0))
		, x(static_cast<real>(0.0))
		, y(static_cast<real>(0.0))
		, z(static_cast<real>(0.0))
	{
	}

	quat::quat(real W, real X, real Y, real Z)
		: w(W)
		, x(X)
		, y(Y)
		, z(Z)
	{
	}

	quat::quat(real *v)
		: w(v[0])
		, x(v[1])
		, y(v[2])
		, z(v[3])
	{
	}

	quat::quat(const quat &other)
		: w(other.w)
		, x(other.x)
		, y(other.y)
		, z(other.z)
	{
	}

	quat::quat(const vec3 &v, real W)
		: w(W)
		, x(v.x)
		, y(v.y)
		, z(v.z)
	{
	}

	quat::quat(real angle, const vec3 &axis)
	{
		set(angle, axis);
	}

	quat::quat(real yaw, real pitch, real roll)
	{
		set(yaw, pitch, roll);
	}

	quat::quat(const mat4 &m)
	{
		set(m);
	}

	quat::~quat()
	{
	}

	quat &quat::clear()
	{
		w = static_cast<real>(0.0);
		x = static_cast<real>(0.0);
		y = static_cast<real>(0.0);
		z = static_cast<real>(0.0);
		return *this;
	}

	quat &quat::set(real W, real X, real Y, real Z)
	{
		w = W;
		x = X;
		y = Y;
		z = Z;
		return *this;
	}

	quat &quat::set(real *v)
	{
		w = v[0];
		x = v[1];
		y = v[2];
		z = v[3];
		return *this;
	}

	quat &quat::set(const quat &other)
	{
		w = other.w;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	quat &quat::set(const vec3 &v, real W)
	{
		w = W;
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	quat &quat::set(real angle, const vec3 &axis)
	{
		real rads(angle * DEGREES * static_cast<real>(0.5));
		real sa(static_cast<real>(sin(rads)));
		w = static_cast<real>(cos(rads));
		x = sa * axis.x;
		y = sa * axis.y;
		z = sa * axis.z;
		return *this;
	}

	quat &quat::set(real yaw, real pitch, real roll)
	{
		// yaw = z-roll!
		// pitch = x-axis!
		real dtr2(DEGREES * static_cast<real>(0.5));
		real _yaw(yaw * dtr2);
		real _pitch(pitch * dtr2);
		real _roll(roll * dtr2);
		// calculate trig identities
		real cr(COS(_roll));
		real cp(COS(_pitch));
		real cy(COS(_yaw));
		real sr(SIN(_roll));
		real sp(SIN(_pitch));
		real sy(SIN(_yaw));
		real cpcy(cp * cy);
		real spsy(sp * sy);
		w = cr * cpcy + sr * spsy;
		x = cr * sp * cy + sr * cp * sy;
		y = cr * cp * sy - sr * sp * cy;
		z = sr * cpcy - cr * spsy;
		return *this;
	}

	quat &quat::set(const mat4 &m)
	{
		real  trace, s, q[4];
		int i, j, k;
		int nxt[3] = { 1, 2, 0 };
		trace = m.data[0] + m.data[5] + m.data[10];

		// check the diagonal
		if (trace > 0.0)
		{
			s = SQRT(trace + static_cast<real>(1.0));
			w = s / static_cast<real>(2.0);
			s = static_cast<real>(0.5) / s;
			x = (m[6] - m[9]) * s;
			y = (m[8] - m[2]) * s;
			z = (m[1] - m[4]) * s;
		}
		else
		{
			// diagonal is negative
			i = 0;
			if (m[5] > m[0]) i = 1;
			if (m[10] > m[i * 4 + i]) i = 2;
			j = nxt[i];
			k = nxt[j];
			s = static_cast<real>(SQRT((m[i * 4 + i] - (m[j * 4 + j] + m[k * 4 + k])) + static_cast<real>(1.0)));
			q[i] = s * static_cast<real>(0.5);
			if (s != static_cast<real>(0.0)) s = static_cast<real>(0.5) / s;
			q[3] = (m[j * 4 + k] - m[k * 4 + j]) * s;
			q[j] = (m[i * 4 + j] + m[j * 4 + i]) * s;
			q[k] = (m[i * 4 + k] + m[k * 4 + i]) * s;
			x = q[0];
			y = q[1];
			z = q[2];
			w = q[3];
		}
		return *this;
	}

	quat &quat::operator=(const quat &rhs)
	{
		w = rhs.w;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	quat &quat::operator+=(const quat &rhs)
	{
		w += rhs.w;
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	quat &quat::operator-=(const quat &rhs)
	{
		w -= rhs.w;
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	quat &quat::operator*=(const quat &rhs)
	{
		real a(y*rhs.z - z * rhs.y + x * rhs.w + w * rhs.x);
		real b(z*rhs.x - x * rhs.z + y * rhs.w + w * rhs.y);
		real c(x*rhs.y - y * rhs.x + z * rhs.w + w * rhs.z);
		real d(w*rhs.w - x * rhs.x - y * rhs.y - z * rhs.z);
		x = a;
		y = b;
		y = c;
		w = d;
		return *this;
	}

	quat &quat::operator/=(const quat &rhs)
	{
		(*this) = (*this) * rhs.inverse();
		return (*this);
	}

	quat &quat::operator*(real s)
	{
		// same as *this = scale(s);
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	quat &quat::operator-()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		return *this;
	}

	quat &quat::invert()
	{
		*this = inverse();
		return *this;
	}

	quat quat::operator+(const quat &rhs) const
	{
		return quat(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	quat quat::operator-(const quat &rhs) const
	{
		return quat(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	quat quat::operator*(const quat &rhs) const
	{
		return quat(
			w*rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,   // w
			y*rhs.z - z * rhs.y + x * rhs.w + w * rhs.x,   // x
			z*rhs.x - x * rhs.z + y * rhs.w + w * rhs.y,   // y
			x*rhs.y - y * rhs.x + z * rhs.w + w * rhs.z);  // z
	}

	quat quat::operator/(const quat &rhs) const
	{
		return quat((*this) * rhs.inverse());
	}

	quat quat::operator*(real s) const
	{
		return quat(x * s, y * s, z * s, w * s);
	}

	vec3 quat::operator*(const vec3 rhs)
	{
		//vec3 u(x, y, z);
		//real s(w);
		//// this does not work
		//// https://gamedev.stackexchange.com/a/50545
		////real ud = vec3::Dot(u, rhs);
		////real uu = vec3::Dot(u, u);
		//vec3 p = 2.0f * vec3::Dot(u, rhs) * u
		//	 + (s * s - vec3::Dot(u, u)) * rhs
		//     + 2.0f * s * vec3::Cross(u, rhs);
		//return p;

		// this method is almost 4x faster
		vec3 r;
		r.x = 2 * (w*rhs.z*y + x * rhs.z*z - w * rhs.y*z + x * rhs.y*y) + rhs.x*(w*w + x * x - y * y - z * z);
		r.y = 2 * (w*rhs.x*z + x * rhs.x*y - w * rhs.z*x + y * rhs.z*z) + rhs.y*(w*w - x * x + y * y - z * z);
		r.z = 2 * (w*rhs.y*x - w * rhs.x*y + x * rhs.x*z + y * rhs.y*z) + rhs.z*(w*w - x * x - y * y + z * z);
		return r;
	}

	quat quat::operator-() const
	{
		return quat(-x, -y, -z, -w);
	}

	bool quat::operator==(const quat &rhs) const
	{
		real a(x - rhs.x);
		real b(y - rhs.y);
		real c(z - rhs.z);
		real d(w - rhs.w);
		return(a > -EPSILON && a < EPSILON &&
			   b >-EPSILON && b < EPSILON &&
			   c >-EPSILON && c < EPSILON &&
			   d >-EPSILON && d < EPSILON);
	}

	bool quat::operator!=(const quat &rhs) const
	{
		return !(*this == rhs);
	}

	quat quat::inverse() const
	{
		return conjugate().scale(1 / norm());
	}

	quat quat::scale(real s) const
	{
		return quat(w * s, x * s, y * s, z * s);
	}

	quat quat::unitize() const
	{
		real len(this->magnitude());
		if (len < EPSILON)
			len = static_cast<real>(1.0);
		return quat(this->scale(static_cast<real>(1.0) / len));
	}

	quat quat::normalize() const
	{
		return unitize();
	}

	quat quat::slerp(real pct, const quat &q2) const
	{
		real from[] = { w, x, y, z };
		real to[] = { q2.w, q2.x, q2.y, q2.z };
		real com(dot(q2)); // cosine
		real to1[4];
		if (com < static_cast<real>(0.0)) {
			to1[0] = -to[0];
			to1[1] = -to[1];
			to1[2] = -to[2];
			to1[3] = -to[3];
		}
		else {
			to1[0] = to[0];
			to1[1] = to[1];
			to1[2] = to[2];
			to1[3] = to[3];
		}

		real scale0, scale1;
		if ((static_cast<real>(1.0) - com > EPSILON)) {
			real omega(static_cast<real>(acos(com)));
			real som(static_cast<real>(sin(omega)));
			scale0 = static_cast<real>(sin((static_cast<real>(1.0) - pct)) * omega) / som;
			scale1 = static_cast<real>(sin(pct * omega)) / som;
		}
		else {
			// too close together - do linear interp
			scale0 = static_cast<real>(1.0) - pct;
			scale1 = pct;
		}
		return quat(scale0*from[0] + scale1 * to1[0],
					scale0*from[1] + scale1 * to1[1],
					scale0*from[2] + scale1 * to1[2],
					scale0*from[3] + scale1 * to1[3]);
	}

	quat quat::lerp(real pct, const quat &q2) const
	{
		return ((*this)*(1 - pct) + q2 * pct).normalize();
	}

	mat4 quat::mat4x4() const
	{
		real x2(x * static_cast<real>(2.0));
		real y2(y * static_cast<real>(2.0));
		real z2(z * static_cast<real>(2.0));
		real wx(x2*w);
		real wy(y2*w);
		real wz(z2*w);
		real xx(x2*x);
		real xy(y2*x);
		real xz(z2*x);
		real yy(y2*y);
		real yz(z2*y);
		real zz(z2*z);
		return mat4(static_cast<real>(1.0) - (yy + zz), xy + wz, xz - wy, static_cast<real>(0.0),
					xy - wz, static_cast<real>(1.0) - (xx + zz), yz + wx, static_cast<real>(0.0),
					xz + wy, yz - wx, static_cast<real>(1.0) - (xx + yy), static_cast<real>(0.0),
					static_cast<real>(0.0), static_cast<real>(0.0), static_cast<real>(0.0), static_cast<real>(1.0));
	}


} // namespace sge
