#include "file_json.h"


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*/

const char* swsp(const char* p)
{
	while (*p == ' ' || *p == '\t' || *p == 'r' || *p == '\n')
		p++;
	return p;
}

size_t stkn(const char* p, char token)
{
	size_t s(0);
	while (s < JSON_MAX_LEX && p[s] != token)
		s++;
	return s;
}

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*/

JsonDocument::JsonDocument()
{
	null_element.type = JSON_ELEM_VALUE_TYPE::NULLELEM;
}

JsonDocument::~JsonDocument()
{
}

bool JsonDocument::Load(const std::string& path)
{
	FILE* file = fopen(path.c_str(), "r");
	if (!file) {
		fprintf(stderr, "Could not open file: %s\n", path.c_str());
		return false;
	}

	size_t size(0);
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (!size) {
		fprintf(stderr, "File is empty: %s\n", path.c_str());
		return false;
	}

	char* c = (char*)malloc((size + 1) * sizeof(char));
	if (c) {
		c[size] = '\0';
		size_t n(fread(c, sizeof(char), size, file));
		if (n != size) {
			//fprintf(stderr, "Could not input all file contents: %s\n", path.c_str());
			c[n] = '\0'; //return false;
		}
		json_contents = c;
	}
	free(c);

	return Parse(json_contents.c_str());
}



const char* parse_name(const char* cp, std::string& name, bool no_new)
{
	size_t p(0);
	name = "";
	cp = swsp(cp);
	while (*cp) {
		if (cp[p] == '"') {
			p++;
			while (cp[p] != '"' && cp[p] >= ' ')
				p++;
			if (cp[p] == '"') {
				name = std::string(cp).substr(0, p + 1);
				cp += p;
			}
			cp++;
			return cp;
		}
		cp++;
	}
	fprintf(stderr, "Name/value pair is missing a name.\n");
	return cp;
}

const char* parse_value(const char* cp, JsonElement* elem, std::string& value, bool no_new)
{
	size_t p(0);
	value = "";
	while (*cp) {

		if (*cp == '{')
			return parse_object(cp, elem, no_new);

		if (*cp == '[')
			return parse_array(cp, elem, no_new);

		// the value can be a string, a number or a literal
		// it will not be an obect or array.

		cp = swsp(cp);
		if (*cp == '"') {
			p++;
			while (cp[p] != '"' && cp[p] >= ' ')
				p++;
			if (cp[p] == '"') {
				value = std::string(cp).substr(0, p + 1);
				cp += p;
				elem->type = JSON_ELEM_VALUE_TYPE::STRING;
			}
			cp++;
			return cp;
		}
		else {
			while (cp[p] && cp[p] > ' ' && cp[p] != ',' && cp[p] != ']' && cp[p] != '}')
				p++;
			value = std::string(cp).substr(0, p);
			cp += p;
		}
		if (value == "true" || value == "false" || value == "null") {
			elem->type = JSON_ELEM_VALUE_TYPE::LITERAL;
			return cp;
		}

		// test for numeric values
		//std::string num;
		//size_t pn(0);

		char* end(nullptr);
		if (value.find(".") != value.npos) {
			double f = strtod(value.c_str(), &end);
			if (end != value.c_str() && *end == '\0' && f != HUGE_VAL) {
				elem->type = JSON_ELEM_VALUE_TYPE::FLOAT;
				return cp;
			}
		}
		end = nullptr;
		int64_t i = strtol(value.c_str(), &end, 10);
		if (end != value.c_str() && *end == '\0') {
			elem->type = JSON_ELEM_VALUE_TYPE::NUMBER;
			return cp;
		}
		fprintf(stderr, "Undefined value type.\n");
		return cp;

	}
	fprintf(stderr, "Name/value pair is missing a value.\n");
	return cp;
}

