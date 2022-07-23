#pragma once
#include "sge_defines.h"
#include "vec3.h"


namespace sge
{



	class Plane
	{
	public:

		const static int JGE_BEHIND_PLANE = -1;   // Object is behind the plane
		const static int JGE_COPLANAR = 0;        // Object is on the plane
		const static int JGE_INFRONT_PLANE = 1;   // Obect is in front of the plane

	public:
		Plane();
		Plane(const real a, const real b, const real c, const real d);
		Plane(const Plane &other);
		Plane(const vec3 &p1, const vec3 &p2, const vec3 &p3);
		Plane(const vec3 &normal, real dist);
		~Plane() {}


		void set(const real a, const real b, const real c, const real d);
		void set(const Plane &other);
		void set(const vec3 &p1, const vec3 &p2, const vec3 &p3);
		void set(const vec3 &normal, real dist);
		void reset();

		void normalize();

		real distance(const vec3 &pt) const;

		bool is_behind(const vec3 &pt) const;


		inline vec3 normal() const {
			return vec3(a, b, c);
		}

		inline real distance() const { return dist; }

		union {
			struct {
				real norm[3];
				real dist;	
			};
			struct {
				real a;			// equivalent to normal[0]
				real b;			// equivalent to normal[1]
				real c;			// equivalent to normal[2]
				real d;			// equivalent ot distance
			};
		};


		friend inline std::ostream& operator << (std::ostream& output, const Plane& p)
		{
			char buffer[64];
			snprintf(buffer, 64, "[(%7.4f, %7.4f, %7.4f) %7.4f]", p.a, p.b, p.c, p.d);
			output << buffer << std::endl;
			return output;
		}
	};


} // namespace sge

