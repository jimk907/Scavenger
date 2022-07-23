#include "unicode.h"


namespace sge
{

	// the number of bytes which must follow the first byte of a utf-8 code point.
	// note: a utf-8 code point can only be 4 bytes max so the values below > 3
	//       are illegal. 
	static const uint8_t utf8_trailing_bytes[256] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//   0. -  31. byte 00-1F
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//  32. -  63. byte 20-3F
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//  64. -  95. byte 40-5F
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//  96. - 127. byte 60-7F
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	// 128. - 159. byte 80-9F
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	// 160. - 191. byte A0-BF
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	// 192. - 223. byte C0-DF
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5	// 224. - 255. byte E0-FF
	};


	uint32_t utf16_trailing_words(UTF16 u)
	{
		if (u >= 0xd800 && u <= 0xdbff)
			return 2;
		else
			return 1;
	}

	char char_from_utf8(UTF8* src) {
		char ret(0);
		if (src) {
			uint32_t bytes = utf8_trailing_bytes[*src] + 1;
			if (bytes == 1) {
				ret = *src;
			}
			else
				ret = SGE_STR_REPLACEMENT;
		}
		return ret;
	}

	//-----------------------------------------------------------------------------
	bool utf8char_is_valid(const UTF8* codepoint, size_t length)
	{
		UTF8 a(0);
		UTF8 src(*codepoint);
		const UTF8* srcptr = codepoint + length;
		switch (length) {
		default:
			return false;
			/* Everything else falls through when "true"... */
		case 4:
			if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
				return false;
		case 3:
			if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
				return false;
		case 2:
			if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
				return false;

			switch (src) {
				/* no fall-through in this inner switch */
				// special two-byte cases
			case 0xE0: if (a < 0xA0) return false; break;
			case 0xED: if (a > 0x9F) return false; break;
			case 0xF0: if (a < 0x90) return false; break;
			case 0xF4: if (a > 0x8F) return false; break;
			default:   if (a < 0x80) return false;
			}

		case 1:
			if (src >= 0x80 && src < 0xC2)
				return false;
		}
		if (src > 0xF4) return false;
		return true;

	}

	//-----------------------------------------------------------------------------
	bool utf16char_is_valid(const UTF16* codepoint, size_t length, bool BMP)
	{
		const UTF16* s(codepoint);
		bool ret(false);

		if (length) {
			ret = true;
			if (*s == SGE_UTF16_BOM) {
				// BOM?
				return ret;
			}
			if ((*s & 0xd800) == 0xd800) {
				// surrogate?
				if (length < 2) return false;
				if ((s[1] & 0xdc00) != 0xd800) return false;
				return ret;
			}
			if (length > 2)
				return false;
			if (BMP) {
				UTF32 dst = utf32char_from_utf16char(codepoint, length);
				if (dst > 0x10FFFF)
					return false;
			}
		}
		return ret;
	}

	//-----------------------------------------------------------------------------
	bool utf32char_is_valid(const UTF32* codepoint, bool BMP)
	{
		const UTF32* s(codepoint);
		bool ret(false);

		ret = true;
		if (*s == SGE_UTF32_BOM) {
			// BOM?
			return ret;
		}
		if ((*s & 0xFF000000) > 0)
			return false;
		if (BMP) {
			if (*s > 0x10FFFF)
				return false;
		}
		return ret;
	}

	//-----------------------------------------------------------------------------
	size_t get_unicode_type(const char* bytes, size_t length)
	{
		bool   is8(true), is16(true), is32(true);
		size_t n8(0), n16(0), n32(0);             // next byte to check
		size_t len(0);
		const UTF8* chr(reinterpret_cast<const unsigned char*>(bytes));

		if (length & 0x1) {// odd number of chars cannot be utf16 or utf32
			is16 = false;
			is32 = false;
		}

		// check minimum lengths
		if (length < 4)
			is32 = false;
		if (length < 2)
			is16 = false;

		// check BOMs - even though we check LE BOMs
		// they should not exist when this function is called.
		if (length > 1) {
			if ((chr[0] == 0xfe && chr[1] == 0xff) || (chr[0] == 0xff && chr[1] == 0xfe)) {
				is8 = false;
				is32 = false;
				chr += 2; // skip the BOM
			}
		}
		if (is8 && length > 2) {
			if (chr[0] == 0xef && chr[1] == 0xbb && chr[2] == 0xbf) {
				is16 = false;
				is32 = false;
				chr += 3; // skip the BOM
			}
		}
		if (is32 && length > 3) {
			if ((chr[0] == 0 && chr[1] == 0 && chr[2] == 0xfe && chr[3] == 0xff) ||
				(chr[0] == 0xff && chr[1] == 0xfe && chr[2] == 0 && chr[3] == 0)) {
				is8 = false;
				is16 = false;
				chr += 4;
			}
		}

		// the following will count the number of encoded ascii sequences
		size_t a8(0), a16(0), a32(0);

		// scan chars
		while (len < length) {
			if (is8 && (n8 == len)) {
				int c = utf8_trailing_bytes[*chr] + 1;
				n8 += c;
				if (!utf8char_is_valid(chr, c))
					is8 = false;
			}
			if (is16 && (n16 == len)) {
				int c = 2;
				if (*chr > 0xd7ff && *chr < 0xdc00) {
					if (len < length - 1)
						if (*(chr + 1) > 0xdb00 && *(chr + 1) < 0xe000)
							c = 4;
				}
				n16 += c;
			}
			// under current definitions of unicode, utf-32 is encoded in 3 octets.
			// so, if the first octet is non-zero it can't be utf-32.
			if (is32 && (len >= 3) && ((len & 0x3) == 0x3))
				if (chr[len - 3] > 0)
					is32 = false;

			// check for encoded ascii + ctrl chars
			if (chr[len] < 0x80) {

				// utf-32 ascii signature:
				// prev. 32 bits seq. being tested
				// |         -4| |-3 -2 -1 len| len & 0x3 must equal 0x3
				// |00 00 2D 3E| |00 00 00  0A|
				// |         ^^| |^^ ^^ ^^    |
				// |must be > 0| |must be 0   |

				if (is32 && (len > 4) && (len & 0x3) == 0x3) {  // the ascii must be the 4th byte (len & 0x3 == 0x3)
					if (chr[len - 1] == 0 && chr[len - 2 == 0] && chr[len - 3 == 0] && chr[len - 4] != 0)
						++a32;
				}
				else
					if (is16 && (len > 2) && (len & 0x1) != 0x1) {
						if (chr[len - 1] == 0 && chr[len - 2] != 0)
							++a16;
						else
							++a8;
					}
					else
						++a8;
			}
			++len;
		}

		// check ascii counts...use an arbitrary factor of 2
		size_t n = a32 * 2;
		if ((is16 && (n < a16)) || (is8 && (n < a8)))
			is32 = false;
		n = a16 * 2;
		if ((is8 && (n < a8)))
			is16 = false;

		// check for z-string termination chars
		if (is32 & (length > 3)) {
			if (chr[length - 4] == 0 && chr[length - 3] == 0 && chr[length - 2] == 0 && chr[length - 1] == 0) {
				// looks like utf-32 terminator
				if (is8 && is16) { // if still undecided...
					is8 = false;
					is16 = false;
				}
			}
		}
		if (is16 & (length > 3)) {
			if (chr[length - 2] == 0 && chr[length - 1] == 0) {
				// looks like utf-16 terminator
				is8 = false;
			}
		}

		size_t retv = SGE_IS_UNKNOWN;
		if (is8)  retv += SGE_IS_UTF8;
		if (is16) retv += SGE_IS_UTF16;
		if (is32) retv += SGE_IS_UTF32;
		return retv;
	}


	//-----------------------------------------------------------------------------
	size_t utf8char_from_wchar(UTF8* destination, size_t nDest, const wchar_t source)
	{
		const char32_t u32 = static_cast<UTF32>(source); //wchar_t may be 16 or 32 bits (platform dependent)!	
		return utf8char_from_utf32char(destination, nDest, u32);
	}


	size_t utf8char_from_utf16char(UTF8* destination, size_t nDest, const UTF16 source)
	{
		const char32_t u32 = static_cast<UTF32>(source);
		return utf8char_from_utf32char(destination, nDest, u32);
	}

	size_t utf8char_from_char(UTF8* destination, size_t nDest, const char source)
	{
		size_t chr(source);
		chr &= 0x00ff;
		const UTF32 u32 = static_cast<UTF32>(chr);
		return utf8char_from_utf32char(destination, nDest, u32);
	}

	size_t utf8char_from_utf32char(UTF8* destination, size_t nDest, const UTF32 source)
	{
		if (destination && nDest) {
			const uint32_t u32 = source;
			if (u32 < 0x0080) {
				destination[0] = static_cast<char>(u32);
				return 1;
			}
			if (u32 < 0x0800 && nDest > 1) {
				destination[0] = static_cast<char>((u32 >> 6) | 0xC0);
				destination[1] = (u32 & 0x3F) | 0x80;
				return 2;
			}
			if (u32 < 0x10000 && nDest > 2) {
				destination[0] = static_cast<char>((u32 >> 12) | 0xE0);
				destination[1] = ((u32 >> 6) & 0x3F) | 0x80;
				destination[2] = (u32 & 0x3F) | 0x80;
				return 3;
			}
			if (u32 < 0x110000 && nDest > 3) {
				destination[0] = static_cast<char>((u32 >> 18) | 0xF0);
				destination[1] = ((u32 >> 12) & 0x3F) | 0x80;
				destination[2] = ((u32 >> 6) & 0x3F) | 0x80;
				destination[3] = (u32 & 0x3F) | 0x80;
				return 4;
			}
		}
		return 0;
	}

	//-----------------------------------------------------------------------------
	size_t utf16char_from_utf8char(UTF16* destination, size_t nDest, const UTF8* source, size_t nSrc)
	{
		if (destination && nDest) {
			//const UTF8* src(source);
			UTF16 dst[2] = { 0, 0 };
			if (*source < 0x7f) {
				*destination = static_cast<UTF16>(*source);
				return 1;
			}
			if ((*source & 0xe0) == 0xc0 && nSrc > 1) {
				if ((source[1] & 0xc0) == 0x80) {
					dst[0] = UTF16(((source[0] & 0x1f) << 6) + (source[1] & 0x3f));
					*destination = dst[0];
					return 1;
				}
			}
			if ((*source & 0xf0) == 0xe0 && nSrc > 2) {
				if ((source[1] & 0xc0) == 0x80 && (source[2] & 0xc0) == 0x80) {
					dst[0] = UTF16(((source[0] & 0xf) << 12) + ((source[1] & 0x3f) << 6) + (source[2] & 0x3f));
					*destination = dst[0];
					return 1;
				}
			}
			//000u uuuu zzzz yyyy yyxx xxxx
			if ((*source & 0xf8) == 0xf0 && nSrc > 3 && nDest > 1) {
				UTF32 u32 = utf32char_from_utf8char(source, nSrc) - 0x10000;
				destination[0] = static_cast<UTF16>(u32 >> 10) + 0xD800;
				destination[1] = (u32 & 0x3FF) + 0xDC00;
				return 2;
				//if ((source[1] & 0xc0) == 0x80 && (source[2] & 0xc0) == 0x80 && (source[3] & 0xc0) == 0x80) {
				//	dst[0] = ((source[0] & 0x7) << 2) + ((source[1] & 0x30) >> 4 );
				//	dst[1] = ((source[1] & 0xf) << 12) + ((source[2] & 0x3f) << 6) + (source[3] & 0x3f);
				//	destination[0] = dst[0];
				//	destination[1] = dst[1];
				//	return 2;
				//}
			}
		}
		return 0;
	}

	//-----------------------------------------------------------------------------
	size_t utf16char_from_utf32char(UTF16* destination, size_t nDest, const UTF32 source)
	{
		if (destination && nDest) {
			if (source < 0xE000 && source > 0xD7FFF)
				return 0;
			if (source < 0x10000) {
				if (nDest > 1) {
					destination[0] = static_cast<UTF16>(source);
					return 1;
				}
			}
			else {
				// construct surrogate pair
				//if (source < 0x10FFFF && nDest > 3) {
				uint32_t src = static_cast<uint32_t>(source) - 0x10000;
				// 0000 0000 0000 0000 0000
				// F    F    C >> 10         + D800
				// 0    0    3    F    F     + DC00
				destination[0] = ((src & 0xFFC00) >> 10) + 0xD800;
				destination[1] = (src & 0x003FF) + 0xDC00;
				return 2;
				//}
			}
		}
		return 0;
	}

	//-----------------------------------------------------------------------------
	UTF32 utf32char_from_utf8char(const UTF8* source, size_t nSrc)
	{
		if (!source)
			return 0;
		UTF16 d[2];
		size_t nd = utf16char_from_utf8char(d, 2, source, nSrc);
		if (!nd)
			return 0;
		return utf32char_from_utf16char(d, nd);
	}

	//-----------------------------------------------------------------------------
	UTF32 utf32char_from_utf16char(const UTF16* source, size_t nSrc)
	{
		UTF32 ret(0);
		if (nSrc && source) {
			if (*source < 0xd800 || *source > 0xdbff)
				ret = static_cast<UTF32>(*source);
			else if (nSrc > 1) {
				// decode the surrogate
				ret = (((source[0] - 0xD800) << 10) + (source[1] - 0xDC00)) + 0x10000;
			}
		}
		return ret;
	}

	UTF32 utf32char_from_wchar(const wchar_t* source, size_t nSrc)
	{
		UTF32 dst(0);
		if (!source)
			return dst;
		if (source[0] >= 0xd800 && source[0] <= 0xdbff) {
			// surrogate pair
			if (nSrc < 2)
				return dst;
			dst = 0x10000;
			dst += (source[0] & 0x3fff) << 10;
			dst += (source[1] & 0x3fff);
		}
		return dst;
	}


	//-----------------------------------------------------------------------------
	size_t utf16len_from_utf8str(UTF8* source, size_t nSrc)
	{
		size_t ret(0);
		size_t ptr(0);
		UTF16  dst[2]; // dummy

		while (source && (nSrc > 0)) {
			while (ptr < nSrc) {
				uint32_t c = utf8_trailing_bytes[*(source + ptr)];
				size_t u = utf16char_from_utf8char(dst, 2, source + ptr, c);
				ptr += c;
				ret += u;
			}
		}
		return ret;
	}

	//-----------------------------------------------------------------------------
	size_t utf32len_from_utf8str(UTF8* source, size_t nSrc)
	{
		size_t ret(0);
		size_t ptr(0);

		while (source && (nSrc > 0)) {
			while (ptr < nSrc) {
				uint32_t c = utf8_trailing_bytes[*(source + ptr)];
				ptr += c;
				++ret;
			}
		}
		return ret;
	}


	//-----------------------------------------------------------------------------
	wchar_t wchar_from_char(char u)
	{
		uint16_t w(u);
		return wchar_t(w);
	}

	//-----------------------------------------------------------------------------
	size_t  wchar_from_utf8char(wchar_t* w, size_t wcount, const UTF8* u, size_t ucount)
	{
		UTF16 u1[2] = { 0 };
		size_t c(utf16char_from_utf8char(u1, 2, u, ucount));

		return wchar_from_utf16char(w, wcount, u1, c);
	}

	//-----------------------------------------------------------------------------
	size_t  wchar_from_utf16char(wchar_t* w, size_t wcount, const UTF16* u, size_t ucount)
	{
		// endian test
		union {
			uint16_t u;
			char   c[2];
		} bend = { 0x0102 };

		for (size_t i = 0; i < ucount; i++) {
			unsigned short us = u[i];
			//if(bend.c[0] != 0x01)
			//	us = _byteswap_ushort(u[i]);
			w[i] = us;
		}
		return ucount;
	}

	//-----------------------------------------------------------------------------
	size_t wchar_from_utf32char(wchar_t* w, size_t wcount, UTF32 u)
	{
		UTF16 u1[2] = { 0 };
		size_t c(utf16char_from_utf32char(u1, 2, u));
		c = wchar_from_utf16char(w, wcount, u1, c);
		return c;
	}

	size_t u32string_from_string(std::u32string& out, const std::string& in)
	{
		size_t ret(0);
		out.clear();
		if (in.empty()) return 0;
		
		size_t p(0);
		i8     cpsize(0);
		while (p < in.length()) {
			cpsize = utf8_trailing_bytes[in[p]] + 1;
			ret += utf32char_from_utf8char((const UTF8*)&in[p], in.size());
			p += cpsize;
		}
		return ret;
	}

	size_t u32string_from_wstring(std::u32string& out, const std::wstring& in)
	{
		size_t ret(0);
		out.clear();
		if (in.empty()) return 0;

		size_t p(0);
		i8     cpsize(0);
		while (p < in.length()) {
			cpsize = utf16_trailing_words(in[p]);
			ret += utf32char_from_wchar(&in[p], in.size());
			p += cpsize;
		}
		
		return ret;
	}

	size_t u32string_from_u16string(std::u32string& out, const std::u16string& in)
	{
		size_t ret(0);
		out.clear();
		if (in.empty()) return 0;

		size_t p(0);
		i8     cpsize(0);
		while (p < in.length()) {
			cpsize = utf16_trailing_words(in[p]);
			ret += utf32char_from_utf16char(&in[p], in.length());
			p += cpsize;
		}

		return ret;
	}


} // namespace sge

