#pragma once


#include "sge_defines.h"
#include "math/vec3.h"
#include "math/mat4.h"


namespace sge
{

	class BillboardMatrix
	{
	public:
		BillboardMatrix();
		virtual ~BillboardMatrix()
		{
		}

		mat4 Point(const vec3& pos, const vec3& target, const vec3& up);
		mat4 AxisX(const vec3& pos, const vec3& target);
		mat4 AxisY(const vec3& pos, const vec3& target);
		mat4 AxisZ(const vec3& pos, const vec3& target);
		mat4 Arbitrary(const vec3& pos, const vec3& target, const vec3& arbitrary);

	protected:
		mat4& AimTo(const vec3& position, const vec3& look, const vec3& right, const vec3& up);

		union {
			struct {
				vec3 x_axis;
				f32 xw;
				vec3 y_axis;
				f32 yw;
				vec3 z_axis;
				f32 zw;
				vec3 translate;
				f32 tw;
			};
			f32 elements[16];
			mat4 matrix;
		};
	};


} // nmaespace sge

