#pragma once


#include "varset.h"


namespace sge
{

	class VarKeySet
	{
	public:
		VarKeySet(bool casesensitive = false)
			: va_case_sens(casesensitive)
		{}

		~VarKeySet()
		{
		}

		void set(const String& key, const String& var, u8 val)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, val);
		}

		void set(const String& key, const String& var, u32 val)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, val);
		}

		void set(const String& key, const String& var, int val)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, val);
		}

		void set(const String& key, const String& var, float val)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, val);
		}

		//void set(const String& key, const String& var, bool val)
		//{
		//	String k(case_convert(key));
		//	var_keyset[k].set(var, val);
		//}

		void set(const String& key, const String& var, const vec2& val)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, val);
		}

		void set(const String& key, const String& var, const vec3& val)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, val);
		}

		void set(const String& key, const String& var, const vec4& val)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, val);
		}

		void set(const String& key, const String& var, const mat3& val)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, val);
		}

		void set(const String& key, const String& var, const mat4& val)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, val);
		}

		void set(const String& key, const String& var, const String str)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set(var, str);
		}

		void set_byprefix(const String& key, const String& var, const String str)
		{
			std::string k(case_convert(key).to_string());
			var_keyset[k].set_byprefix(var, str);
		}

		u8 get(const String& key, const String& var, u8 deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		u32 get(const String& key, const String& var, u32 deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		int get(const String& key, const String& var, int deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		float get(const String& key, const String& var, float deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		//bool get(const String& key, const String& var, bool deflt)
		//{
		//	String k(case_convert(key));
		//	return var_keyset[k].get(var, deflt);
		//}

		vec2 get(const String& key, const String& var, const vec2& deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		vec3 get(const String& key, const String& var, const vec3& deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		vec4 get(const String& key, const String& var, const vec4& deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		mat3 get(const String& key, const String& var, const mat3& deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		mat4 get(const String& key, const String& var, const mat4& deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		String get(const String& key, const String& var, const String deflt)
		{
			std::string k(case_convert(key).to_string());
			return var_keyset[k].get(var, deflt);
		}

		//int getset(VarSet *set, const String &key)
		//{
		//	int iret(0);
		//	if (!set) return iret;

		//	std::map<String, VarSet>::iterator it = var_keyset.find(key);
		//	if (it != var_keyset.end()) {
		//		for (u32 i = 0; i < it->second.size(); i++)
		//			set[i] = it->second;
		//	}
		//}

		std::ostream& print_all(std::ostream& os)
		{
			auto it = var_keyset.begin();
			while (it != var_keyset.end()) {
				os << "[" << it->first << "]" << std::endl;
				print_set(os, it->first);
				os << std::endl;
			}
			return os;
		}

		//std::wostream& print_all(std::wostream& os)
		//{
		//	auto it = var_keyset.begin();
		//	while (it != var_keyset.end()) {
		//		os << L"[" << it->first << L"]" << std::endl;
		//		print_set(os, it->first);
		//		os << std::endl;
		//	}
		//	return os;
		//}

		std::ostream& print_set(std::ostream& os, const String& key)
		{
			std::string k(case_convert(key).to_string());
			auto it = var_keyset.find(k);
			if (it != var_keyset.end())
				it->second.print_all(os);
			return os;
		}

		//std::wostream& print_set(std::wostream& os, const String& key)
		//{
		//	String k(case_convert(key));
		//	auto it = var_keyset.find(k);
		//	if (it != var_keyset.end())
		//		it->second.print_all(os);
		//	return os;
		//}

		std::ostream& print(std::ostream& os, const String& key, const String& var)
		{
			std::string k(case_convert(key).to_string());
			auto it = var_keyset.find(k);
			if (it != var_keyset.end())
				it->second.print(os, var);
			return os;
		}

		//std::ostream& print(std::wostream& os, const String& key, const String& var)
		//{
		//	String k(case_convert(key));
		//	auto it = var_keyset.find(k);
		//	if (it != var_keyset.end())
		//		it->second.print(os, var);
		//	return os;
		//}

		bool key_exists(const String& key)
		{
			std::string k(case_convert(key).to_string());
			auto it = var_keyset.find(k);
			return (it != var_keyset.end());
		}


	private:
		String case_convert(const String& str)
		{
			String s(str);
			if (!va_case_sens)
				s.upper();
			return s;
		}

	protected:
		bool                               va_case_sens;
		std::unordered_map<std::string, VarSet> var_keyset;

	};


} // namespace sge

