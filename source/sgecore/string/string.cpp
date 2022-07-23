#include "string.h"
#include "unicode.h"
#include <locale>
#include <codecvt>
#include <algorithm>

namespace sge
{

	///////////////////////////////////////////////////////////////////////////////
	// default constructor
	//
	String::String()
		: str_int()
	{
	}

	///////////////////////////////////////////////////////////////////////////////
	// destructor
	//
	String::~String()
	{
		str_int.clear();
	}

	///////////////////////////////////////////////////////////////////////////////
	// copy constructors
	//
	String::String(const char* s)
		: str_int(convert(s))
	{
	}

	String::String(const wchar_t* s)
		: str_int(convert(s))
	{
	}

	String::String(const std::string& s)
		: str_int(convert(s))
	{
	}

	String::String(const std::wstring& s)
		: str_int(convert(s))
	{
	}

	String::String(const std::u16string& s)
		: str_int(convert(s))
	{
	}

	String::String(const std::u32string& s)
		: str_int(s)
	{
	}

	String::String(const String& s)
		: str_int(s.str_int)
	{
	}

	String::String(const u8 v)
	{
		str_int = convert(std::to_string(v));
	}

	String::String(const u16 v)
	{
		str_int = convert(std::to_string(v));
	}

	String::String(const u32 v)
	{
		str_int = convert(std::to_string(v));
	}

	String::String(const u64 v)
	{
		str_int = convert(std::to_string(v));
	}

	String::String(const i8 v)
	{
		str_int = convert(std::to_string(v));
	}

	String::String(const i16 v)
	{
		str_int = convert(std::to_string(v));
	}

	String::String(const i32 v)
	{
		str_int = convert(std::to_string(v));
	}

	String::String(const i64 v)
	{
		str_int = convert(std::to_string(v));
	}

	String::String(const f32 v)
	{
		str_int = convert(std::to_string(v));
	}

	String::String(const f64 v)
	{
		str_int = convert(std::to_string(v));
	}

	///////////////////////////////////////////////////////////////////////////////
	// operator=
	//
	String& String::operator=(const char* s)
	{
		str_int = convert(s);
		return *this;
	}

	String& String::operator=(const wchar_t* s)
	{
		str_int = convert(s);
		return *this;
	}

	String& String::operator=(const std::string& s)
	{
		str_int = convert(s);
		return *this;
	}

	String& String::operator=(const std::wstring& s)
	{
		str_int = convert(s);
		return *this;
	}

	String& String::operator=(const std::u16string& s)
	{
		str_int = convert(s);
		return *this;
	}

	String& String::operator=(const std::u32string& s)
	{
		str_int = s;
		return *this;
	}

