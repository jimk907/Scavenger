#include "file_xml.h"
//#include "common/strutils.h"



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// XMLDocument definitiion
//
XMLDocument::XMLDocument()
{

}

XMLDocument::~XMLDocument()
{
	delete root;
}

bool XMLDocument::Load(const std::string& path)
{
	FILE* file = fopen(path.c_str(), "r");
	if (!file) {
		fprintf(stderr, "XML ERR: Could not open file: %s", path.c_str());
		return false;
	}

	size_t size(0);
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (!size) {
		fprintf(stderr, "XML ERR: Empty file: %s\n", path.c_str());
		return false;
	}

	char* txt((char*)malloc((size + 1) * sizeof(char)));
	if (txt) {
		fread(txt, sizeof(char), size, file);
		txt[size] = '\0';
		xml_contents = txt + char(0);
	}
	else {
		fprintf(stderr, "XML ERR: Could not allocate memory (%d)\n", (int)(size + 1));
		return false;
	}

	return Parse(xml_contents);
}

bool XMLDocument::Parse(const std::string& doc_text)
{

	const char* buf(doc_text.c_str());
	char lex[JGE_MAX_XML_LEX];
	size_t p(0); // lex index
	root = new XMLElement(nullptr); // curr_elem;
	root->type = XML_TYPE_ROOT;
	XMLElement* curr_elem = nullptr;  //root;

	bool elem_end = false;

	while (*buf) {

		// start of an element
		if (*buf == '<') {

			// end of an element
			if (*(buf + 1) == '/') {

				// retreive the element text
				if (p) {
					lex[p] = '\0';
					curr_elem->text = lex;
					p = 0;
				}

				buf += 2;
				while (*buf && *buf != '>' && p < JGE_MAX_XML_LEX)
					lex[p++] = *buf++;
				lex[p] = '\0';
				if (curr_elem->tag != lex) {
					fprintf(stderr, "Tag mismatch.\n");
					delete curr_elem;
					return false;
				}
				p = 0;
				elem_end = true;
			}
			else {
				// check for unterminated element
				// e.g. <node>Inner text<node>
				if (p) {
					// make sure this not extraneous white space
					lex[p] = '\0';
					size_t pp(0);
					while (lex[pp] <= ' ') pp++;
					if (pp && (pp != (p + 1))) {
						fprintf(stderr, "New element inside an open element.\n");
						// do not delete curr_node in this case - should clean up 
						// when then funtion exits.
						return false;
					}
					p = 0;
				}
				// create a new element
				if (!elem_end) {
					curr_elem = new XMLElement(curr_elem);
					if (!curr_elem->parent)
						curr_elem->parent = root;
					if (curr_elem->parent)
						curr_elem->parent->children.push_back(curr_elem);
				}
			}

			// declaration element
			if (*(buf + 1) == '?') {
				p = 0;
				buf++;
				while (p < 4 && *buf)
					lex[p++] = *buf++;
				lex[p] = '\0';
				std::string key = "?xml";
				std::string val;
				if (key != lex) {
					fprintf(stderr, "Declaration syntax.\n");
					delete curr_elem;
					return false;
				}
				curr_elem->tag = key;
				while (*buf && *buf != '?') {
					p = 0;
					while (*buf && *buf != '=') {
						if (*buf > ' ')
							lex[p++] = *buf;
						buf++;
					}
					lex[p] = '\0';
					key = lex;
					p = 0;

					while (*buf && *buf != '"')
						buf++;
					buf++;
					while (*buf && *buf != '"')
						lex[p++] = *buf++;
					if (*buf == '"') {
						buf++;
						lex[p] = '\0';
						val = lex;
						p = 0;
					}
					XMLAttribute* attrib = new XMLAttribute;
					attrib->key = key;
					attrib->value = val;
					if (key == "version") {
						xml_version = val;
						curr_elem->attributes.push_back(attrib);
					}
					else if (key == "encoding") {
						xml_encoding = val;
						curr_elem->attributes.push_back(attrib);
					}
					else if (key == "standalone") {
						xml_standalone = val;
						curr_elem->attributes.push_back(attrib);
					}
					else {
						delete attrib;
						fprintf(stderr, "Unknown declaration key: %s\n", key.c_str());
					}
					while (*buf && *buf <= ' ')
						buf++;
				}
				buf++;
				while (*buf && *buf != '>')
					buf++;
				curr_elem->type = XML_TYPE_DECLARATION;
				curr_elem = curr_elem->parent;
			}

			// comment element
			if (*(buf + 1) == '!') {
				buf++;
				p = 0;
				while (p < 3 && *buf)
					lex[p++] = *buf++;
				lex[p] = '\0';
				curr_elem->tag = lex;
				if (curr_elem->tag != "!--") {
					fprintf(stderr, "Bad comment.\n");
					delete curr_elem;
					return false;
				}
				p = 0;
				while (*buf && *buf != '>' && p < JGE_MAX_XML_LEX)
					lex[p++] = *buf++;
				if (*buf != '>') {
					fprintf(stderr, "Comment text not terminated.\n");
					delete curr_elem;
					return false;
				}
				curr_elem->type = XML_TYPE_COMMENT;
				elem_end = true;
				lex[p] = '\0';
				curr_elem->text = lex;
				p = 0;
			}

			// simple element
			if (*(buf + 1) == 'x') {
				std::string s = std::string((buf + 1), 3);
				if (s == "xs:") {

				}
				while (*buf && *buf != '>')
					buf++;
				curr_elem->type = XML_TYPE_SIMPLE;
			}

			// 'normal' tagged elements
			if (*buf == '<') {
				buf++;
				while (*buf && *buf != '>' && *buf > ' ' && *buf != '/')
					lex[p++] = *buf++;
				lex[p] = '\0';
				if (!(*buf)) {
					fprintf(stderr, "End of element tag not found.\n");
					delete curr_elem;
					return false;
				}
				if (*buf == '/') {
					buf++;
					curr_elem->type = XML_TYPE_EMPTY;
					elem_end = true;
				}
				else
					curr_elem->type = XML_TYPE_TAGGED;
				curr_elem->tag = lex;
				p = 0;
			}

			// collect element attributes
			while (*buf != '/' && *buf != '>') {
				// scan off white space
				while (*buf <= ' ' && *buf)
					buf++;
				p = 0;
				while (*buf && *buf != '=' && p < JGE_MAX_XML_LEX)
					lex[p++] = *buf++;
				lex[p] = '\0';
				if (*buf != '=') {
					fprintf(stderr, "Attribute syntax error.\n");
					delete curr_elem;
					return false;
				}
				buf++; // skip the '='

				// create an attribute
				XMLAttribute* curr_attr = new XMLAttribute;
				curr_attr->key = lex;
				p = 0;

				// scan off white space until quote
				while (*buf <= ' ' && *buf)
					buf++;
				if (*buf == '"') {
					p = 0;
					buf++; // skip leading quote
					while (&buf && *buf != '"' && p < JGE_MAX_XML_LEX)
						lex[p++] = *buf++;
					lex[p] = '\0';
					if (*buf != '"') {
						fprintf(stderr, "Attribute value missing a closing quote.\n");
						delete curr_elem;
						delete curr_attr;
						return false;
					}
					curr_attr->value = lex;
					p = 0;
					buf++;
				}
				else {
					fprintf(stderr, "Attribute missing a value.\n");
					delete curr_elem;
					delete curr_attr;
					return false;
				}
				curr_elem->attributes.push_back(curr_attr);
			}
			if (*buf == '/') {
				buf++;
				curr_elem->type = XML_TYPE_EMPTY;
				elem_end = true;
			}
		}

		if (*buf == '>') {
			if (elem_end) {
				curr_elem = curr_elem->parent;
			}
			elem_end = false;
			buf++;
			// scan off all white space
			while (*buf && *buf <= ' ')
				buf++;
			continue;
		}
		if (!elem_end) {
			if (*buf >= ' ' && *buf < 0x80)
				lex[p++] = *buf;
		}
		buf++;
	} // while not done parsing
	return true;
}

