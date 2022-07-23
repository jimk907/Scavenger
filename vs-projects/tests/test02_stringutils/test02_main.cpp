#include "sge_defines.h"
#include "log/logger.h"
#include "utilities/gen_utils.h"
#include "utilities/string_utils.h"
#include "string/unicode.h"

using namespace sge;

 

std::string bool2str(bool b)
{
	if (b)
		return std::string("true");
	else
		return std::string("false");
}

int main(int argc, char* argv[])
{
	SGE_MEM_LEAK_CHECK;

	std::u32string u32test = U"abc不亦Даלו"; // test string of random glyphs
	std::wstring   uc2test = L"不亦abcДа";
	size_t n(0);

	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test unicode conversions **");
	std::u32string us32;
	std::string us8;
	n = ConvertUnicodeString(us8, u32test);
	n = ConvertUnicodeString(us32, us8);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "us32 == u32test? : %s", us32 == u32test ? "TRUE" : "FALSE");
	std::wstring usw;
	us32.clear();
	n = ConvertUnicodeString(usw, u32test);
	n = ConvertUnicodeString(us32, usw);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "wstr == u32test? : %s", us32 == u32test ? "TRUE" : "FALSE");
	std::u16string us16;
	us32.clear();
	n = ConvertUnicodeString(us16, u32test);
	n = ConvertUnicodeString(us32, us16);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "us16 == u32test? : %s", us32 == u32test ? "TRUE" : "FALSE");

	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "\n** Press any key to continue... **");
	WaitKey();


	// conStructorS & equateS for String typeS
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test constructors **");
	String s0("test1 s0"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s0 = %s", s0.to_string().c_str());
	String s1(L"test1 s1"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s1 = %s", s1.to_string().c_str());
	String s2(std::string("test1 s2")); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s2 = %s", s2.to_string().c_str());
	String s3(std::wstring(L"test1 s3")); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s3 = %s", s3.to_string().c_str());
	String s4(std::u16string(u"test1 u16")); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s4 = %s", s4.to_string().c_str());
	String s5(std::u32string(U"test1 u32")); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s5 = %s", s5.to_string().c_str());
	String s6(s0); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s6 = %s", s6.to_string().c_str());
	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test Equates **");
	String T0 = "test2 T0"; LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T0 = %s", T0.to_string().c_str());
	String T1 = L"test2 T1"; LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T1 = %s", T1.to_string().c_str());
	String T2 = std::string("test2 T2"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T2 = %s", T2.to_string().c_str());
	String T3 = std::wstring(L"test2 T3"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T3 = %s", T3.to_string().c_str());
	String T4 = std::u16string(u"test2 u16"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T4 = %s", T4.to_string().c_str());
	String T5 = std::u32string(U"test2 u32"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T5 = %s", T5.to_string().c_str());
	String T6 = s0; LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T6 = %s", T6.to_string().c_str());
	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test concatenation **");
	T0 += " + test3 T0"; LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T0 = %s", T0.to_string().c_str());
	T1 += L" + test3 T1"; LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T1 = %s", T1.to_string().c_str());
	T2 += std::string(" + test3 T2"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T2 = %s", T2.to_string().c_str());
	T3 += std::wstring(L" + test3 T3"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T3 = %s", T3.to_string().c_str());
	T4 += std::u16string(u" + test3 u16"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T4 = %s", T4.to_string().c_str());
	T5 += std::u32string(U" + test3 u32"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T5 = %s", T5.to_string().c_str());
	T6 += s0; LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T6 = %s", T6.to_string().c_str());
	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test const concatentation **");
	T0 = s0 + " + test4 T0"; LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T0 = %s", T0.to_string().c_str());
	T1 = s1 + L" + test4 T1"; LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T1 = %s", T1.to_string().c_str());
	T2 = s2 + std::string(" + test4 T2"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T2 = %s", T2.to_string().c_str());
	T3 = s3 + std::wstring(L" + test4 T3"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T3 = %s", T3.to_string().c_str());
	T4 = s4 + std::u16string(u" + test4 T4"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T4 = %s", T4.to_string().c_str());
	T5 = s5 + std::u32string(U" + test4 T5"); LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T5 = %s", T5.to_string().c_str());
	T6 = s6 + s0; LOGGER::ATTN_LOG(SgeLogLevel::INFO, "T6 = %s", T6.to_string().c_str());

	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test bool equivalence true **");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s0 == chars     ? %s", bool2str(s0 == "test1 s0").c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s1 == wchars    ? %s", bool2str(s1 == L"test1 s1").c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s2 == string    ? %s", bool2str(s2 == std::string("test1 s2")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s3 == wstring   ? %s", bool2str(s3 == std::wstring(L"test1 s3")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s4 == u16string ? %s", bool2str(s4 == std::u16string(u"test1 u16")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s5 == u32string ? %s", bool2str(s5 == std::u32string(U"test1 u32")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s6 == String ? %s", bool2str(s6 == String("test1 s0")).c_str());
	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test bool equivalence false **");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s0 == chars     ? %s", bool2str(s0 == "test s0").c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s1 == wchars    ? %s", bool2str(s1 == L"test s1").c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s2 == string    ? %s", bool2str(s2 == std::string("test s2")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s3 == wstring   ? %s", bool2str(s3 == std::wstring(L"test s3")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s4 == u16string ? %s", bool2str(s4 == std::u16string(u"test u16")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s5 == u32string ? %s", bool2str(s5 == std::u32string(U"test u32")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s6 == String ? %s", bool2str(s6 == String("test1 T0")).c_str());
	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test bool non-equivalence true **");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s0 != chars     ? %s", bool2str(s0 != "test s0").c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s1 != wchars    ? %s", bool2str(s1 != L"test s1").c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s2 != string    ? %s", bool2str(s2 != std::string("test s2")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s3 != wstring   ? %s", bool2str(s3 != std::wstring(L"test s3")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s4 != u16string ? %s", bool2str(s4 != std::u16string(u"test u16")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s5 != u32string ? %s", bool2str(s5 != std::u32string(U"test u32")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s6 != String ? %s", bool2str(s6 != String("test1 T0")).c_str());
	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test bool non-equivalence false **");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s0 != chars     ? %s", bool2str(s0 != "test1 s0").c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s1 != wchars    ? %s", bool2str(s1 != L"test1 s1").c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s2 != string    ? %s", bool2str(s2 != std::string("test1 s2")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s3 != wstring   ? %s", bool2str(s3 != std::wstring(L"test1 s3")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s4 != u16string ? %s", bool2str(s4 != std::u16string(u"test1 u16")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s5 != u32string ? %s", bool2str(s5 != std::u32string(U"test1 u32")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s6 != String ? %s", bool2str(s6 != String("test1 s0")).c_str());
	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test greater/less comparison operators true **");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "U16string < String ? %s", bool2str(String("abc") < String("acc")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "U16string > String ? %s", bool2str(String("acc") > String("abc")).c_str());
	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test greater/less comparison operators false **");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "U16string > String ? %s", bool2str(String("abc") > String("acc")).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "U16string < String ? %s", bool2str(String("acc") < String("abc")).c_str());
	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test index operators **");
	s0 = "abcdef";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "wchar_t \"abcdef\" at index 3 = %c", s0[3]);
	const wchar_t chr(s0[0]);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "const wchar_t \"abcdef\" at index 0 = %c", chr);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test size methods **");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Size of s0 = %i", s0.size());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Length of s0 = %i", s0.length());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s0.Empty() = %s", bool2str(s0.empty()).c_str());
	s0.clear();
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Length of s0 after Clear() = %i", s0.length());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "s0.Empty() = %s", bool2str(s0.empty()).c_str());

	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test misc methods **");
	s0 = "abcdef";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Substr(\"abcdef\", 2) = %s", s0.substr(2).to_string().c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Substr(\"abcdef\", 2, 2) = %s", s0.substr(2, 2).to_string().c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Upper(\"abcdef\", 2) = %s", s0.upper().to_string().c_str());
	s0 = s0.upper();
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Lower(\"ABCDEF\", 2) = %s", s0.lower().to_string().c_str());
	// also verifies friend method of rval concatenation
	s0 = "  1 2 3 " + s0;
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "LTrim(\"  1 2 3 abcdef\") = \"%s\"", s0.ltrim().to_string().c_str());
	s0 = "abcdef 1 2 3  ";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "RTrim(\"abcdef 1 2 3  \") = \"%s\"", s0.rtrim().to_string().c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Erase(\"abcdef 1 2 3\", 1, 3) = \"%s\"", s0.erase(1, 3).to_string().c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Test str to num conversion methods **");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "To_i32(\"-123\") = %i", String("-123").to_i32());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "To_i32(\"123.4\") = %i", String("123.4").to_i32());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "To_i32(\"123.6\") = %i", String("123.6").to_i32());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "To_u32(\"123.4\") = %u", String("123.4").to_u32());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "To_u32(\"123\") = %u", String("123").to_u32());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "To_u32(\"0x123\") = %u", String("0x123").to_u32());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "To_float(\"123.123456789\") = %4.4f", String("123.123456789").to_f32());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "To_double(\"123.123456789\") = %4.9f", String("123.123456789").to_f64());

	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "\n** Press any key to continue... **");
	WaitKey();

	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Tests for string utilities **\n");
	String s("-123");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsInt(\"-123\") : %s", bool2str(IsInt(s)).c_str());
	s = "1.23";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsInt(\"1.23\") : %s", bool2str(IsInt(s)).c_str());
	s = "3.12";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsFloat(\"3.12\") : %s", bool2str(IsReal(s)).c_str());
	s = "1e-2";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsFloat(\"1e-2\") : %s", bool2str(IsReal(s)).c_str());
	s = "182";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsFloat(\"182\") : %s", bool2str(IsReal(s)).c_str());
	s = "0x123";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsUint(\"0x123\") : %s", bool2str(IsUint(s)).c_str());
	s = "-123";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsUint(\"-123\") : %s", bool2str(IsUint(s)).c_str());
	s = "123";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsUint(\"123\") (default to int) : %s", bool2str(IsUint(s)).c_str());
	s = "false";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsBool(\"false\") : %s", bool2str(IsBool(s)).c_str());
	s = "TRUE";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsBool(\"TRUE\") : %s", bool2str(IsBool(s)).c_str());
	s = "yes";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "IsBool(\"yes\") : %s", bool2str(IsBool(s)).c_str());

	LOGGER::LINE_LOG(1);
	s = "123";
	i32 i(0);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Str2Int(\"123\") converted? : %s", bool2str(Str2Int(s, i)).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  Function returns : %i", i);
	s = "0x123";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Str2Int(\"0x123\") converted? : %s", bool2str(Str2Int(s, i)).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  Function returns : %i", i);
	s = "false";
	bool b(false);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Str2Bool(\"false\") converted? : %s", bool2str(Str2Bool(s, b)).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  Function returns : %s", bool2str(b).c_str());
	s = "true";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Str2Bool(\"true\") converted? : %s", bool2str(Str2Bool(s, b)).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  Function returns : %s", bool2str(b).c_str());
	s = "1";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Str2Bool(\"1\") converted? : %s", bool2str(Str2Bool(s, b)).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  Function returns : %s", bool2str(b).c_str());
	s = "0";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Str2Bool(\"0\") converted? : %s", bool2str(Str2Bool(s, b)).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  Function returns : %s", bool2str(b).c_str());
	s = "1.23";
	f32 f(0);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Str2Float(\"1.23\") converted? : %s", bool2str(Str2Real(s, f)).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  Function returns : %f", f);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "toHexStr(0xff80) : %s", toHexString(u32(0xff80)).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "toHexStr(1234) : %s", toHexString(1234).c_str());

	LOGGER::LINE_LOG(1);
	s = "  \tTest";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "A+Ltrim(\" \\tTest\")+B : A%sB", LTrim(s.to_string()).c_str());
	s = "Test \t";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "A+Rtrim(\"Test \\t\")+B : A%sB", RTrim(s.to_string()).c_str());
	s = "  Test \t";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "A+Trim(\"  Test \\t\")+B : A%sB", Trim(s.to_string()).c_str());

	LOGGER::LINE_LOG(1);
	s = "1234567890";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Right(\"1234567890\", 3) : %s", Right(s.to_string(), 3).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Left(\"1234567890\", 3) : %s", Left(s.to_string(), 3).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Mid(\"1234567890\", 3, 4) : %s", Mid(s.to_string(), 3, 4).c_str());
	s = "AbCdEf";
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "toUpper(\"%s\") : %s", s.to_string().c_str(), toUpper(s.to_string()).c_str());
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "toLower(\"%s\") : %s", s.to_string().c_str(), toLower(s.to_string()).c_str());

	LOGGER::LINE_LOG(1);
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "** Tests tokenization functions **\n");
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  src string = \"one, two, three\" to String[]");
	String sary[3];
	int it(Tokenize("one, two, three", sary, 3));
	for (i = 0; i < it; i++) {
		LOGGER::ATTN_LOG(SgeLogLevel::NONE, "    Token %i = %s", i + 1, sary[i].to_char());
	}

	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  src string = \"one, two, three\" to vector<String>");
	std::vector<String> svec;
	it = Tokenize("one, two, three", svec);
	for (i = 0; i < it; i++) {
		LOGGER::ATTN_LOG(SgeLogLevel::NONE, "    Token %i = %s", i + 1, svec[i].to_char());
	}

	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  src string = \"1.11, 22.2, .333\" to vector<f32>");
	std::vector<f32> fvec;
	it = Tokenize("1.11,22.2, .333", fvec);
	for (i = 0; i < it; i++) {
		LOGGER::ATTN_LOG(SgeLogLevel::NONE, "    Token %i = %f", i + 1, fvec[i]);
	}

	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  src string = \"111, 222, 333\" to vector<i32>");
	std::vector<i32> ivec;
	it = Tokenize("111,222, 333", ivec);
	for (i = 0; i < it; i++) {
		LOGGER::ATTN_LOG(SgeLogLevel::NONE, "    Token %i = %i", i + 1, ivec[i]);
	}

	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "  src string = \"0x111, 0x222, 0x333\" to vector<u32>");
	std::vector<u32> uvec;
	it = Tokenize("0x111,0x222, 0x333", uvec);
	for (i = 0; i < it; i++) {
		LOGGER::ATTN_LOG(SgeLogLevel::NONE, "    Token %i = %u", i + 1, uvec[i]);
	}


	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "\n** Press any key to continue... **");
	WaitKey();

	return 0;
}