//------------------------------------------------------------
// unicode string conversions
// The following functions are scavenged from:
// https://github.com/Alexhuszagh/UTFPP and modified for this
// library which is copyrighted and licensed.
// (see file Unicode.h in this project.)
// 

const std::array<uint8_t, 7> FIRST_BYTE_MARK = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
const std::array<uint8_t, 256> UTF8_BYTES = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};
const std::array<uint32_t, 6> UTF8_OFFSETS = { 0x00000000UL, 0x00003080UL, 0x000E2080UL, 0x03C82080UL, 0xFA082080UL, 0x82082080UL };



/** \brief Replace illegal Unicode character if checkStrict is off.
	*/
uint32_t checkStrict(bool strict)
{
	constexpr uint32_t replacement = 0x0000FFFD;
	if (strict) {
		throw IllegalCharacterError();
	}
	return replacement;
}


size_t ConvertUnicodeString(std::u16string& dst, const std::u32string& src, bool strict)
{
	constexpr uint32_t maxUtf32 = 0x0010FFFF;
	constexpr uint32_t highBegin = 0xD800;
	constexpr uint32_t lowBegin = 0xDC00;
	constexpr uint32_t maxbmp = 0x0000FFFF;
	constexpr int shift = 10;
	constexpr uint32_t base = 0x0010000UL;
	constexpr uint32_t mask = 0x3FFUL;


	size_t src_len(src.length());
	auto siter = src.begin();

	char32_t c(0);
	while (siter != src.end()) {
		c = *siter++;

		if (c <= maxbmp) {
			if (c >= highBegin && c <= lowBegin) {
				dst += checkStrict(strict);
			}
			else {
				dst += UTF16(c);
			}
		}
		else if (c > maxUtf32) {
			dst += checkStrict(strict);
		}
		else {
			c -= base;
			dst += UTF16((c >> shift) + highBegin);
			dst += UTF16((c & mask) + lowBegin);
		}

	}
	return dst.length();
}

