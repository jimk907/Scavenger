#pragma once
#include "sge_defines.h"
#include <locale>
#include <iomanip>
#include <sstream>



extern const String DELIMCSV; // list of CVS delimeters
extern const String DELIMDIR; // list of path delimeters
extern const String DELIMSPC; // list of white-space delimiters


std::string  toUTF8(const std::wstring& src);
std::wstring toUTF16(const std::string& src);	

std::wstring toUTF16(const char* src, size_t n);

std::string  toLower(const std::string& src);
std::wstring toLower(const std::wstring& src);
std::string  toUpper(const std::string& src);
std::wstring toUpper(const std::wstring& src);

std::string Left(const std::string& src, size_t count);
std::string Right(const std::string& src, size_t count);
std::string Mid(const std::string& src, size_t start, size_t count);
std::string LTrim(const std::string& src);
std::string RTrim(const std::string& src);
std::string Trim(const std::string& src);


u32 Tokenize(const String& src, std::vector<String>& tokens, const String& delimiters = DELIMCSV);
u32 Tokenize(const String& str, std::vector<real>& vals, const String& delimiters = DELIMCSV);
u32 Tokenize(const String& str, std::vector<int>& vals, const String& delimiters = DELIMCSV);
u32 Tokenize(const String& str, std::vector<u32>& vals, const String& delimiters = DELIMCSV);
u32 Tokenize(const String& str, String list[], int size);
u32 Tokenize(const String& str, real vals[], int size);
u32 Tokenize(const String& str, int vals[], int size);
u32 Tokenize(const String& str, u32 vals[], int size);


int    toInt(const String& str);
u32    toUint(const String& str);
bool   toBool(const String& str);
float  toFloat(const String& str);
double toDouble(const String& str);

bool toInt(const String& str, int* v);
bool toUint(const String& str, u32* v);
bool toBool(const String& str, bool* v);
bool toFloat(const String& str, float* v);
bool toDouble(const String& str, double* v);

bool IsReal(const String& str);
bool IsInt(const String& str);
bool IsUint(const String& str);
bool IsBool(const String& str);


// Convert a value to a hex string:
//    v      = value to be converted
//    places = desired width of string, 0 = only the required length
//    upcase = return uppercase hex value.
std::string toHexString(u32 v, int places = 0, bool upcase = false);
std::string toHexString(u64 v, int places = 0, bool upcase = false);
std::string toHexString(int v, int places = 0, bool upcase = false);

String StringFormat(const char* pszFormat, ...);

String StreamToString(const std::ostream& os);

//===============================================================================
//   Changes the current locale to 'C' locale temporaly. (RAII, Resource 
//   Acquisition Is Initialization)
//   When this instance gets destroyed the old locale setting is restored
//   => Not possible to forget the restore anymore ;)
//
class CLocaleChanger
{

public:
	CLocaleChanger() : m_pstrSavedLocale(nullptr)
	{
		// Get the currently set locale, if it's a null pointer or already "C" just do nothing
		const char* pszCurrentLocale = setlocale(LC_ALL, nullptr);
		if (pszCurrentLocale && pszCurrentLocale[0] != 'C') {
			// Do never ever pass a null pointer into "strdup" because the behavior isn't specified in POSIX (http://pubs.opengroup.org/onlinepubs/9699919799/functions/strdup.html)
			// -> On MS Windows and Linux a null pointer will be returned, on Android it just crashes...

			// Duplicate the string
			m_pstrSavedLocale = _strdup(pszCurrentLocale);

			// Set the locale back to the default
			setlocale(LC_ALL, "C");
		}
	}

	~CLocaleChanger()
	{
		if (m_pstrSavedLocale) {
			// Be polite and restore the previously set locale
			setlocale(LC_ALL, m_pstrSavedLocale);

			// ... and don't forget to free the memory of our locale backup...
			free(m_pstrSavedLocale);
		}
	}

private:
	CLocaleChanger(const CLocaleChanger& cSource) : m_pstrSavedLocale(nullptr)
	{
		// No implementation because the copy constructor is never used
	}

	CLocaleChanger& operator =(const CLocaleChanger& cSource)
	{
		// No implementation because the copy operator is never used
		return *this;
	}

	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
private:
	char* m_pstrSavedLocale;
};
