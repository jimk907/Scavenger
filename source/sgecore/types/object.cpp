#include "object.h"



namespace sge
{
	static u32 SGE_OBJECT_ID(0);

	Object::Object()
		: object_id(0)
	{
		object_id = ++SGE_OBJECT_ID;
	}

	Object::~Object()
	{
	}



} // namespace sge