#include "character_utils.h"



namespace sge
{

	std::string get_line(char* p, bool trim)
	{
		std::string retval;

		while ((*p) && ((*p != '\n') && (*p != '\r'))) {
			retval += *p++;
		}
		p++;
		return retval;
	}

	char* skip_white_space(char* p)
	{
		while (*p != '\0' && (*p == ' ' || *p == '\t' || *p == '\a' || *p == '\n'))
			++p;
		return p;
	}

	char* find_next_line(char* p)
	{
		while (*p != '\0' && *p != '\r' && *p != '\n')
			++p;
		if (*p != '\0' && (*p == '\r' || *p == '\n')) 
			++p;
		return p;
	}

	char* find_token(char* p, char token)
	{
		while (*p && *p != token)
			++p;
		return p;
	}

	bool is_alpha(char* p)
	{
		return ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z'));
	}

	bool is_alphanumeric(char* p)
	{
		return (is_alpha(p) || (*p >= '0' && *p <= '9'));
	}

	std::string get_until_token(char* p, char token)
	{
		std::string result;
		while(*p && (*p != token))
			result += *(p++);
		p++;
		return result;
	}

	std::string get_until_set(char* p, const char* set)
	{
		std::string result;
		while (*p)
		{
			const char* q = set;
			while(*q)
				if (*p == *q++)
				{
					p++;
					return result;
				}
			result += *p++;
		}
		return result;
	}

	std::string get_quoted_text(char* p)
	{
		return get_until_token(p, '"');
	}


} // namespace sge
