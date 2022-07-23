#pragma once
#include "sge_defines.h"
#include "utilities/string_utils.h"


namespace sge
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
			Dispatch(msg.to_string());
		}
		static void Dispatch(const std::string& msg)
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
		static void Dispatch(const std::string& msg)
		{
			m_LogBuffer.push_back(msg);
		}

	private:
		static std::vector<std::string> m_LogBuffer;

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
			std::wstring mg = msg.to_wstring();
			MessageBoxW(GetDesktopWindow(), mg.c_str(), L"SgeLog Message", MB_OK);
		}
		static void Dispatch(const std::string& msg)
		{
			std::wstring mg = toUTF16(msg);
			MessageBoxW(GetDesktopWindow(), mg.c_str(), L"SgeLog Message", MB_OK);
		}
	};

#endif



} // namespace sge