const char* parse_object(const char* cp, JsonElement* elem, bool no_new)
{
	JsonElement* this_obj(elem);
	bool bnew(no_new);

	if (!bnew) {
		this_obj = new JsonElement(elem);
		this_obj->parent->children.push_back(this_obj);
	}
	this_obj->type = JSON_ELEM_VALUE_TYPE::OBJECT;
	cp++; // scan-off '{'
	bnew = false;

	while (*cp) {
		if (*cp == '}') {
			elem = this_obj->parent;
			cp++;
			return cp;
		}

		// parse only name/value pairs
		cp = swsp(cp);
		std::string name;
		cp = parse_name(cp, name);
		if (name.empty()) {
			fprintf(stderr, "Name/value pair expected but no name found.\n");
			return cp;
		}
		cp = swsp(cp);
		if (*cp != ':') {
			fprintf(stderr, "Name/value pair expected but no ':' found.\n");
			return cp;
		}
		cp++;

		JsonElement* val_obj(this_obj);
		if (!bnew) {
			val_obj = new JsonElement(this_obj);
			val_obj->parent->children.push_back(val_obj);
		}
		val_obj->name = name;

		cp = swsp(cp);
		// parse out the value
		if (*cp == '{')
			cp = parse_object(cp, val_obj, true);
		else
			if (*cp == '[') {
				cp = parse_array(cp, val_obj, true);
			}
			else {
				cp = parse_value(cp, val_obj, name);
				val_obj->value = name;
			}
		cp = swsp(cp);
		if (*cp == ',') {
			cp++;
			continue;
		}


	} // * cp
	fprintf(stderr, "Object does not contain closing '}'.\n");
	return cp;
}

const char* parse_array(const char* cp, JsonElement* elem, bool no_new)
{
	std::string sval = "";
	JsonElement* this_obj(elem);
	if (!no_new) {
		this_obj = new JsonElement(elem);
		this_obj->parent->children.push_back(this_obj);
	}
	this_obj->type = JSON_ELEM_VALUE_TYPE::ARRAY;

	cp++; // scan-off '['
	cp = swsp(cp);

	while (*cp) {
		if (*cp == ']') {
			elem = this_obj->parent;
			cp++;
			return cp;
		}

		// parse only values
		cp = swsp(cp);

		if (*cp == '{') {
			cp = parse_object(cp, this_obj);
		}
		else if (*cp == '[') {
			cp = parse_array(cp, this_obj);
		}
		else {

			// first create a value element assuming it will be valid
			JsonElement* val_obj = new JsonElement(this_obj);

			cp = parse_value(cp, val_obj, sval);
			if (val_obj->type != JSON_ELEM_VALUE_TYPE::UNDEF) {
				val_obj->value = sval;
				val_obj->parent->children.push_back(val_obj);
			}
			else {
				delete val_obj;
				fprintf(stderr, "Undefined value in array.\n");
			}
		}
		cp = swsp(cp);
		if (*cp == ',') {
			cp++;
			continue;
		}

	} // * cp
	fprintf(stderr, "Array does not contain closing ']'.\n");
	return cp;
}

bool JsonDocument::Parse(const char* contents)
{

	const char* buf = contents;
	//int p(0);
	//char lex[JSON_MAX_LEX];
	if (!root)
		root = new JsonElement(nullptr);
	root->type = JSON_ELEM_VALUE_TYPE::ROOT;
	JsonElement* curr_elem = root;

	// new method

	while (*buf) {

		buf = swsp(buf);
		if (*buf == '{') {
			buf = parse_object(buf, curr_elem);
			continue;
		}
		if (*buf == '[') {
			buf = parse_array(buf, curr_elem);
			continue;
		}

		// only a simple value?
		std::string value;
		if (*buf) {
			buf = parse_value(buf, curr_elem, value);
			if (value.empty()) {
				fprintf(stderr, "Missing value element.\n");
			}
		}

	} // while *buf


	return true;
}

bool JsonDocument::Write(const std::string& out_path, int indent)
{
	FILE* file = 0;
	if (out_path.empty())
		file = stdout;
	else {
		file = fopen(out_path.c_str(), "wb");
		if (!file) {
			fprintf(stderr, "Unable to create file: %s\n", out_path.c_str());
			return false;
		}
		if (setvbuf(file, NULL, _IONBF, 0) == 0)
			printf("Set stream to unbuffered mode\n");
	}

	write_element(file, root, indent, 0);
	fprintf(file, "\n\0\0");
	fflush(file);
	fclose(file);
	return true;
}

