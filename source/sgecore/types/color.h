#pragma once
#include "sge_defines.h"


namespace sge
{

	class color4f
	{
	public:
		union {
			struct {
				f32 r;
				f32 g;
				f32 b;
				f32 a;
			};
			f32 data[4];
		};

		color4f();
		color4f(f32 red, f32 green, f32 blue, f32 alpha);
		color4f(f32 red, f32 green, f32 blue);
		color4f(f32 v);
		
		color4f& operator=(const color4f& rhs);
		color4f  operator=(const color4f& rhs) const;
		void     alpha(f32 v);

		operator f32* () { return data; }

	};

} // namespace sge

