#pragma once
#include "sge_defines.h"
#include "logformat.h"
#include "logdispatcher.h"


namespace sgecore
{

	enum class SgeLogLevel : u8
	{
		NONE,
		TRACE,
		INFO,
		WARN,
		ERROR,
		FATAL,

	};


	template<typename Formatter = DefaultFormat, typename Dispatcher = DefaultDispatcher>
	class Logger : private Formatter, private Dispatcher
	{
	public:
		static void Log(const WString& msg, SgeLogLevel type)
		{
			Log(toUTF8(msg).c_str(), type);
		}

		static void Log(const std::string& msg, SgeLogLevel type)
		{
			Log(msg.c_str(), type);
		}

		static void Log(const char* msg, SgeLogLevel type)
		{
			Dispatcher::Dispatch(Formatter::Format(msg, LogTypeToString(type)));
		}

		static int Log(SgeLogLevel type, const char* format, ...)
		{
			va_list arg_list;
			va_start(arg_list, format);

			const auto nchars = Log(type, format, arg_list);
			va_end(arg_list);
			return nchars;
		}

		static int Log(SgeLogLevel type, const char* format, va_list args)
		{
			const size_t nchars = std::vsnprintf(nullptr, 0, format, args);
			//va_end(arg_list);

			//if (nchars > 0)
			{
				std::vector<char> buffer(nchars + 1U);
				std::vsnprintf(buffer.data(), buffer.size(), format, args);
				//String msg({ buffer.begin(), buffer.end() });
				String msg(buffer.data());
				Log(msg.c_str(), type);
			}

			//va_end(arg_list_cpy);
			return (int)nchars;
		}

		static std::string LogTypeToString(SgeLogLevel type)
		{
			switch (type)
			{
				case SgeLogLevel::TRACE:
					return std::string("DEBUG: ");
				case SgeLogLevel::INFO:
					return std::string(" INFO: ");
				case SgeLogLevel::WARN:
					return std::string(" WARN: ");
				case SgeLogLevel::ERROR:
					return std::string("ERROR: ");
				default:
					return std::string();
			}
		}
	};


}