size_t ConvertUnicodeString(std::wstring& dst, const std::u32string& src, bool strict)
{
	constexpr uint32_t maxUtf32 = 0x0010FFFF;
	constexpr uint32_t highBegin = 0xD800;
	constexpr uint32_t lowBegin = 0xDC00;
	constexpr uint32_t maxbmp = 0x0000FFFF;
	constexpr int shift = 10;
	constexpr uint32_t base = 0x0010000UL;
	constexpr uint32_t mask = 0x3FFUL;


	size_t src_len(src.length());
	auto siter = src.begin();

	char32_t c(0);
	while (siter != src.end()) {
		c = *siter++;

		if (c <= maxbmp) {
			if (c >= highBegin && c <= lowBegin) {
				dst += checkStrict(strict);
			}
			else {
				dst += UTF16(c);
			}
		}
		else if (c > maxUtf32) {
			dst += checkStrict(strict);
		}
		else {
			c -= base;
			dst += UTF16((c >> shift) + highBegin);
			dst += UTF16((c & mask) + lowBegin);
		}

	}
	return dst.length();
}

size_t ConvertUnicodeString(std::u8string& dst, const std::u32string& src, bool strict)
{
	constexpr uint32_t maxUtf32 = 0x0010FFFF;
	constexpr uint32_t bytemark = 0x80;
	constexpr uint32_t bytemask = 0xBF;

	size_t src_len(src.length());
	auto siter = src.begin();
	char32_t c(0);

	char8_t buffer[5]{ 0 };

	while (siter != src.end()) {
		c = *siter++;

		// calculate bytes to write
		short bytes(0);
		if (c < 0x80) {
			bytes = 1;
		}
		else if (c < 0x800) {
			bytes = 2;
		}
		else if (c < 0x10000) {
			bytes = 3;
		}
		else if (c <= maxUtf32) {
			bytes = 4;
		}
		else {
			bytes = 3;
			c = checkStrict(strict);
		}

		short p(bytes);

		switch (bytes) {
		case 4:
			buffer[p--] = UTF8((c | bytemark) & bytemask);
			//*--begin = UTF8((c | bytemark) & bytemask);
			c >>= 6;
		case 3:
			buffer[p--] = UTF8((c | bytemark) & bytemask);
			//*--begin = UTF8((c | bytemark) & bytemask);
			c >>= 6;
		case 2:
			buffer[p--] = UTF8((c | bytemark) & bytemask);
			//*--begin = UTF8((c | bytemark) & bytemask);
			c >>= 6;
		case 1:
			buffer[p--] = UTF8((c | bytemark) & bytemask);
			//*--begin = UTF8(c | FIRST_BYTE_MARK[bytes]);
		}
		//begin += bytes;
		while (bytes--) {
			dst += buffer[p++];
		}
	}
	return dst.length();
}

