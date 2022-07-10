#include "utilities/string_utils.h"
#include <stringapiset.h>

//=============================================================================
// NOTE: In general, Jackal treats all strings as UTF-8 and so will convert
//       strings to wide-char format and back again when calling Windows
//       API functions. However this code-base has no code-page or locale
//       management and has never been tested using any locale other than
//       the Microsoft default for US character sets.
// 
//       Future consideration for locale management and extensive testing
//       needs to be done.
//=============================================================================


const String DELIMCSV = " ,|:"; // list of CVS delimeters
const String DELIMDIR = "\\/:"; // list of path delimeters
const String DELIMSPC = " \t\b"; // list of white-space delimiters

//-------------------------------------------------------------
// The followinf string conversions between UTF8 & UTF16
// are Win32 specific implementations. Despite inherent issues
// with potential buffer overflow and criticism in the
// C++ community these conversions are optimized well enough.
//-------------------------------------------------------------
std::wstring toUTF16(const std::string& src) {
	int size = MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, NULL, 0);
	std::wstring dst;
	//------------------------------------------------------------
	// These Microsoft conversions will add a 0-terminator on the
	// end of the result. std::wstrings do not need it so we
	// decrement the 'size' value truncate the string properly.
	dst.resize(size - 1U);
	if (size > 0)
		MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, &dst[0], size);
	return dst;
}

std::string toUTF8(const std::wstring& src) {
	//---------------------------------------------------------
	// These Microsoft conversion functions produce zero
	// terminated strings.
	int size = WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, NULL, 0, NULL, NULL);
	std::string dst;
	//------------------------------------------------------------
	// These Microsoft conversions will add a 0-terminator on the
	// end of the result. std::strings do not need it so we
	// decrement the 'size' value truncate the string properly.
	dst.resize(size - 1U);
	if (size > 0)
		WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, &dst[0], size, NULL, NULL);
	return dst;
}

std::wstring toUTF16(const char* src, size_t n)
{
	String s = "";
	for (auto i = 0; i < n; ++i)
	{
		if (src[i] == '\0')
			s += '\1';
		else
			s += src[i];
	}
	WString result = toUTF16(s);
	for (auto i = 0; i < n; ++i)
	{
		if (result[i] == L'\1')
			result[i] = L'\0';
	}
	return result;
}

//-------------------------------------------------------------

//-------------------------------------------------------------
// The following case conversions are not tested in other
// locale contexts other than "en_US".
std::string  toLower(const std::string& src)
{
	//--------------------------------------------
	// TODO: set the locale for application, not
	// just these local functions.
	//std::setlocale(LC_CTYPE, "en_US.UTF-8");
	std::wstring wstr = toUTF16(src);
	for (std::wstring::iterator it = wstr.begin(); it != wstr.end(); ++it)
		*it = std::tolower(*it);
	return toUTF8(wstr);
}

std::wstring toLower(const std::wstring& src)
{
	// Probably does not work for UTF16 4-byte code units but
	// should be okay for all code-points within the BMP?
	WString dst = src;
	std::transform(dst.begin(), dst.end(), dst.begin(), ::tolower);
	return dst;
}

std::string  toUpper(const std::string& src)
{
	std::wstring wstr = toUTF16(src);
	for (std::wstring::iterator it = wstr.begin(); it != wstr.end(); ++it)
		*it = std::toupper(*it);
	return toUTF8(wstr);
}

std::wstring toUpper(const std::wstring& src)
{
	// Probably does not work for UTF16 4-byte code units but
	// should be okay for all code-points within the BMP?
	WString dst = src;
	std::transform(dst.begin(), dst.end(), dst.begin(), ::toupper);
	return dst;
}

std::string Left(const std::string& src, size_t count)
{
	return src.substr(0, count);
}

std::string Right(const std::string& src, size_t count)
{
	size_t n = src.length() - count;
	if (n < 0) n = 0;
	return src.substr(n, count);
}

std::string Mid(const std::string& src, size_t start, size_t count)
{
	if (start > src.length()) return "";
	return src.substr(start, count);
}

std::string LTrim(const std::string& src)
{
	size_t p(src.find_first_not_of(" \t"));
	if (p == std::string::npos) p = 0;
	return src.substr(p);
}

std::string RTrim(const std::string& src)
{
	if (src.empty()) return "";
	size_t len = src.length();
	size_t p = len - 1;
	while ((src[p] == ' ') || (src[p] == '\t'))
	{
		p--;
		len--;
		if (p == 0) break;
	}
	return src.substr(0, len);
}

