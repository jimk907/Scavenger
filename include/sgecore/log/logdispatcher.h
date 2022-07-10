#pragma once
#include "../sge_defines.h"


namespace sgecore
{

	//------------------------------------------------------------
	//  This dispatcher writes to the std::cout which may be
	//  rerouted to a file (in future).
	// The message is converted to UTF16 to accomodate unicode.
	//------------------------------------------------------------
	class DefaultDispatcher
	{
	protected:
		static void Dispatch(const String& msg)
		{
			std::wcout << toUTF16(msg) << std::endl;
		}
	};

	//------------------------------------------------------------
	//  This dispatcher saves the log messages in a buffer which
	//  maybe periodically flushed to a file or display.
	//------------------------------------------------------------
	class BufferedDispatcher
	{
	protected:
		static void Dispatch(const String& msg)
		{
			m_LogBuffer.push_back(msg);
		}

	private:
		std::vector<String> m_LogBuffer;

	};

#ifdef _WIN32

	//------------------------------------------------------------
	//  For Win32 only, this dispatcher displays the message to a 
	//  standard windows message box.
	//  The message is converted to UTF16 to accomodate unicode.
	//------------------------------------------------------------
	class MessageBoxDispatcher
	{
	protected:
		static void Dispatch(const String& msg)
		{
			MessageBoxW(GetDesktopWindow(), toUTF16(msg).c_str(), L"SgeLog Message", MB_OK);
		}
	};

#endif



} // namespace sgecore
