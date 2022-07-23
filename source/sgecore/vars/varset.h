#pragma once


#include "vardef.h"



namespace sge
{

	// !!!!!NOTE!!!!!
	// This version of the VarSet class eliminates 'bool' var types do to
	// the fact strings will be interpreted as bools, however, 'bool' types
	// can be returned.
	class VarSet
	{
	public:
		typedef std::unordered_map<std::string, Var*>::iterator iterator;

	public:
		inline VarSet(bool case_sensitive = false, const String& name = "");
		inline ~VarSet();

		inline void set(const String& name, int v);
		inline void set(const String& name, u32 v);
		inline void set(const String& name, char v);
		inline void set(const String& name, u8 v);
		//inline void set(const String& name, bool v);
		inline void set(const String& name, float v);
		//inline void set(const String& name, double v);
		inline void set(const String& name, const vec2& v);
		inline void set(const String& name, const vec3& v);
		inline void set(const String& name, const vec4& v);
		inline void set(const String& name, const mat3& v);
		inline void set(const String& name, const mat4& v);
		inline void set(const String& name, const String& v);
		inline void set_byprefix(const String& name, const String& v);

		inline int    get_int(const String& name);
		inline u32    get_uint(const String& name);
		inline char   get_char(const String& name);
		inline u8     get_ubyte(const String& name);
		inline bool   get_bool(const String& name);
		inline float  get_float(const String& name);
		//inline double get_double(const String& name);
		inline vec2   get_vec2(const String& name);
		inline vec3   get_vec3(const String& name);
		inline vec4   get_vec4(const String& name);
		inline mat3   get_mat3(const String& name);
		inline mat4   get_mat4(const String& name);
		inline String get_string(const String& name);

		inline int    get(const String& name, int deflt);
		inline u32    get(const String& name, u32 deflt);
		inline char   get(const String& name, char deflt); 
		inline u8     get(const String& name, u8 deflt);
		//inline bool   get(const String& name, bool deflt);
		inline float  get(const String& name, float deflt);
		//inline double get(const String& name, double deflt);
		inline vec2   get(const String& name, const vec2& deflt);
		inline vec3   get(const String& name, const vec3& deflt);
		inline vec4   get(const String& name, const vec4& deflt);
		inline mat3   get(const String& name, const mat3& deflt);
		inline mat4   get(const String& name, const mat4& deflt);
		inline String get(const String& name, const String& deflt);

		inline std::ostream& print_all(std::ostream& os);
		//inline std::wostream& print_all(std::wostream& os);
		inline std::ostream& print(std::ostream& os, const String& var);
		//inline std::wostream& print(std::wostream& os, const String& var);
		inline String to_string(const String& name);

		inline Var& operator()(const String& name);

		inline iterator first();
		inline iterator next();
		inline iterator end();

	private:
		String convert_case(const String& str)
		{
			String s(str);
			if (!va_case_sens)
				s.upper();
			return s;
		}


	private:
		String                                          va_name;
		bool                                            va_case_sens;
		std::unordered_map<std::string, Var*>           va_map;
		std::unordered_map<std::string, Var*>::iterator va_it;
	};


} // namespace sge

namespace sge
{

	VarSet::VarSet(bool case_sensitive, const String& sname)
		: va_name(sname)
		, va_case_sens(case_sensitive)
		, va_it(va_map.end())
	{
	}

	VarSet::~VarSet()
	{
		auto it = va_map.begin();
		while (it != va_map.end())
			delete (Var*)(it++)->second;
		va_map.clear();
	}

