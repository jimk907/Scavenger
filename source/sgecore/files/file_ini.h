#pragma once
#include "sge_defines.h"



namespace sge
{


	class VarKeySet;


	class IniFile
	{
	public:
		IniFile();
		~IniFile();
		u32 Read(VarKeySet* varset, const std::string& filespec);
		bool Parse(VarKeySet* varset, char* filedata, u32 size);
		bool Write(VarKeySet* varset, const std::string& filespec);

		std::string GetErrorStr() const { return error_str; }

	private:
		std::string error_str;
		size_t      file_size = 0;
		char* file_data = nullptr;


	private:
		//std::string get_line(char* p, bool trim = true);


		//char* skip_white_space(char* p);
		//char* find_next_line(char* p);
		//char* find_token(char* p, char token);
		//bool  is_alpha(char* p);
		//bool  is_alphanumeric(char* p);

	};



} // namespace sge

