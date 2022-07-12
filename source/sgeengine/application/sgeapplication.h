#pragma once
#include "sge_settings.h"



namespace sge
{

	class SgeApplication
	{
	public:
		SgeApplication();
		virtual ~SgeApplication();

		bool Initialize();
		i64  Run();
		void Shutdown();

	};

} // namespace sge

