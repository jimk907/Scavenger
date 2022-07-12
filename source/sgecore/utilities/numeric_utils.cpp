#include "numeric_utils.h"



namespace sge
{

	u64  toU64(u32 low, u32 hi)
	{
		U64LittleEndian le;
		le.U32[0] = low;
		le.U32[1] = hi;
		return le.U64;
	}

	u32  toU32LowPart(u64 v)
	{
		U64LittleEndian le;
		le.U64 = v;
		return le.U32[0];
	}

	u32  toU32HighPart(u64 v)
	{
		U64LittleEndian le;
		le.U64 = v;
		return le.U32[1];
	}

} // namespace sge

