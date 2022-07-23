#include "quad.h"

namespace sge
{

	Quad::Quad()
	{
	}

	Quad::Quad(const vec3* v)
	{
		corner[BOTTOM_LEFT] = v[0];
		corner[BOTTOM_RIGHT] = v[1];
		corner[TOP_RIGHT] = v[2];
		corner[TOP_LEFT] = v[3];
		calc_center();
	}

	Quad::Quad(const vec3& bottomleft, const vec3& bottomright, const vec3& topright, const vec3& topleft)
	{
		corner[BOTTOM_LEFT] = bottomleft;
		corner[BOTTOM_RIGHT] = bottomright;
		corner[TOP_RIGHT] = topright;
		corner[TOP_LEFT] = topleft;
		calc_center();
	}

	void Quad::calc_center()
	{
		center = corner[BOTTOM_LEFT] + (corner[TOP_RIGHT] - corner[BOTTOM_LEFT]) * 0.5f;
	}

	void Quad::GetTriangle(vec3& p0, vec3& p1, vec3& p2, bool tri2, bool left_hand)
	{
		// not tr2 means lower triangle
		if (!tri2) {
			if (!left_hand) {
				p0 = corner[BOTTOM_LEFT];
				p1 = corner[BOTTOM_RIGHT];
				p2 = corner[TOP_LEFT];
			}
			else {
				p0 = corner[BOTTOM_LEFT];
				p1 = corner[TOP_LEFT];
				p2 = corner[BOTTOM_RIGHT];
			}
		}
		else {
			if (!left_hand) {
				p0 = corner[TOP_LEFT];
				p1 = corner[BOTTOM_RIGHT];
				p2 = corner[TOP_RIGHT];
			}
			else {
				p0 = corner[BOTTOM_RIGHT];
				p1 = corner[TOP_LEFT];
				p2 = corner[TOP_RIGHT];
			}
		}



	}

} // sge