std::string Trim(const std::string& src)
{
	return RTrim(LTrim(src));
}


u32 Tokenize(const String& src, std::vector<String>& tokens, const String& delimiters)
{
	size_t len = src.length();
	if (!len)
		return 0;
	size_t ptr(0);
	size_t end(0);

	while (ptr < len && end != src.npos) {
		ptr = src.find_first_not_of(delimiters, ptr);
		end = src.find_first_of(delimiters, ptr + 1);
		if (end == std::string::npos) {
			tokens.push_back(src.substr(ptr));
			return (u32)tokens.size();
		}
		tokens.push_back(src.substr(ptr, (end - ptr)));
		ptr = end + 1;
	}

	return (u32)tokens.size();
}

u32 Tokenize(const String& src, std::vector<real>& tokens, const String& delimiters)
{
	size_t len = src.length();
	if (!len)
		return 0;
	size_t ptr(0);
	size_t end(0);

	while (ptr < len && end != src.npos) {
		ptr = src.find_first_not_of(delimiters, ptr);
		end = src.find_first_of(delimiters, ptr + 1);
		if (end == std::string::npos) {
			tokens.push_back((real)toDouble(src.substr(ptr)));
			return (u32)tokens.size();
		}
		tokens.push_back((real)toDouble(src.substr(ptr, (end - ptr))));
		ptr = end + 1;
	}

	return (u32)tokens.size();

}

u32 Tokenize(const String& src, std::vector<int>& tokens, const String& delimiters)
{
	size_t len = src.length();
	if (!len)
		return 0;
	size_t ptr(0);
	size_t end(0);

	while (ptr < len && end != src.npos) {
		ptr = src.find_first_not_of(delimiters, ptr);
		end = src.find_first_of(delimiters, ptr + 1);
		if (end == std::string::npos) {
			tokens.push_back(toInt(src.substr(ptr)));
			return (u32)tokens.size();
		}
		tokens.push_back(toInt(src.substr(ptr, (end - ptr))));
		ptr = end + 1;
	}

	return (u32)tokens.size();
}

u32 Tokenize(const String& src, std::vector<u32>& tokens, const String& delimiters)
{
	size_t len = src.length();
	if (!len)
		return 0;
	size_t ptr(0);
	size_t end(0);

	while (ptr < len && end != src.npos) {
		ptr = src.find_first_not_of(delimiters, ptr);
		end = src.find_first_of(delimiters, ptr + 1);
		if (end == std::string::npos) {
			tokens.push_back(toUint(src.substr(ptr)));
			return (u32)tokens.size();
		}
		tokens.push_back(toUint(src.substr(ptr, (end - ptr))));
		ptr = end + 1;
	}

	return (u32)tokens.size();
}


u32 Tokenize(const String& str, String list[], int size)
{
	if (!str.length() || size < 1)
		return 0;
	size_t head = 0;
	size_t tail = 0;
	size_t ndx(0);
	const std::string delim = " ,|:";
	while (head < str.length() && ndx < size) {
		tail = str.find_first_of(delim, head);
		if (tail == String::npos) {
			tail = str.length();
		}
		if (head != tail) {
			list[ndx++] = str.substr(head, tail - head);
		}
		head = tail + 1;
	}
	return (u32)ndx;
}

u32 Tokenize(const String& str, real vals[], int size)
{
	String* tokens = new String[size];
	int c = Tokenize(str, tokens, size);
	for (int i = 0; i < c; i++)
		vals[i] = (real)toDouble(tokens[i]);
	delete[] tokens;
	return c;
}

u32 Tokenize(const String& str, int vals[], int size)
{
	String* tokens = new String[size];
	int c = Tokenize(str, tokens, size);
	for (int i = 0; i < c; c++)
		vals[i] = toInt(tokens[i]);
	delete[] tokens;
	return c;
}

u32 Tokenize(const String& str, u32 vals[], int size)
{
	String* tokens = new String[size];
	int c = Tokenize(str, tokens, size);
	for (int i = 0; i < c; c++)
		vals[i] = toUint(tokens[i]);
	delete[] tokens;
	return c;
}


int toInt(const String& str)
{
	return (int)std::strtol(str.c_str(), 0, 10);
}

u32 toUint(const String& str)
{
	return std::strtoul(str.c_str(), 0, 0);
}

