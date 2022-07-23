#include "frustum.h"
#include "math/vec3.h"
#include "math/mat4.h"


namespace sge
{


	Frustum::Frustum()
	{
	}

	Frustum::Frustum(const mat4& mat)
	{
		from_matrix(mat);
	}

	void Frustum::from_matrix(const mat4& view, const mat4& proj)
	{
		mat4 m = proj * view;
		from_matrix(m);
	}


	void Frustum::from_matrix(const mat4& m)
	{
		//
		// ref: Gil Gribb & Klaus Hartmann
		// Fast Extraction of Viewing Frustum Planes
		// from the World-View-Projection Matrix
		//

		// column major (opengl)
		p[LEFT_SIDE].a = m[12] + m[0];
		p[LEFT_SIDE].b = m[13] + m[1];
		p[LEFT_SIDE].c = m[14] + m[2];
		p[LEFT_SIDE].d = m[15] + m[3];

		p[RIGHT_SIDE].a = m[12] - m[0];
		p[RIGHT_SIDE].b = m[13] - m[1];
		p[RIGHT_SIDE].c = m[14] - m[2];
		p[RIGHT_SIDE].d = m[15] - m[3];

		p[BOTTOM_SIDE].a = m[12] + m[4];
		p[BOTTOM_SIDE].b = m[13] + m[5];
		p[BOTTOM_SIDE].c = m[14] + m[6];
		p[BOTTOM_SIDE].d = m[15] + m[7];

		p[TOP_SIDE].a = m[12] - m[4];
		p[TOP_SIDE].b = m[13] - m[5];
		p[TOP_SIDE].c = m[14] - m[6];
		p[TOP_SIDE].d = m[15] - m[7];

		p[NEAR_SIDE].a = m[12] + m[8];
		p[NEAR_SIDE].b = m[14] + m[9];
		p[NEAR_SIDE].c = m[14] + m[10];
		p[NEAR_SIDE].d = m[15] + m[11];

		p[FAR_SIDE].a = m[12] - m[8];
		p[FAR_SIDE].b = m[13] - m[9];
		p[FAR_SIDE].c = m[14] - m[10];
		p[FAR_SIDE].d = m[15] - m[11];

		// row major direct-x
	#if 0
		p[LEFT_SIDE].a = m[3] + m[0];
		p[LEFT_SIDE].b = m[7] + m[4];
		p[LEFT_SIDE].c = m[11] + m[8];
		p[LEFT_SIDE].d = m[15] + m[12];

		p[RIGHT_SIDE].a = m[3] - m[0];
		p[RIGHT_SIDE].b = m[7] - m[4];
		p[RIGHT_SIDE].c = m[11] - m[8];
		p[RIGHT_SIDE].d = m[15] - m[12];

		p[BOTTOM_SIDE].a = m[3] + m[1];
		p[BOTTOM_SIDE].b = m[7] + m[5];
		p[BOTTOM_SIDE].c = m[11] + m[9];
		p[BOTTOM_SIDE].d = m[15] + m[13];

		p[TOP_SIDE].a = m[3] - m[1];
		p[TOP_SIDE].b = m[7] - m[5];
		p[TOP_SIDE].c = m[11] - m[9];
		p[TOP_SIDE].d = m[15] - m[13];

		p[NEAR_SIDE].a = m[2];
		p[NEAR_SIDE].b = m[6];
		p[NEAR_SIDE].c = m[10];
		p[NEAR_SIDE].d = m[14];

		p[FAR_SIDE].a = m[3] - m[2];
		p[FAR_SIDE].b = m[7] - m[6];
		p[FAR_SIDE].c = m[11] - m[10];
		p[FAR_SIDE].d = m[15] - m[14];
	#endif
		/*
		p[LEFT_SIDE].a = m[3] + m[0];
		p[LEFT_SIDE].b = m[7] + m[4];
		p[LEFT_SIDE].c = m[11] + m[8];
		p[LEFT_SIDE].d = m[15] + m[12];

		p[RIGHT_SIDE].a = m[3] - m[0];
		p[RIGHT_SIDE].b = m[7] - m[4];
		p[RIGHT_SIDE].c = m[11] - m[8];
		p[RIGHT_SIDE].d = m[15] - m[12];

		p[BOTTOM_SIDE].a = m[3] + m[1];
		p[BOTTOM_SIDE].b = m[7] + m[5];
		p[BOTTOM_SIDE].c = m[11] + m[9];
		p[BOTTOM_SIDE].d = m[15] + m[13];

		p[TOP_SIDE].a = m[3] - m[1];
		p[TOP_SIDE].b = m[7] - m[5];
		p[TOP_SIDE].c = m[11] - m[9];
		p[TOP_SIDE].d = m[15] - m[13];

		p[NEAR_SIDE].a = m[3] + m[2];
		p[NEAR_SIDE].b = m[7] + m[6];
		p[NEAR_SIDE].c = m[11] + m[10];
		p[NEAR_SIDE].d = m[15] + m[14];

		p[FAR_SIDE].a = m[3] - m[2];
		p[FAR_SIDE].b = m[7] - m[6];
		p[FAR_SIDE].c = m[11] - m[10];
		p[FAR_SIDE].d = m[15] - m[14];

	#if 0
		// Directx per gribb & Hartmann, 2001
		p[LEFT_SIDE].a = m[12] + m[0];
		p[LEFT_SIDE].b = m[13] + m[1];
		p[LEFT_SIDE].c = m[14] + m[2];
		p[LEFT_SIDE].d = m[15] + m[3];

		p[RIGHT_SIDE].a = m[12] - m[0];
		p[RIGHT_SIDE].b = m[13] - m[1];
		p[RIGHT_SIDE].c = m[14] - m[2];
		p[RIGHT_SIDE].d = m[15] - m[3];

		p[BOTTOM_SIDE].a = m[12] + m[4];
		p[BOTTOM_SIDE].b = m[13] + m[5];
		p[BOTTOM_SIDE].c = m[14] + m[6];
		p[BOTTOM_SIDE].d = m[15] + m[7];

		p[TOP_SIDE].a = m[12] - m[4];
		p[TOP_SIDE].b = m[13] - m[5];
		p[TOP_SIDE].c = m[14] - m[6];
		p[TOP_SIDE].d = m[15] - m[7];

		p[NEAR_SIDE].a = m[8];
		p[NEAR_SIDE].b = m[9];
		p[NEAR_SIDE].c = m[10];
		p[NEAR_SIDE].d = m[11];

		p[FAR_SIDE].a = m[12] - m[8];
		p[FAR_SIDE].b = m[13] - m[8];
		p[FAR_SIDE].c = m[14] - m[10];
		p[FAR_SIDE].d = m[15] - m[11];
	#endif
	*/
		p[LEFT_SIDE].normalize();
		p[RIGHT_SIDE].normalize();
		p[BOTTOM_SIDE].normalize();
		p[TOP_SIDE].normalize();
		p[NEAR_SIDE].normalize();
		p[FAR_SIDE].normalize();
	}

