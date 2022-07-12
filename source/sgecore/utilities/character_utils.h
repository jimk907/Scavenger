#pragma once
#include "sge_defines.h"


namespace sge
{
	// ASCII char functions for parsers
	std::string get_line(char* p, bool trim);
	char*       skip_white_space(char* p);
	char*       find_next_line(char* p);
	char*       find_token(char* p, char token);
	bool        is_alpha(char* p);
	bool        is_alphanumeric(char* p);

	// ASCII strings parsers 

	// Parse out a string starting at char* p, until the first
	// instance of char 'token' is found or until the end of the
	// string. Return with *p one char beyond the token or end.
	std::string get_until_token(char* p, char token);
	// Parse out a string starting at char* p, until the first
	// instance of char in the string 'set' is found or until the
	// end of the string. Return with *p one char beyond the 
	// token or end.
	std::string get_until_set(char* p, const char* set);
	// Parse out a string starting at char* p, until the first
	// instance of char '"' is found or until the end of the
	// string. Return with *p one char beyond the '"' or end.
	std::string get_quoted_text(char* p);

} // namespace sge

