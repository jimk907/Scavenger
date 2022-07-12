#pragma once
#include "sge_defines.h"
#include <chrono>



namespace sgecore
{

#define LOG_TIMESTR_SIZE 64

	template <typename Impl>
	class BaseFormat
	{
	protected:
		static String Format(const String& msg, const String typestr)
		{
			return Impl::Format(msg, typestr);
		}

		static String GetTimeDateString()
		{
			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			time_t nowtime = std::chrono::system_clock::to_time_t(now);
			char timestr[LOG_TIMESTR_SIZE];
			ctime_s(timestr, LOG_TIMESTR_SIZE, &nowtime);
			std::string ret(timestr);
			return String(std::string(std::begin(ret), std::end(ret) - 1));
		}
	};

	class DefaultFormat : public BaseFormat<DefaultFormat>
	{
	protected:
		static String Format(const String& msg, const String typestr)
		{
			String ret("");
			if (!typestr.empty())
				ret = typestr;
			ret += msg;
			return ret;
		}
	};

	class DatestampFormat : public BaseFormat<DatestampFormat>
	{
	protected:
		static String Format(const String& msg, const String typestr)
		{
			return String(GetTimeDateString() + typestr + msg);
		}
	};

	class AttnFormat : public BaseFormat<AttnFormat>
	{
	protected:
		static String Format(const String& msg, const String& typestr)
		{
			if (typestr == "ERROR: ") {
				return String("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n" + \
							  typestr + " " + GetTimeDateString() + "\n" + msg + "\n" + \
							  "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
			}
			return String(typestr + msg);
		}
	};


} // nmaespace sgecore

