#pragma once


#include "sge_defines.h"

namespace sge
{


	typedef unsigned char UTF8;  /**< UTF-8 type as unsigned 8-bit char */
	typedef char16_t      UTF16; /**< UTF-16 type as unsigned 16 bit word */
	typedef char32_t      UTF32; /**< UTF-32 type as unsigned 32 bit integer */

#define SGE_UTF16_BOM         0xFEFF     /**< Byte-Order mark (BOM) for UTF-16 BE */
#define SGE_UTF16_LE_BOM      0xFFFE     /**< Byte-Order Mark (BOM) for UTF-16 LE */
#define SGE_UTF32_BOM         0x0000FEFF /**< Byte-Order Mark (BOM) for UTF-32 BE */
#define SGE_UTF32_LE_BOM      0xFFFE0000 /**< Byte-Order Mark (BOM) for UTF-32 LE */
#define SGE_UNI_WORD_JOINER   0x2060     /**< ZWNBS zero-width no-break space word joiner */
#define SGE_UTF8_BOM          0xEFBBBF   /**< Byte-Order Mark (BOM) for UTF-8 */
#define SGE_UTF8_REPLACEMENT  0xEFBFBD   /**< UTF-8 string replacement char */
#define SGE_STR_REPLACEMENT   '?'        /**< SGE defined string replacement char */
#define SGE_WCHAR_REPLACEMENT 0xFFFD     /**< SGE defined wchar_t replaement char */
#define SGE_UTF16_REPLACEMENT 0xFFFD     /**< UTF16 replacement character */
#define SGE_UTF8_MAX_BYTES    4          /**< 1 + max of 3 following bytes - update if standard changes */


	enum SGEUnicodeType : uint32_t {
		SGE_IS_UNKNOWN = 0, /**< Unicode type is unknown */
		SGE_IS_UTF8 = 1, /**< Unicode type is UTF-8 */
		SGE_IS_UTF16 = 2, /**< Unicode type is UTF-16 */
		SGE_IS_UTF32 = 4, /**< Unicode type is UTF-32 */
	};

	enum SGEUnicodeError : int32_t {
		SGE_ERR_CONVERSION_FAIL = -1, /**< Malformed or unknown codepoint */
		SGE_ERR_DESTINATION_SIZE = -2, /**< Destination buffer is too small */
		SGE_ERR_OUT_OF_RANGE = -3, /**< The codepoint is out of range */
	};


	extern const uint8_t utf8_trailing_bytes[256]; /**< static global table of UTF-8 trailing byte counts */
	uint32_t utf16_trailing_words(UTF16 u);

	//------------------------------------------------------------
	// codepoint info and conversions
	char     char_from_utf8(UTF8* src);

	bool    utf8char_is_valid(const UTF8* codepoint, size_t length);
	bool    utf16char_is_valid(const UTF16* codepoint, size_t length, bool BMP = false);
	bool    utf32char_is_valid(const UTF32* codepoint, bool BMP = false);

	size_t  get_unicode_type(const char* bytes, size_t length);

	size_t  utf8char_from_wchar(UTF8* destination, size_t nDest, const wchar_t source);
	size_t  utf8char_from_utf16char(UTF8* destination, size_t nDest, const UTF16 source);
	size_t  utf8char_from_utf32char(UTF8* destination, size_t nDest, const UTF32 source);
	size_t  utf8char_from_char(UTF8* destination, size_t nDest, const char source);

	size_t  utf16char_from_utf8char(UTF16* destination, size_t nDest, const UTF8* source, size_t nSrc);
	size_t  utf16char_from_utf32char(UTF16* destination, size_t nDest, const UTF32 source);

	UTF32   utf32char_from_utf8char(const UTF8* source, size_t nSrc);
	UTF32   utf32char_from_utf16char(const UTF16* source, size_t nSrc);
	UTF32   utf32char_from_wchar(const wchar_t* source, size_t nSrc);

	size_t  utf16len_from_utf8str(UTF8* source, size_t nSrc);
	size_t  utf32len_from_utf8str(UTF8* source, size_t nSrc);

	wchar_t wchar_from_char(char c);

	size_t  wchar_from_utf8char(wchar_t* w, size_t wcount, const UTF8* u, size_t ucount);
	size_t  wchar_from_utf16char(wchar_t* w, size_t wcount, const UTF16* u, size_t count);
	size_t  wchar_from_utf32char(wchar_t* w, size_t wcount, const UTF32 u);

	//------------------------------------------------------------
	// unicode string conversions
	// The following functions are scavenged from:
	// https://github.com/Alexhuszagh/UTFPP and modified for this
	// library which is published with the following copyright and
	// license...
	// 
	// Unicode Terms of Use
	//Copyright 2001 - 2004 Unicode, Inc.
	//Copyright 2016 2016 The Regents of the University of California.
	//
	//Disclaimer
	// This source code is provided as is by Unicode, Inc.No claims 
	// are made as to fitness for any particular purpose.No warranties 
	// of any kind are expressed or implied.The recipient agrees to 
	// determine applicability of information provided.If this file 
	// has been purchased on magnetic or optical media from Unicode, 
	// Inc., the sole remedy for any claim will be exchange of 
	// defective media within 90 days of receipt.
	//
	//Limitations on Rights to Redistribute This Code
	// Unicode, Inc.hereby grants the right to freely use the 
	// information supplied in this file in the creation of products 
	// supporting the Unicode Standard, and to make copies of this 
	// file in any form for internal or external distribution as long 
	// as this notice remains attached.
	//
} // namespace sge


#include <stdint.h>
#include <string>
#include <array>
#include <stdexcept>


typedef char8_t  UTF8; // defined in C++20
typedef char16_t UTF16;
typedef char32_t UTF32;

extern const std::array<uint8_t, 7> FIRST_BYTE_MARK;
extern const std::array<uint8_t, 256> UTF8_BYTES;
extern const std::array<uint32_t, 6> UTF8_OFFSETS;

/** \brief Illegal character detected.
	*/
struct IllegalCharacterError : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Illegal character found during conversion.\n";
	}
};


/** \brief Not enough space in output buffer.
	*/
struct BufferRangeError : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Cannot add characters too buffer, output is too small.\n";
	}
};


size_t ConvertUnicodeString(std::u16string& dst, const std::u32string& src, bool strict = false);
size_t ConvertUnicodeString(std::wstring& dst, const std::u32string& src, bool strict = false);
size_t ConvertUnicodeString(std::u8string& dst, const std::u32string& src, bool strict = false);
size_t ConvertUnicodeString(std::string& dst, const std::u32string& src, bool strict = false);

size_t ConvertUnicodeString(std::u32string& dst, const std::u16string& src, bool strict = false);
size_t ConvertUnicodeString(std::u32string& dst, const std::wstring& src, bool strict = false);
size_t ConvertUnicodeString(std::u32string& dst, const std::u8string& src, bool strict = false);
size_t ConvertUnicodeString(std::u32string& dst, const std::string& src, bool strict = false);