size_t ConvertUnicodeString(std::string& dst, const std::u32string& src, bool strict)
{
	constexpr uint32_t maxUtf32 = 0x0010FFFF;
	constexpr uint32_t bytemark = 0x80;
	constexpr uint32_t bytemask = 0xBF;

	size_t src_len(src.length());
	auto siter = src.begin();
	char32_t c(0);

	char8_t buffer[4]{ 0 };

	while (siter != src.end()) {
		c = *siter++;

		// calculate bytes to write
		short bytes(0);
		if (c < 0x80) {
			bytes = 1;
		}
		else if (c < 0x800) {
			bytes = 2;
		}
		else if (c < 0x10000) {
			bytes = 3;
		}
		else if (c <= maxUtf32) {
			bytes = 4;
		}
		else {
			bytes = 3;
			c = checkStrict(strict);
		}

		short p(bytes);

		switch (bytes) {
		case 4:
			buffer[--p] = UTF8((c | bytemark) & bytemask);
			//*--begin = UTF8((c | bytemark) & bytemask);
			c >>= 6;
		case 3:
			buffer[--p] = UTF8((c | bytemark) & bytemask);
			//*--begin = UTF8((c | bytemark) & bytemask);
			c >>= 6;
		case 2:
			buffer[--p] = UTF8((c | bytemark) & bytemask);
			//*--begin = UTF8((c | bytemark) & bytemask);
			c >>= 6;
		case 1:
			buffer[--p] = UTF8(c | FIRST_BYTE_MARK[bytes]);
			//*--begin = UTF8(c | FIRST_BYTE_MARK[bytes]);
		}
		//begin += bytes;
		while (bytes--) {
			dst += buffer[p++];
		}
	}
	return dst.length();
}



