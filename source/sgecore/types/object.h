#pragma once

#include "sge_defines.h"


namespace sge
{

	extern u32 SGE_OBJECT_ID;

	class Object
	{
	public:
		Object();
		~Object();

		inline u32 GetId() const { return object_id; }

	private:
		u32 object_id;
	};

} // nmaespace sge

