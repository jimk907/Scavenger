#include "log/logger.h"
#include "utilities/gen_utils.h"


using namespace sgecore;
char HOLD_CHAR(' ');


int main(int arg, char** argv)
{
	Logger<>::Log("hello world", SgeLogLevel::INFO);
	Logger<DefaultFormat>::Log("DefaultFormat, empty dispatcher, SgeLogLevel::NONE.", SgeLogLevel::NONE);
	Logger<DatestampFormat>::Log("DatestampFormat, LOG_WARN", SgeLogLevel::WARN);
	Logger<AttnFormat>::Log("DatestampFormat, LOG_ERROR", SgeLogLevel::ERROR);
	Logger<DefaultFormat, MessageBoxDispatcher>::Log("Messagebox dispatcher!", SgeLogLevel::ERROR);
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "Messagebox closed...Test specific purpose loggers.");
	LOGGER::LOG_INF("Info message...");
	LOGGER::LOG_TRC("Debug message...");
	LOGGER::LOG_WRN("Warning message...");
	LOGGER::LOG_ERR("Error log...");
	LOGGER::LOG(SgeLogLevel::INFO, "Arg substitution: float> %f, integer> %i, unsigned> %u, char> %c", 3.1415f, -15, 0xff, 'Z');
	LOGGER::LOG(SgeLogLevel::INFO, "Logging three blank lines...");
	LOGGER::LINE_LOG(3);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Highlighted log info...");
	LOGGER::ATTN_LOG(SgeLogLevel::WARN, "Highlighted log warning...");
	LOGGER::ATTN_LOG(SgeLogLevel::ERROR, "Highlighted log ERROR: Temperature=%3.1f", 98.6f);
	LOGGER::MSG_LOG(SgeLogLevel::INFO, "Log test will now end.");
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "\n** Press '%c' to continue... **", HOLD_CHAR);
	WaitKey(HOLD_CHAR);
	return 0;
}