size_t ConvertUnicodeString(std::u32string& dst, const std::u16string& src, bool strict)
{
	constexpr uint32_t highBegin = 0xD800;
	constexpr uint32_t highEnd = 0xDBFF;
	constexpr uint32_t lowBegin = 0xDC00;
	constexpr uint32_t lowEnd = 0xDFFF;
	constexpr int shift = 10;
	constexpr uint32_t base = 0x0010000UL;

	size_t src_len(src.length());
	auto siter = src.begin();
	char16_t c1(0);
	char16_t c2(0);

	while (siter != src.end()) {
		c1 = *siter++;
		if (c1 >= highBegin && c1 <= highEnd) {
			// surrogate pairs
			c2 = *siter++;
			if (c2 >= lowBegin && c2 <= lowEnd) {
				dst += ((c1 - highBegin) << shift) + (c2 - lowBegin) + base;
			}
			else {
				dst += checkStrict(strict);
			}
		}
		else if (c1 >= lowBegin && c1 <= lowEnd) {
			dst += checkStrict(strict);
		}
		else {
			dst += c1;
		}
	}
	return dst.length();
}

size_t ConvertUnicodeString(std::u32string& dst, const std::wstring& src, bool strict)
{
	constexpr uint32_t highBegin = 0xD800;
	constexpr uint32_t highEnd = 0xDBFF;
	constexpr uint32_t lowBegin = 0xDC00;
	constexpr uint32_t lowEnd = 0xDFFF;
	constexpr int shift = 10;
	constexpr uint32_t base = 0x0010000UL;

	size_t src_len(src.length());
	auto siter = src.begin();
	char16_t c1(0);
	char16_t c2(0);

	while (siter != src.end()) {
		c1 = *siter++;
		if (c1 >= highBegin && c1 <= highEnd) {
			// surrogate pairs
			c2 = *siter++;
			if (c2 >= lowBegin && c2 <= lowEnd) {
				dst += ((c1 - highBegin) << shift) + (c2 - lowBegin) + base;
			}
			else {
				dst += checkStrict(strict);
			}
		}
		else if (c1 >= lowBegin && c1 <= lowEnd) {
			dst += checkStrict(strict);
		}
		else {
			dst += c1;
		}
	}
	return dst.length();
}

