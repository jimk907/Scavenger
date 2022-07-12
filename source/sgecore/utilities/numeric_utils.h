#pragma once
#include "sge_defines.h"


namespace sge
{

	struct U64LittleEndian
	{
		union
		{
			u64 U64;
			u32 U32[2];
			u16 U16[4];
			u8  U8[8];
		};

		U64LittleEndian() :U64(0) {}
	};

	u64  toU64(u32 low, u32 hi);
	u32  toU32LowPart(u64 v);
	u32  toU32HighPart(u64 v);

} // namespace sge
