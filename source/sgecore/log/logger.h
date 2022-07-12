#pragma once
#include "sge_defines.h"
#include "logformat.h"
#include "logdispatcher.h"
#include "utilities/string_utils.h"



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


} // namespace sgecore

namespace LOGGER
{

	using namespace sgecore;

	inline void LOG_INF(const String& msg) { Logger<>::Log(msg, SgeLogLevel::INFO); }
	inline void LOG_TRC(const String& msg) { Logger<>::Log(msg, SgeLogLevel::TRACE); }
	inline void LOG_WRN(const String& msg) { Logger<>::Log(msg, SgeLogLevel::WARN); }
	inline void LOG_ERR(const String& msg) { Logger<>::Log(msg, SgeLogLevel::ERROR); }
	inline void LOG(SgeLogLevel type, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		Logger<>::Log(type, format, args);
		va_end(args);
	}
	inline void ATTN_LOG(SgeLogLevel type, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		Logger<AttnFormat>::Log(type, format, args);
		va_end(args);
	}
	inline void LINE_LOG(u8 n)
	{
		for (u8 i = 0; i < n; i++)
			Logger<>::Log(SgeLogLevel::NONE, "");
	}
#if SGE_WIN32
	inline void MSG_LOG(SgeLogLevel type, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		Logger<AttnFormat, MessageBoxDispatcher>::Log(type, format, args);
		va_end(args);
	}
#endif


} // namespace LOGGER