	String& String::operator=(const String& s)
	{
		str_int = s.str_int;
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	// operator+=
	//
	String& String::operator+=(const char* s)
	{
		str_int += convert(s);
		return *this;
	}

	String& String::operator+=(const wchar_t* s)
	{
		str_int += convert(s);
		return *this;
	}

	String& String::operator+=(const std::string& s)
	{
		str_int += convert(s);
		return *this;
	}

	String& String::operator+=(const std::wstring& s)
	{
		str_int += convert(s);
		return *this;
	}

	String& String::operator+=(const std::u16string& s)
	{
		str_int += convert(s);
		return *this;
	}

	String& String::operator+=(const std::u32string& s)
	{
		str_int += s;
		return *this;
	}

	String& String::operator+=(const String& s)
	{
		str_int += s.str_int;
		return *this;
	}

	bool String::operator==(const char* s)
	{
		return str_int == convert(s);
	}

	bool String::operator==(const wchar_t* s)
	{
		return str_int == convert(s);
	}

	bool String::operator==(const std::string& s)
	{
		return str_int == convert(s);
	}

	bool String::operator==(const std::wstring& s)
	{
		return str_int == convert(s);
	}

	bool String::operator==(const std::u16string& s)
	{
		return str_int == convert(s);
	}

	bool String::operator==(const std::u32string& s)
	{
		return str_int == s;
	}

	bool String::operator==(const String& s) const
	{
		return str_int == s.str_int;
	}


	bool String::operator!=(const char* s)
	{
		return str_int != convert(s);
	}

	bool String::operator!=(const wchar_t* s)
	{
		return str_int != convert(s);
	}

	bool String::operator!=(const std::string& s)
	{
		return str_int != convert(s);
	}

	bool String::operator!=(const std::wstring& s)
	{
		return str_int != convert(s);
	}

	bool String::operator!=(const std::u16string& s)
	{
		return str_int != convert(s);
	}

	bool String::operator!=(const std::u32string& s)
	{
		return str_int != s;
	}

	bool String::operator!=(const String& s) const
	{
		return str_int != s.str_int;
	}

	bool String::operator<(const String& s) const
	{
		return str_int < s.str_int;
	}

	bool String::operator>(const String& s) const
	{
		return str_int > s.str_int;
	}

	char32_t& String::operator[](u32 pos)
	{
		return str_int[pos];
	}

	const char32_t& String::operator[](u32 pos) const
	{
		return str_int[pos];
	}

	///////////////////////////////////////////////////////////////////////////////
	// operator+
	//
	String String::operator+(const char* s)
	{
		String ret(*this);
		ret += s;
		return ret;
	}

	String String::operator+(const wchar_t* s)
	{
		String ret(*this);
		ret += s;
		return ret;
	}

	String String::operator+(const std::string& s)
	{
		String ret(*this);
		ret += s;
		return ret;
	}

	String String::operator+(const std::wstring& s)
	{
		String ret(*this);
		ret += s;
		return ret;
	}

	String String::operator+(const std::u16string& s)
	{
		String ret(*this);
		ret += s;
		return ret;
	}

	String String::operator+(const std::u32string& s)
	{
		String ret(*this);
		ret += s;
		return ret;
	}

	String String::operator+(const String& s)
	{
		String ret(*this);
		ret += s;
		return ret;
	}

	///////////////////////////////////////////////////////////////////////////////
	// non-member operator for string concatenization
	//
	String operator+(const String& s1, const String& s2)
	{
		String ret(s1);
		ret += s2;
		return ret;
	}

	std::wostream& operator<<(std::wostream& out, String& str)
	{
		out << str.to_wstring();
		return out;
	}

	///////////////////////////////////////////////////////////////////////////////
	// return converted string types
	std::string String::to_string() const
	{
		std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
		return conv.to_bytes(str_int);
	}

	std::wstring String::to_wstring() const
	{
		//std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> conv;
		//std::string bytes = conv.to_bytes(str_int.c_str());
		//return std::wstring(reinterpret_cast<const wchar_t*>(bytes.c_str()), bytes.length() / sizeof(wchar_t));

		std::wstring ret;
		size_t n(ConvertUnicodeString(ret, str_int));
		return ret;
	}

	const wchar_t* String::to_wchar()
	{
		str_u16 = to_wstring();
		return str_u16.data();
	}

	const char* String::to_char()
	{
		str_u8 = to_string();
		return str_u8.data();
	}

	///////////////////////////////////////////////////////////////////////////////
	// return string as numeric values
	//
	i32 String::to_i32(size_t* pos) const
	{
		return static_cast<i32>(std::stoi(to_string(), pos, 10));
	}

	u32 String::to_u32(size_t* pos) const
	{
		return static_cast<u32>(std::stol(to_string(), pos, 0));
	}

	f32 String::to_f32(size_t* pos) const
	{
		return static_cast<f32>(std::stof(to_string(), pos));
	}

	f64 String::to_f64(size_t* pos) const
	{
		return static_cast<f64>(std::stof(to_string(), pos));
	}

	void String::clear()
	{
		str_int.clear();
	}

	String::iterator String::begin()
	{
		return str_int.begin();
	}

	String::iterator String::end()
	{
		return str_int.end();
	}

	size_t String::find(const String& str, size_t pos) const
	{
		return str_int.find(str.str_int.c_str(), pos);
	}

	size_t String::find_first_of(const String& str, size_t pos) const
	{
		return str_int.find_first_of(str.str_int.c_str(), pos);
	}

	size_t String::find_first_of(const char& chr, size_t pos) const
	{
		char32_t c = (char32_t)chr;
		return str_int.find_first_of(c, pos);
	}

	size_t String::find_last_of(const String& str, size_t pos) const
	{
		return str_int.find_last_of(str.str_int.c_str(), pos);
	}

	size_t String::find_last_of(const char& chr, size_t pos) const
	{
		char32_t c = (char32_t)chr;
		return str_int.find_last_of(c, pos);
	}

	size_t String::find_first_not_of(const String& str, size_t pos) const
	{
		return str_int.find_first_not_of(str.str_int.c_str(), pos);
	}

	size_t String::find_first_not_of(const char& chr, size_t pos) const
	{
		char32_t c = (char32_t)chr;
		return str_int.find_first_not_of(c, pos);
	}

	size_t String::find_last_not_of(const String& str, size_t pos) const
	{
		return str_int.find_last_not_of(str.str_int.c_str(), pos);
	}

	size_t String::find_last_not_of(const char& chr, size_t pos) const
	{
		char32_t c = (char32_t)chr;
		return str_int.find_last_not_of(c, pos);
	}

	String String::substr(size_t pos, size_t len) const
	{
		return str_int.substr(pos, len);
	}

	String& String::erase(size_t pos, size_t len)
	{
		str_int.erase(pos, len);
		return *this;
	}

	String& String::ltrim()
	{
		str_int.erase(0, str_int.find_first_not_of(U" \n\r\t"));
		return *this;
	}

	String& String::rtrim()
	{
		str_int.erase(str_int.find_last_not_of(U" \n\r\t") + 1);
		return *this;
	}

	String& String::trim()
	{
		ltrim();
		rtrim();
		return *this;
	}

	String& String::upper()
	{
		std::u32string var(str_int);
		std::transform(var.begin(), var.end(), var.begin(), ::toupper);
		str_int = var;
		return *this;
	}

	String& String::lower()
	{
		std::u32string var(str_int);
		std::transform(var.begin(), var.end(), var.begin(), ::tolower);
		str_int = var;
		return *this;
	}


	///////////////////////////////////////////////////////////////////////////////
	// internal conversions
	//
	std::u32string String::convert(const char* s)
	{
		std::u32string str;
		ConvertUnicodeString(str, s);
		return str;
	}

	std::u32string String::convert(const wchar_t* s)
	{
		std::u32string str;
		ConvertUnicodeString(str, s);
		return str;
	}

	std::u32string String::convert(const std::wstring& s)
	{
		std::u32string str;
		ConvertUnicodeString(str, s);
		return str;
	}

	std::u32string String::convert(const std::u16string& s)
	{
		std::u32string str;
		ConvertUnicodeString(str, s);
		return str;
	}

	std::u32string String::convert(const std::string& s)
	{
		std::u32string str;
		ConvertUnicodeString(str, s);
		return str;
	}


} // namespace sge

