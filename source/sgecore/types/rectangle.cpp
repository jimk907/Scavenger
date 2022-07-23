#include "rectangle.h"


namespace sge
{

	recti::~recti()
	{
	}

	recti::recti()
		: x0(0), y0(0)
		, x1(0), y1(0)
	{
	}

	recti::recti(i32 left, i32 top, i32 right, i32 bottom)
		: x0(left), y0(top)
		, x1(right), y1(bottom)
	{
	}

	recti::recti(const recti& rhs)
	{
		top_left     = rhs.top_left;
		bottom_right = rhs.bottom_right;
	}

	i32 recti::width() const
	{
		return x1 - x0;
	}

	i32 recti::height() const
	{
		return y1 - y0;
	}

	recti& recti::operator=(const recti& rhs)
	{
		x0 = rhs.x0; y0 = rhs.y0;
		x1 = rhs.x1; y1 = rhs.y1;
		return *this;
	}

	recti::recti(const RECT& rc)
		: x0(rc.left), y0(rc.top)
		, x1(rc.right), y1(rc.bottom)
	{
	}

	recti& recti::operator=(const RECT& rc)
	{
		x0 = rc.left;
		y0 = rc.top;
		x1 = rc.right;
		y1 = rc.bottom;
		return *this;
	}


} // namespace sge

