#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>


constexpr size_t JSON_MAX_LEX = 1024;


enum class JSON_ELEM_VALUE_TYPE : int
{
	UNDEF,
	ROOT,
	OBJECT,
	ARRAY,
	STRING,
	NUMBER,
	FLOAT,
	LITERAL,
	VALUE,
	NULLELEM,
	//KEYVAL,
	//VALUE,
};

//enum class JSON_VALUE_TYPE : int
//{
//	UNDEF,
//	STRING,
//	FLOAT,
//	NUMBER,
//	BOOL,
//	NULLVAL,
//};

struct JsonElement
{
	JSON_ELEM_VALUE_TYPE type = JSON_ELEM_VALUE_TYPE::UNDEF;
	JsonElement();
	JsonElement(JsonElement* parent);
	virtual ~JsonElement();
	std::string name = "";
	std::string value = "";
	JsonElement* parent = nullptr;
	std::vector<JsonElement*> children;
};


//struct JsonValue : public JsonElement
//{
//	JsonValue(JsonElement* parent);
//	~JsonValue();
//	JSON_VALUE_TYPE type = JSON_VALUE_TYPE::UNDEF;
//	std::string     key;
//	std::string     sval = "";
//	bool            bval = false;
//	double          fval = 0.0;
//	int64_t         nval = 0;
//};

const char* parse_name(const char* cp, std::string& name, bool no_new = false);
const char* parse_value(const char* cp, JsonElement* elem, std::string& value, bool no_new = false);
const char* parse_object(const char* cp, JsonElement* elem, bool no_new = false);
const char* parse_array(const char* cp, JsonElement* elem, bool no_new = false);


class JsonDocument
{
public:
	JsonDocument();
	~JsonDocument();
	bool Load(const std::string& path);
	bool Parse(const char* json_contents);
	bool Write(const std::string& out_path, int indent = 2);

	JsonElement& GetElement(const std::string& path);
	std::string GetElementValue(const std::string& path);

	JsonElement* root = nullptr;

private:
	void write_element(FILE* file, JsonElement* elem, int indent, int level);
	std::string strip_quotes(const std::string& s);

private:
	std::string json_contents;
	JsonElement null_element;
};

