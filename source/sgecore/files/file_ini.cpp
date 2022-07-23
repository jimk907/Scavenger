#include "file_ini.h"
#include "utilities/character_utils.h"
#include "utilities/string_utils.h"

#include "vars/varkeyset.h"


namespace sge
{


	IniFile::IniFile()
	{

	}

	IniFile::~IniFile()
	{
		if (file_data)
			delete file_data;
	}

	u32 IniFile::Read(VarKeySet* varset, const std::string& filespec)
	{
		if (!varset)
			return 0;

		FILE* file;
		errno_t err = fopen_s(&file, filespec.c_str(), "rb");
		if (err) {
			// ERROR
			error_str = "Could not open file: " + filespec;
			return 0;
		}

		fseek(file, 0, SEEK_END);
		file_size = ftell(file);
		fseek(file, 0, SEEK_SET);

		file_data = new char[file_size + 1U]; // leave room to terminate the file
		size_t cnt = fread_s(file_data, file_size, 1, file_size, file) == (size_t)file_size;
		fclose(file);

		if (cnt != (size_t)file_size) {
			error_str = "Failed reading contents of file: " + filespec;
			delete file_data;
			file_data = nullptr;
			return 0;
		}
		file_data[file_size] = '\0'; // terminate the file data

		u32 retval = 0;

		if (Parse(varset, file_data, (u32)file_size)) {
			retval = (u32)file_size;
		}

		delete file_data;
		file_data = nullptr;

		return retval;
	}

	bool IniFile::Parse(VarKeySet* varset, char* filedata, u32 count)
	{
		char* p = filedata;
		std::string section;
		std::string key;
		std::string value;
		std::string line;
		bool eq_found = false;
		int  keycount = 0;
		char* start = filedata;

		while (p && ((u32)(p - start) < count)) {
			p = skip_white_space(p);
			if (!*p)
				return (keycount > 0);

			// end of line char - skip and continue
			if (*p == '\r' || *p == '\n') {
				eq_found = false;
				p = find_next_line(p);
				key.clear();
				value.clear();
				continue;
			}

			// comment - skip and continue
			if (*p == ';' || *p == '#') {
				p = find_next_line(p);
				continue;
			}

			// section - get section text and coninue
			if (*p == '[') {
				p++;
				section = get_until_token(p, ']');
				Trim(section);
				continue;
			}

			char set[] = "=\r\n#;\0";
			key = get_until_set(p, set);
			if (*p == '=') {
				eq_found = true;
				p = skip_white_space(++p);
			}
			if (eq_found) {
				if (*p == '"') {
					value = get_quoted_text(p);
				}
				else {
					value = get_until_set(p, set);
				}
			}
			if (!section.empty() && !key.empty() && !value.empty()) {
				Trim(section);
				Trim(key);
				Trim(value);
				varset->set(section, key, value);
				keycount++;
				key.clear();
				value.clear();
			}
		}
		// hopefully we will not exit here
		return (keycount > 0);
	}

	bool IniFile::Write(VarKeySet* varset, const std::string& filespec)
	{
		return false;
	}




} // namespace sge