JsonElement& JsonDocument::GetElement(const std::string& path)
{
	size_t n(0);
	size_t p(0);
	int ndx(-1);
	std::string name;
	if (path.empty() || root->children.size() == 0) return null_element;
	JsonElement* ref_elem = root;

	while (n < path.length()) {
		p = path.find(":", n);
		name = path.substr(n, p - n);

		// check for array syntax
		size_t pp = name.find(".");
		char* end = nullptr;
		if (pp != name.npos) {
			std::string nbr = name.substr(pp + 1);
			name = name.substr(0, pp);
			ndx = strtol(nbr.c_str(), &end, 10);
			if (!(end != nbr.c_str() && *end == '\0')) {
				ndx = -1;
			}
		}

		if (name != "")
			name = "\"" + name + "\"";
		n = p + 1;
		if (n == 0)
			n = std::string::npos;
		for (auto child : ref_elem->children) {
			if (child->name == name) {
				ref_elem = child;

				if (ndx >= 0) {
					if (ref_elem->children.size() > ndx) {
						ref_elem = ref_elem->children[ndx];
						return *ref_elem;
					}
					else
						ref_elem = &null_element;
				}
				break;
			}
		}
		if (ref_elem->name == name && n >= path.length()) {
			if (ndx >= 0) {
				if (ref_elem->children.size() > ndx) {
					ref_elem = ref_elem->children[ndx];
					return *ref_elem;
				}
				else
					ref_elem = &null_element;
			}
			return *ref_elem;
		}
		if (n >= path.length())
			break;
		continue;
	}
	return null_element;
}

std::string JsonDocument::GetElementValue(const std::string& path)
{
	JsonElement& e = GetElement(path);
	if (e.type != JSON_ELEM_VALUE_TYPE::UNDEF)
		return strip_quotes(e.value);
	return "";
}


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*  Private methods for JsonDocument
*/

void JsonDocument::write_element(FILE* file, JsonElement* elem, int indent, int n)
{
	if (n)
		fprintf(file, "%*s", indent * n, " ");

	if (elem->type == JSON_ELEM_VALUE_TYPE::OBJECT) {
		if (!elem->name.empty())
			fprintf(file, "%s : ", elem->name.c_str());
		fprintf(file, "\n%*s{\n", indent * n, " ");
		for (int i = 0; i < elem->children.size(); i++) {
			write_element(file, elem->children[i], indent, n + 1);
			if (i < elem->children.size() - 1)
				fprintf(file, ", ");
			fprintf(file, "\n");
		}
		//if (n)
		fprintf(file, "%*s}", indent * n, " ");
		fprintf(file, "\n");
		return;
	}
	if (elem->type == JSON_ELEM_VALUE_TYPE::ARRAY) {
		if (!elem->name.empty())
			fprintf(file, "%s : ", elem->name.c_str());
		fprintf(file, "\n%*s[", indent * n, " ");
		//if (!elem->name.empty()) {
		//fprintf(file, "%*s%s ", indent * (n + 1), " ", elem->value.c_str());
		//}
		for (int i = 0; i < elem->children.size(); i++) {
			write_element(file, elem->children[i], indent, 0);// , n + 1);
			if (i < elem->children.size() - 1)
				fprintf(file, ", ");
		}
		//if (n)
		//	fprintf(file, "%*s\n", indent * n, " ");
		fprintf(file, "]\n");
		return;
	}
	if (!elem->name.empty()) {
		fprintf(file, elem->name.c_str());
		if (!elem->value.empty())
			fprintf(file, " : ");
		//fprintf(file, "\n");
	}
	fprintf(file, elem->value.c_str());
	if (elem->type == JSON_ELEM_VALUE_TYPE::ROOT) {
		for (auto child : elem->children) {
			write_element(file, child, indent, n);
		}
	}
}

std::string JsonDocument::strip_quotes(const std::string& s)
{
	std::string r(s);
	size_t n(r.size() - 1);
	if (r[0] == '\"' && r[n] == '\"') {
		r = s.substr(1, n - 1);
	}
	return r;
}

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

JsonElement::JsonElement()
{
}

JsonElement::JsonElement(JsonElement* parent)
{
	this->parent = parent;
}

JsonElement::~JsonElement()
{
	for (auto elem : children)
		delete elem;
	children.clear();
}