bool XMLDocument::Write(const std::string& out_path, int indent)
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

	// write a declaration element
	fprintf(file, "<?xml version=\"%s\" encoding=\"%s\" standalone=\"%s\"?>\n",
			xml_version.empty() ? "1.0" : xml_version.c_str(),
			xml_encoding.empty() ? "UTF-8" : xml_encoding.c_str(),
			xml_standalone.empty() ? "no" : xml_standalone.c_str());

	bool b = print_element(file, root, indent, 0);
	fprintf(file, "\0\0\0\0");
	fflush(file);
	fclose(file);
	return true;
}

bool XMLDocument::print_element(FILE* file, XMLElement* elem, int indent, int n)
{
	for (auto e : elem->children) {

		if (n)
			fprintf(file, "%*s", indent * n, " ");


		if (e->type == XML_TYPE_COMMENT) {
			fprintf(file, "<!--%s>\n", e->text.c_str());
		}
		else if (e->type != XML_TYPE_DECLARATION) {
			fprintf(file, "<%s", e->tag.c_str());
			for (auto a : e->attributes) {
				fprintf(file, " %s=\"%s\"", a->key.c_str(), a->value.c_str());
			}
			if (e->type == XML_TYPE_EMPTY)
				fprintf(file, "/>\n");
			else {
				fprintf(file, ">");
				if (!e->children.size())
					fprintf(file, "%s</%s>\n", e->text.c_str(), e->tag.c_str());
				else {
					fprintf(file, "\n");
					print_element(file, e, indent, n + 1);
					if (n)
						fprintf(file, "%*s", indent * n, " ");
					fprintf(file, "</%s>\n", e->tag.c_str());
				}
			}
		}
	}
	return false;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// XMLElement definitiion
//
XMLElement::XMLElement()
{
}

XMLElement::XMLElement(XMLElement* owner)
{
	parent = owner;
}

XMLElement::~XMLElement()
{
	for (auto node : children)
		delete node;
	children.clear();
	for (auto attr : attributes)
		delete attr;
	attributes.clear();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// XMLAttribute definition
//
