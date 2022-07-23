
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdarg>

#include <string>
#include <vector>
#include <iostream>

//#include <msxml6.h>
//#pragma import(lib, "msxml6.dll")
////using namespace MSXML6;
//// Macro that calls a COM method returning HRESULT value.
//#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0)
//
//// Macro to verify memory allcation.
//#define CHK_ALLOC(p)        do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0)
//
//// Macro that releases a COM object if not NULL.
//#define SAFE_RELEASE(p)     do { if ((p)) { (p)->Release(); (p) = NULL; } } while(0)\

#define JGE_MAX_XML_LEX 1024

constexpr int XML_TYPE_UNDEFINED = -1;
constexpr int XML_TYPE_TAGGED = 0;
constexpr int XML_TYPE_COMMENT = 1;
constexpr int XML_TYPE_DECLARATION = 2;
constexpr int XML_TYPE_SIMPLE = 3;
constexpr int XML_TYPE_EMPTY = 4;
constexpr int XML_TYPE_ATTRIBUTE = 5;
constexpr int XML_TYPE_ROOT = 99;

struct XMLAttribute
{
	std::string key;
	std::string value;
};

struct XMLElement
{
	XMLElement();
	XMLElement(XMLElement* owner);
	~XMLElement();
	int type = XML_TYPE_UNDEFINED;
	std::string tag;
	std::string text;

	XMLElement* parent = nullptr;

	std::vector<XMLAttribute*> attributes;
	std::vector<XMLElement*> children;
};

class XMLDocument
{
public:
	XMLDocument();
	~XMLDocument();

	bool Load(const std::string& path);
	bool Parse(const std::string& doc_text);
	bool Write(const std::string& out_path, int indent = 2);
	XMLElement* root = nullptr;

private:
	bool print_element(FILE* file, XMLElement* elem, int indent, int n);

private:
	std::string xml_version;
	std::string xml_encoding;
	std::string xml_standalone;
	std::string xml_contents;

};

