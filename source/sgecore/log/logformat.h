#pragma once
#include "sge_defines.h"
#include "string/string.h"
#include <chrono>



namespace sge
{

#define LOG_TIMESTR_SIZE 64

	template <typename Impl>
	class BaseFormat
	{
	protected:
		static String Format(const std::string& msg, const std::string typestr)
		{
			return Impl::Format(msg, typestr);
		}

		static std::string GetTimeDateString()
		{
			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			time_t nowtime = std::chrono::system_clock::to_time_t(now);
			char timestr[LOG_TIMESTR_SIZE];
			ctime_s(timestr, LOG_TIMESTR_SIZE, &nowtime);
			std::string ret(timestr);
			return std::string(std::string(std::begin(ret), std::end(ret) - 1));
		}
	};

	class DefaultFormat : public BaseFormat<DefaultFormat>
	{
	protected:
		static String Format(const std::string& msg, const std::string typestr)
		{
			std::string ret("");
			if (!typestr.empty())
				ret = typestr;
			ret += msg;
			return ret;
		}
	};

	class DatestampFormat : public BaseFormat<DatestampFormat>
	{
	protected:
		static String Format(const std::string& msg, const std::string typestr)
		{
			return String(GetTimeDateString() + typestr + msg);
		}
	};

	class AttnFormat : public BaseFormat<AttnFormat>
	{
	protected:
		static std::string Format(const std::string& msg, const std::string& typestr)
		{
			if (typestr == "ERROR: ") {
				return std::string("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n" + \
							                  typestr + " " + GetTimeDateString() + "\n" + msg + "\n" + \
							         "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			}
			return std::string(typestr + msg);
		}
	};


} // nmaespace sge

