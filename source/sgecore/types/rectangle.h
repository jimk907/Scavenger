#pragma once
#include "sge_defines.h"
#include "math/vec2.h"


namespace sge
{


	class recti
	{
	public:
		union {
			struct {
				i32 x0;
				i32 y0;
				i32 x1;
				i32 y1;
			};
			struct {
				vec2i top_left;
				vec2i bottom_right;
			};
		};

		~recti();
		recti();
		recti(i32 left, i32 top, i32 right, i32 bottom);
		recti(const recti& rhs);
		i32 width() const;
		i32 height() const;

		recti& operator=(const recti& rhs);

		//******** WIN32 specific **********//
		recti(const RECT& rc);
		recti& operator=(const RECT& rc);

	};

} // namespace sge