size_t ConvertUnicodeString(std::u32string& dst, const std::u8string& src, bool strict)
{
	size_t src_len(src.length());
	auto siter = src.begin();
	char8_t c(0);
	uint8_t bytes(0);

	while (siter != src.end()) {
		c = *siter;
		bytes = UTF8_BYTES[c];
		if (siter + bytes > src.end()) {
			throw IllegalCharacterError();
		}
		char32_t cp(0);

		switch (bytes) {
		case 5:
			cp = checkStrict(strict);
			cp <<= 6;
		case 4:
			cp = checkStrict(strict);
			cp <<= 6;
		case 3:
			cp += *siter++;
			cp <<= 6;
		case 2:
			cp += *siter++;
			cp <<= 6;
		case 1:
			cp += *siter++;
			cp <<= 6;
		case 0:
			cp += *siter++;
		}
		cp -= UTF8_OFFSETS[bytes];
		dst += cp;
	}
	return dst.length();
}


size_t ConvertUnicodeString(std::u32string& dst, const std::string& src, bool strict)
{
	size_t src_len(src.length());
	auto siter = src.begin();
	char8_t c(0);
	uint8_t bytes(0);

	while (siter != src.end()) {
		c = *siter;
		bytes = UTF8_BYTES[c];
		if (siter + bytes > src.end()) {
			throw IllegalCharacterError();
		}
		char32_t cp(0);

		switch (bytes) {
		case 5:
			cp = checkStrict(strict);
			cp <<= 6;
		case 4:
			cp = checkStrict(strict);
			cp <<= 6;
		case 3:
			cp += (*siter++) & 0x00FF;
			cp <<= 6;
		case 2:
			cp += (*siter++) & 0x00FF;
			cp <<= 6;
		case 1:
			cp += (*siter++) & 0x00FF;
			cp <<= 6;
		case 0:
			cp += (*siter++) & 0x00FF;
		}
		cp -= UTF8_OFFSETS[bytes];
		dst += cp;
	}
	return dst.length();
}


