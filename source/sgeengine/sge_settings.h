#pragma once
#include "log/logger.h"


namespace sge
{

	struct ApplicationSettings
	{
		int argc;
		char** argv;

		ApplicationSettings()
			: argc(0), argv(nullptr)
		{}
	};


} // namespace sge


