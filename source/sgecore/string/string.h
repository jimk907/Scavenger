#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "sge_defines.h"
#include <string>
typedef std::string u8string;

//-------------------------------------------------------------
//  One string to rule them all and in the darkness bind them!
// 
//  Scavenger internal string format is UTF32.
//  This string class is a wrapper around u32string and is used
//  to encapsulate common conversions.
//-------------------------------------------------------------


namespace sge
{

	class String
	{
	public:
		typedef std::u32string::iterator iterator;
		typedef std::u32string::size_type size_type;
		static const size_t npos = -1;

		String();
		~String();

		String(const char* s);
		String(const wchar_t* s);
		String(const std::string& s);
		String(const std::wstring& s);
		String(const std::u16string& s);
		String(const std::u32string& s);
		String(const String& s);

		String(const u8);
		String(const u16);
		String(const u32);
		String(const u64);
		String(const i8);
		String(const i16);
		String(const i32);
		String(const i64);
		String(const f32);
		String(const f64);

		String& operator=(const char* s);
		String& operator=(const wchar_t* s);
		String& operator=(const std::string& s);
		String& operator=(const std::wstring& s);
		String& operator=(const std::u16string& s);
		String& operator=(const std::u32string& s);
		String& operator=(const String& s);

		String& operator+=(const char* s);
		String& operator+=(const wchar_t* s);
		String& operator+=(const std::string& s);
		String& operator+=(const std::wstring& s);
		String& operator+=(const std::u16string& s);
		String& operator+=(const std::u32string& s);
		String& operator+=(const String& s);

		String operator+(const char* s);
		String operator+(const wchar_t* s);
		String operator+(const std::string& s);
		String operator+(const std::wstring& s);
		String operator+(const std::u16string& s);
		String operator+(const std::u32string& s);
		String operator+(const String& s);


		bool operator==(const char* s);
		bool operator==(const wchar_t* s);
		bool operator==(const std::string& s);
		bool operator==(const std::wstring& s);
		bool operator==(const std::u16string& s);
		bool operator==(const std::u32string& s);
		bool operator==(const String& s) const;

		bool operator!=(const char* s);
		bool operator!=(const wchar_t* s);
		bool operator!=(const std::string& s);
		bool operator!=(const std::wstring& s);
		bool operator!=(const std::u16string& s);
		bool operator!=(const std::u32string& s);
		bool operator!=(const String& s) const;

		bool operator<(const String& s) const;
		bool operator>(const String& s) const;

		char32_t& operator[](u32 pos);
		const char32_t& operator[](u32 pos) const;


		friend String operator+(const String& s1, const String& s2);
		friend std::wostream& operator<<(std::wostream&, String& str);

		size_t length() const { return str_int.length(); }
		size_t size() const { return str_int.size(); }

		std::string    to_string() const;
		std::wstring   to_wstring() const;
		const wchar_t* to_wchar();
		const char*    to_char();
		i32            to_i32(size_t* pos = 0) const;
		u32            to_u32(size_t* pos = 0) const;
		f32            to_f32(size_t* pos = 0) const;
		f64            to_f64(size_t* pos = 0) const;

		void clear();
		bool empty() const { return str_int.empty(); }

		iterator begin();
		iterator end();

		size_t find(const String& str, size_t pos = 0) const;
		size_t find_first_of(const String& str, size_t pos = 0) const;
		size_t find_first_of(const char& chr, size_t pos = 0) const;
		size_t find_last_of(const String& str, size_t pos = npos) const;
		size_t find_last_of(const char& chr, size_t pos = npos) const;
		size_t find_first_not_of(const String& str, size_t pos = 0) const;
		size_t find_first_not_of(const char& chr, size_t pos = 0) const;
		size_t find_last_not_of(const String& str, size_t pos = npos) const;
		size_t find_last_not_of(const char& chr, size_t pos = npos) const;

		String substr(size_t pos = 0, size_t len = npos) const;
		String& erase(size_t pos = 0, size_t len = npos);
		String& ltrim();
		String& rtrim();
		String& trim();
		String& upper();
		String& lower();

	private:
		std::u32string str_int;
		std::wstring   str_u16;
		std::string    str_u8;

	private:
		std::u32string convert(const char* s);
		std::u32string convert(const wchar_t* s);
		std::u32string convert(const std::wstring& s);
		std::u32string convert(const std::u16string& s);
		std::u32string convert(const std::string& s);

	};

} // namespace sge

