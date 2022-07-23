#pragma once

#include "sge_defines.h"
#include "math/vec3.h"

namespace sge
{


	class Quad
	{
	public:
		enum {
			BOTTOM_LEFT = 0,
			BOTTOM_RIGHT = 1,
			TOP_RIGHT = 2,
			TOP_LEFT = 3,
		};

		Quad();
		Quad(const vec3* v);
		Quad(const vec3& bottomleft, const vec3& bottomright, const vec3& topright, const vec3& topleft);
		~Quad() {}

		void GetTriangle(vec3& p0, vec3& p1, vec3& p2, bool tri2, bool left_hand = false);

		vec3 center;
		vec3 corner[4];

	protected:
		void calc_center();
	};


} // namespace sge