bool   toBool(const String& str)
{
	if (str == "true" || str == "TRUE" || str == "1")
		return true;
	else
		return false;
}

float  toFloat(const String& str)
{
	return std::strtof(str.c_str(), nullptr);
}

double toDouble(const String& str)
{
	return std::strtod(str.c_str(), nullptr);
}


bool toInt(const String& str, int* v)
{
	int chk(0);
	try {
		chk = (int)std::strtol(str.c_str(), 0, 0);
	}
	catch (std::exception& e)
	{
		e = e; // avoid C4101 warning - inreferenced local variable
		return false;
	}
	*v = chk;
	return true;
}

bool toUint(const String& str, u32* v)
{
	u32 chk(0);
	try {
		chk = (u32)std::strtoul(str.c_str(), 0, 0);
	}
	catch (std::exception& e)
	{
		e = e; // avoid C4101 warning - inreferenced local variable
		return false;
	}
	*v = chk;
	return true;
}

bool toBool(const String& str, bool* v)
{
	if (!IsBool(str))
		return false;
	if (str == "true" || str == "TRUE" || str == "1")
		*v = true;
	else
		*v = false;
	return true;
}

bool toFloat(const String& str, float* v)
{
	float chk(0.0f);
	try {
		chk = (float)std::strtod(str.c_str(), 0);
	}
	catch (std::exception& e)
	{
		e = e; // avoid C4101 warning - inreferenced local variable
		return false;
	}
	*v = chk;
	return true;
}

bool toDouble(const String& str, double* v)
{
	double chk(0.0f);
	try {
		chk = std::strtod(str.c_str(), 0);
	}
	catch (std::exception& e)
	{
		e = e; // avoid C4101 warning - inreferenced local variable
		return false;
	}
	*v = chk;
	return true;
}


bool IsReal(const String& str)
{
	char* eptr(0);
	real v = (real)strtod(str.c_str(), &eptr);
	return !(*eptr != '\0' || eptr == str.c_str());
}

bool IsInt(const String& str)
{
	char* eptr(0);
	int v = strtol(str.c_str(), &eptr, 10);
	if ((eptr - str.c_str()) == str.length())
		return true;
	return !(*eptr != '\0' || eptr == str.c_str());
}

bool IsUint(const String& str)
{
	char* eptr(0);
	String chk = RTrim(str);
	if (!chk.empty())
		if (chk[0] == '-')
			return false;
	u32 v = strtoul(str.c_str(), &eptr, 0);
	if ((eptr - str.c_str()) == str.length())
		return true;
	return !(*eptr != '\0' || eptr == str.c_str());
}

bool IsBool(const String& str)
{
	String chk(toLower(str));
	if (chk == "true" || chk == "false" ||
		chk == "yes" || chk == "no" ||
		chk == "1" || chk == "0")
		return true;
	else
		return false;
}

std::string toHexString(u64 v, int places, bool upcase)
{
	std::stringstream ss;
	ss << std::setw(places) << std::setfill('0');
	if (upcase)
		ss << std::uppercase;
	ss << std::hex << v << std::endl;
	return ss.str();

}

std::string toHexString(u32 v, int places, bool upcase)
{
	return toHexString((u64)v, places, upcase);
}

std::string toHexString(int v, int places, bool upcase)
{
	return toHexString(u64(v), places, upcase);
}

String StringFormat(const char* pszFormat, ...)
{
	String sRet;

	// Check format string
	if (pszFormat && pszFormat[0] != '\0') {
		// Ensure that the locale is set to the C default
		// When this instance gets destroyed the locale is restored automatically
		// Not possible to forget the restore anymore ;)
		CLocaleChanger cLocale;

		// Get the required buffer length, does not include the terminating zero character
		static String sRet("");
		va_list arg_list;

		va_start(arg_list, pszFormat);
		const size_t nchars = std::vsnprintf(nullptr, 0, pszFormat, arg_list);
		va_end(arg_list);

		char* buffer = new char[(size_t)nchars + 1];
		va_start(arg_list, pszFormat);
		std::vsnprintf(buffer, (size_t)nchars + 1, pszFormat, arg_list);
		sRet = buffer;
		va_end(arg_list);

		delete[] buffer;
	}
	return sRet;
}

String StreamToString(const std::ostream& os)
{
	std::ostringstream ss;
	ss << os.rdbuf();
	return ss.str();
}
