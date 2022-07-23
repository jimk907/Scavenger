#include "billboardmatrix.h"

namespace sge
{


	BillboardMatrix::BillboardMatrix()
		: x_axis(1.0f, 0.0f, 0.0f)
		, y_axis(0.0f, 1.0f, 0.0f)
		, z_axis(0.0f, 0.0f, 1.0f)
		, translate(0.0f, 0.0f, 0.0f)
		, xw(0.0f)
		, yw(0.0f)
		, zw(0.0f)
		, tw(1.0f)
	{
	}

	mat4& BillboardMatrix::AimTo(const vec3& position, const vec3& look, const vec3& right, const vec3& up)
	{
		x_axis = right;
		y_axis = up;
		z_axis = look;
		translate = position;
		xw = 0.0f;
		yw = 0.0f;
		zw = 0.0f;
		tw = 1.0f;
		return matrix;
	}

	mat4 BillboardMatrix::Point(const vec3& pos, const vec3& target, const vec3& targetup)
	{
		vec3 look((pos - target).normalized());
		vec3 right(targetup.crossed(look));
		vec3 up(look.crossed(right));
		return AimTo(pos, look, right, up);
	}

	mat4 BillboardMatrix::AxisX(const vec3& pos, const vec3& target)
	{
		vec3 look(target - pos);
		look.x = 0.0f;
		look.normalize();
		vec3 up(1.0f, 0.0f, 0.0f);
		vec3 right(up.crossed(look));
		return AimTo(pos, look, right, up);
	}

	mat4 BillboardMatrix::AxisY(const vec3& pos, const vec3& target)
	{
		vec3 look(target - pos);
		look.y = 0.0f;
		look.normalize();
		vec3 up(0.0f, 1.0f, 0.0f);
		vec3 right(up.crossed(look));
		return AimTo(pos, look, -right, up);
	}

	mat4 BillboardMatrix::AxisZ(const vec3& pos, const vec3& target)
	{
		vec3 look(target - pos);
		look.z = 0.0f;
		look.normalize();
		vec3 up(0.0f, 0.0f, 1.0f);
		vec3 right(up.crossed(look));
		return AimTo(pos, look, right, up);
	}

	mat4 BillboardMatrix::Arbitrary(const vec3& pos, const vec3& target, const vec3& arbitrary)
	{
		vec3 look((target - pos).normalized());
		vec3 up(arbitrary.normalized());
		vec3 right(up.crossed(look));
		look = right.crossed(up);
		return AimTo(pos, look, right, up);
	}

} // nmaespace sge

