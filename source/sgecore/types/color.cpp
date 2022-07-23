#include "color.h"


namespace sge
{


		color4f::color4f()
			: r(0.0f), g(0.0f), b(0.0f), a(0.0f)
		{
		}

		color4f::color4f(f32 red, f32 green, f32 blue, f32 alpha)
			: r(red), g(green), b(blue), a(alpha)
		{
		}

		color4f::color4f(f32 red, f32 green, f32 blue)
			: r(red), g(green), b(blue), a(1.0f)
		{
		}

		color4f::color4f(f32 v)
			: r(v), g(v), b(v), a(1.0f)
		{
		}

		color4f& color4f::operator=(const color4f& rhs)
		{
			r = rhs.r; g = rhs.g; b = rhs.b; a = rhs.a;
			return *this;
		}

		color4f color4f::operator=(const color4f& rhs) const
		{
			return color4f(r, g, b, a);
		}

		void color4f::alpha(f32 v)
		{
			a = v;
		}

} // namespace sge
