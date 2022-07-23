#pragma once

#include "sge_defines.h"
#include "math/plane.h"


namespace sge
{
	
	class vec3;
	class mat4;


	// Implements a frustum class.
	class Frustum
	{
	public:

		// Enum identifiers of the six frustum planes
		enum JGE_PLANES : unsigned int {
			LEFT_SIDE   = 0,
			RIGHT_SIDE  = 1,
			BOTTOM_SIDE = 2,
			TOP_SIDE    = 3,
			NEAR_SIDE   = 4,
			FAR_SIDE    = 5
		};


		// Enum for intersection tests.
		enum INTERSECTIONS : unsigned int {
			OUTSIDE    = 0,        //< The object is outside of the frustum
			INSIDE     = 1,        //< The eobject is fully inside the frustum
			INTERSECTS = 2,        //< The object is partially inside the frustum
		};


		// Default constructor
		Frustum();

		// Construct from a matrix
		Frustum(const mat4 &mat);

		// Default destructor
		~Frustum() {}

		// Returns the frustum::INTERSECTION value for a point.
		int  is_point_inside(const vec3 &pt) const;

		// Returns the frustum::INTERSECTION value for a triangle.
		int is_triangle_inside(const vec3*& v);
		int is_triangle_inside(const vec3& p1, const vec3& p2, const vec3& p3);

		//   Returns the frustum::INTERSECTION value for a sphere.
		//                          the radius of the sphere.
		int  is_sphere_inside(const vec3 &center, const real radius) const;

		// Returns the frustum::INTERSECTION value for the AABB.
		int  is_AABB_inside(const vec3 &min, const vec3 &max) const;

		// Returns the frustum::INTERSECTION value for the quad.
		int  is_quad_inside(const vec3 *pts) const;

		// Bulds a frustum from a matrix (mat4)
		void from_matrix(const mat4 &mat);

		// Buids a frustum from a view matrix and a projection matrix (each mat4).
		void from_matrix(const mat4& v, const mat4 &p);


		// Returns copy of the specified plane.
		inline Plane get_plane(JGE_PLANES side) { return p[side]; }


	private:
		Plane p[6];                //< Array of frustum planes
	};




} // namespace sge