	void VarSet::set(const String& name, int v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	void VarSet::set(const String& name, u32 v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	void VarSet::set(const String& name, char v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}
	void VarSet::set(const String& name, u8 v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	//void VarSet::set(const String& name, bool v)
	//{
	//	String nam(convert_case(name));
	//	if (va_map.find(nam) != va_map.end()) {
	//		*va_map[nam] = v;
	//	} else {
	//		va_map[nam] = new Var(v);
	//	}
	//}

	void VarSet::set(const String& name, float v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	//void VarSet::set(const String& name, double v)
	//{
	//	String nam(convert_case(name));
	//	if (va_map.find(nam) != va_map.end()) {
	//		*va_map[nam] = v;
	//	} else {
	//		va_map[nam] = new Var(v);
	//	}
	//}

	void VarSet::set(const String& name, const vec2& v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	void VarSet::set(const String& name, const vec3& v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	void VarSet::set(const String& name, const vec4& v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	void VarSet::set(const String& name, const mat3& v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	void VarSet::set(const String& name, const mat4& v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	void VarSet::set(const String& name, const String& v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			va_map[nam] = new Var(v);
		}
	}

	void VarSet::set_byprefix(const String& name, const String& v)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			*va_map[nam] = v;
		} else {
			if (nam.length() > 2) {
				String pre(nam.substr(0, 2));
				if (pre == "i_" || pre == "I_")
					va_map[nam] = new Var(toInt(v));
				else if (pre == "u_" || pre == "U_")
					va_map[nam] = new Var(toUint(v));
				else if (pre == "c_" || pre == "C_")
					va_map[nam] = new Var(toInt(v));
				else if (pre == "v_" || pre == "V_")
					va_map[nam] = new Var(toUint(v));
				else if (pre == "b_" || pre == "B_")
					va_map[nam] = new Var(toInt(v));
				else if (pre == "f_" || pre == "F_")
					va_map[nam] = new Var(toFloat(v));
				//else if (pre == "d_" || pre == "D_")
				//	va_map[nam] = new Var((double)v.to_real()));
				else if (pre == "s_" || pre == "S_")
					va_map[nam] = new Var(v);
				else
					va_map[nam] = new Var(v);
			}
		}
	}

	int VarSet::get_int(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_int();
	}

	u32 VarSet::get_uint(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_uint();
	}

	char VarSet::get_char(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_char();
	}

	u8 VarSet::get_ubyte(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_ubyte();
	}

	bool VarSet::get_bool(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_bool();
	}

	float VarSet::get_float(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_float();
	}

	//double VarSet::get_double(const String& name)
	//{
	//	String nam(convert_case(name));
	//	return va_map[nam]->get_double();
	//}

	vec2 VarSet::get_vec2(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_vec2();
	}

	vec3 VarSet::get_vec3(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_vec3();
	}

	vec4 VarSet::get_vec4(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_vec4();
	}

	mat3 VarSet::get_mat3(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_mat3();
	}

	mat4 VarSet::get_mat4(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_mat4();
	}

	String VarSet::get_string(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		return va_map[nam]->get_string();
	}

	int VarSet::get(const String& name, int deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	u32 VarSet::get(const String& name, u32 deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	char VarSet::get(const String& name, char deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	u8  VarSet::get(const String& name, u8 deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	//bool   VarSet::get(const String& name, bool deflt)
	//{
	//	String nam(convert_case(name));
	//	if (va_map.find(nam) != va_map.end()) {
	//		return va_map[nam]->get(deflt);
	//	} else {
	//		va_map[nam] = new Var(deflt);
	//		return deflt;
	//	}
	//}

	float  VarSet::get(const String& name, float deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	//double VarSet::get(const String& name, double deflt)
	//{
	//	String nam(convert_case(name));
	//	if (va_map.find(nam) != va_map.end()) {
	//		return va_map[nam]->get(deflt);
	//	} else {
	//		va_map[nam] = new Var(deflt);
	//		return deflt;
	//	}
	//}

	vec2 VarSet::get(const String& name, const vec2& deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	vec3 VarSet::get(const String& name, const vec3& deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	vec4 VarSet::get(const String& name, const vec4& deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	mat3 VarSet::get(const String& name, const mat3& deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	mat4 VarSet::get(const String& name, const mat4& deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	String VarSet::get(const String& name, const String& deflt)
	{
		std::string nam(convert_case(name).to_string());
		if (va_map.find(nam) != va_map.end()) {
			return va_map[nam]->get(deflt);
		} else {
			va_map[nam] = new Var(deflt);
			return deflt;
		}
	}

	std::ostream& VarSet::print_all(std::ostream& os)
	{
		String key;
		auto it = va_map.begin();
		while (it != va_map.end()) {
			key = it->first;
			os << key.to_string() << "=" << (it->first) << std::endl;
		}
		return os;
	}

	//std::wostream& VarSet::print_all(std::wostream& os)
	//{
	//	auto it = va_map.begin();
	//	while (it != va_map.end())
	//		os << it->first << "=" << to_string(it->first) << std::endl;
	//	return os;
	//}

	std::ostream& VarSet::print(std::ostream& os, const String& var)
	{
		os << var.to_string();
		return os;
	}

	//std::wostream& VarSet::print(std::wostream& os, const String& var)
	//{
	//	os << to_string(var);
	//	return os;
	//}


	String VarSet::to_string(const String& name)
	{
		String sret("");
		std::string nam(convert_case(name).to_string());
		auto it = va_map.find(nam);
		if (it != va_map.end()) {
			switch (it->second->get_type()) {
				case VAR_UINT:
					sret = std::to_string(it->second->get_uint());
				case VAR_INT:
					sret = std::to_string(it->second->get_int());
				case VAR_FLOAT:
					sret = std::to_string(it->second->get_float());
				case VAR_STRING:
					sret = it->second->get_string();
			}
		}
		return sret;
	}


	Var& VarSet::operator()(const String& name)
	{
		std::string nam(convert_case(name).to_string());
		auto it = va_map.find(nam);
		return *it->second;
	}

	VarSet::iterator VarSet::first()
	{
		va_it = va_map.begin();
		return va_it;
	}

	VarSet::iterator VarSet::next()
	{
		if (++va_it != va_map.end()) {
			return va_it;
		}
		return va_it;
	}

	VarSet::iterator VarSet::end()
	{
		return va_map.end();
	}

} // namespace sge