	int Frustum::is_sphere_inside(const vec3& cp, const real rad) const
	{
		real dist(static_cast<real>(0.0));
		real nrad(-rad);
		for (int i = 0; i < 6; ++i)
		{
			dist = p[i].distance(cp);
			if (dist < nrad) return OUTSIDE;
			if (static_cast<real>(abs(dist)) < rad) return INTERSECTS;
		}
		return INSIDE;
	}

	int Frustum::is_point_inside(const vec3& pt) const
	{
		int result = INSIDE;

		for (int i = 0; i < 6; i++)
		{
			if (p[i].distance(pt) < 0)
				return OUTSIDE;
		}
		return(result);
	}

	int Frustum::is_triangle_inside(const vec3*& v)
	{
		int result = OUTSIDE;
		int test = INSIDE; 
		if (INSIDE == is_point_inside(v[0])) return test;
		if (INSIDE == is_point_inside(v[1])) return test;
		if (INSIDE == is_point_inside(v[2])) return test;
		return result;
	}

	int Frustum::is_triangle_inside(const vec3& p1, const vec3& p2, const vec3& p3)
	{
		int result = OUTSIDE;
		int test = INSIDE;
		if (INSIDE == is_point_inside(p1)) return test;
		if (INSIDE == is_point_inside(p2)) return test;
		if (INSIDE == is_point_inside(p3)) return test;
		return result;
	}

	int Frustum::is_quad_inside(const vec3* pt) const
	{
		int ptsin(0);
		for (int i = 0; i < 4; i++)
		{
			int out = 0;
			for (int j = 0; j < 6; j++)
			{
				if (p[j].distance(pt[i]) < 0)
					out++;
			}
			if (!out) ptsin++;
		}
		if (!ptsin) return OUTSIDE;
		if (ptsin == 4) return INSIDE;
		return INTERSECTS;
	}

	int Frustum::is_AABB_inside(const vec3& mn, const vec3& mx)  const
	{
		//
		// ref: Dion Picco
		// Frustum Culling - flipcode.com
		//

		// first, bounding sphere test
		vec3 cp((mx - mn) * 0.5f);
		cp += mn;
		float rad(mx.distance(cp));
		if (is_sphere_inside(cp, rad) == OUTSIDE) return OUTSIDE;

		// refine by checking AaBox
		vec3 pt[] = {
			mn,	//bottom front left
			vec3(mx.x, mn.y, mn.z),	//bottom front right
			vec3(mx.x, mn.y, mx.z),	//bottom rear right
			vec3(mn.x, mn.y, mx.z),	//bottom rear left
			vec3(mx.x, mx.y, mn.z),	//top front right
			vec3(mn.x, mx.y, mx.z),	//top front left
			vec3(mn.x, mx.y, mx.z),	//top rear left
			mx	//top rear right
		};

		int totalin(0);
		int incnt(0);
		int ptin(0);
		int i(0);
		for (int j = 0; j < 6; ++j)
		{
			incnt = 8;
			ptin = 1;
			for (i = 0; i < 8; ++i)
			{
				if (p[j].distance(pt[i]) < 0)
				{
					ptin = 0;
					--incnt;
				}
			}
			if (incnt == 0) return OUTSIDE;
			totalin += ptin;
		}
		if (totalin == 6) return INSIDE;
		return INTERSECTS;
	}


} // namespace sge
