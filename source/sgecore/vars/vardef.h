#pragma once



#include "sge_defines.h"
#include  "string/string.h"
#include "utilities/string_utils.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat3.h"
#include "math/mat4.h"


constexpr u8 VAR_VOID   = 0;			// ""
constexpr u8 VAR_INT    = 1;			// "i_"
constexpr u8 VAR_UINT   = 2;			// "u_"
constexpr u8 VAR_FLOAT  = 3;			// "f_"
constexpr u8 VAR_STRING = 4;			// "s_"
constexpr u8 VAR_VEC2   = 5;
constexpr u8 VAR_VEC3   = 6;
constexpr u8 VAR_VEC4   = 7;
constexpr u8 VAR_MAT3   = 8;
constexpr u8 VAR_MAT4   = 9;



namespace sge
{


	class Var
	{
	public:
		inline Var();
		inline Var(int v);
		inline Var(u32 v);
		inline Var(float v);
		inline Var(const String& s);
		inline Var(const vec2& v);
		inline Var(const vec3& v);
		inline Var(const vec4& v);
		inline Var(const mat3& v);
		inline Var(const mat4& v);

		inline Var(const Var& copy);
		inline virtual ~Var();

		inline void set(int v);
		inline void set(u32 v);
		inline void set(float v);
		inline void set(const String& s);
		inline void set(const vec2& v);
		inline void set(const vec3& v);
		inline void set(const vec4& v);
		inline void set(const mat3& v);
		inline void set(const mat4& v);
		inline void set(const Var& copy);

		inline void set_int(const String& v);
		inline void set_uint(const String& v);
		inline void set_float(const String& v);
		inline void set_vec2(const String& v);
		inline void set_vec3(const String& v);
		inline void set_vec4(const String& v);
		inline void set_mat3(const String& v);
		inline void set_mat4(const String& v);
		inline void set_string(const String& v);

		inline int    get_int() const;
		inline u32    get_uint() const;
		inline char   get_char() const;
		inline u8     get_ubyte() const;
		inline bool   get_bool() const;
		inline float  get_float() const;
		inline double get_double() const;
		inline vec2   get_vec2() const;
		inline vec3   get_vec3() const;
		inline vec4   get_vec4() const;
		inline mat3   get_mat3() const;
		inline mat4   get_mat4() const;
		inline String get_string() const;

		inline int    get(int deflt);
		inline u32    get(u32 deflt);
		inline float  get(float deflt);
		inline vec2   get(const vec2& deflt);
		inline vec3   get(const vec3& deflt);
		inline vec4   get(const vec4& deflt);
		inline mat3   get(const mat3& deflt);
		inline mat4   get(const mat4& deflt);
		inline String get(const String& deflt);

		inline bool get(int* dst);
		inline bool get(u32* dst);
		inline bool get(float* dst);
		inline bool get(vec2* dst);
		inline bool get(vec3* dst);
		inline bool get(vec4* dst);
		inline bool get(mat3* dst);
		inline bool get(mat4* dst);


		inline u8 get_type() const;
		inline int   get_component_count() const;

	private:
		inline void destroy();

		union {
			void* vvar;
			int* ivar;
			u32* uvar;
			real* rvar;
			String* svar;
		};
		int   components;
		u8 type;
	};


	inline Var::Var()
		: vvar(nullptr)
		, components(0)
		, type(VAR_VOID)
	{
	}

	inline Var::Var(int v)
		: Var()
	{
		set(v);
	}

	inline Var::Var(u32 v)
		: Var()
	{
		set(v);
	}

	inline Var::Var(float v)
		: Var()
	{
		set(v);
	}

	inline Var::Var(const String& s)
		: Var()
	{
		set(s);
	}

	inline Var::Var(const vec2& v)
		: Var()
	{
		set(v);
	}

	inline Var::Var(const vec3& v)
		: Var()
	{
		set(v);
	}

	inline Var::Var(const vec4& v)
		: Var()
	{
		set(v);
	}

	inline Var::Var(const mat3& m)
		: Var()
	{
		set(m);
	}

	inline Var::Var(const mat4& m)
		: Var()
	{
		set(m);
	}

	inline Var::Var(const Var& copy)
		: Var()
	{
		set(copy);
	}

	inline Var::~Var()
	{
		destroy();
	}

	inline void Var::destroy()
	{
		switch (type) {
			case VAR_INT:
				delete ivar;
				break;
			case VAR_UINT:
				delete uvar;
				break;
			case VAR_FLOAT:
				delete rvar;
				break;
			case VAR_VEC2:
			case VAR_VEC3:
			case VAR_VEC4:
			case VAR_MAT3:
			case VAR_MAT4:
				delete[] rvar;
				break;
			case VAR_STRING:
				delete svar;
		}
	}

	inline u8 Var::get_type() const
	{
		return type;
	}

	inline int Var::get_component_count() const
	{
		return components;
	}

	inline void Var::set(int v)
	{
		if (type)
			destroy();
		ivar = new int(v);
		type = VAR_INT;
	}

	inline void Var::set(u32 v)
	{
		if (type)
			destroy();
		uvar = new u32(v);
		type = VAR_UINT;
	}

	inline void Var::set(float v)
	{
		if (type)
			destroy();
		rvar = new float(v);
		type = VAR_FLOAT;
	}

	inline void Var::set(const vec2& v)
	{
		if (type)
			destroy();
		rvar = new float[2];
		rvar[0] = v.x;
		rvar[1] = v.y;
		type = VAR_VEC2;
	}

	inline void Var::set(const vec3& v)
	{
		if (type)
			destroy();
		rvar = new float[3];
		rvar[0] = v.x;
		rvar[1] = v.y;
		rvar[2] = v.z;
		type = VAR_VEC3;
	}

	inline void Var::set(const vec4& v)
	{
		if (type)
			destroy();
		rvar = new float[4];
		rvar[0] = v.x;
		rvar[1] = v.y;
		rvar[2] = v.z;
		rvar[3] = v.w;
		type = VAR_VEC4;
	}

	inline void Var::set(const mat3& m)
	{
		if (type)
			destroy();
		rvar = new float[9];
		for (auto i = 0; i < 9; i++)
			rvar[i] = m[i];
		type = VAR_MAT3;
	}

	inline void Var::set(const mat4& m)
	{
		if (type)
			destroy();
		rvar = new float[16];
		for (auto i = 0; i < 16; i++)
			rvar[i] = m[i];
		type = VAR_MAT4;
	}

	inline void Var::set(const String& s)
	{
		if (type)
			destroy();
		// attempt to decipher the string. It
		// can be a string, or it may be a
		// string representing a numerical
		// type including an array of numbers.
		std::vector<String> vals;
		Tokenize(s, vals);
		if (vals.size() > 1) {
			size_t p = s.find_first_of(".eE");
			if (p != s.npos) {
				if (IsReal(vals[0])) {
					if (vals.size() == 16) {
						set_mat4(s);
						return;
					}
					if (vals.size() == 9) {
						set_mat3(s);
						return;
					}
					if (vals.size() == 4) {
						set_vec4(s);
						return;
					}
					if (vals.size() == 3) {
						set_vec3(s);
						return;
					}
					if (vals.size() == 2) {
						set_vec2(s);
						return;
					}
					set_float(s);
				}
			}
		}
		if (IsInt(s)) {
			set_int(s);
			return;
		}
		if (IsUint(s)) {
			set_uint(s);
			return;
		}
		svar = new String(s);
		type = VAR_STRING;
	}

	inline void Var::set(const Var& copy)
	{
		switch (copy.type) {
			case VAR_INT:
				set(copy.get_int());
				break;
			case VAR_UINT:
				set(copy.get_uint());
				break;
			case VAR_FLOAT:
				set(copy.get_float());
				break;
			case VAR_VEC2:
				set(copy.get_vec2());
				break;
			case VAR_VEC3:
				set(copy.get_vec3());
				break;
			case VAR_VEC4:
				set(copy.get_vec4());
				break;
			case VAR_STRING:
				set(copy.get_string());
		}
	}

	void Var::set_int(const String& v)
	{
		if (type)
			destroy();
		int* i = new int;
		toInt(v, i);
		ivar = i;
		type = VAR_INT;
	}

	void Var::set_uint(const String& v)
	{
		if (type)
			destroy();
		u32* u = new u32;
		toUint(v, u);
		uvar = u;
		//set(*u);
	}

	void Var::set_float(const String& v)
	{
		if (type)
			destroy();
		float* f = new float;
		toFloat(v, f);
		rvar = f;
		type = VAR_FLOAT;
	}

	void Var::set_vec2(const String& v)
	{
		if (type)
			destroy();
		float* f = new float[2];
		Tokenize(v, f, 2);
		rvar = f;
		type = VAR_VEC2;
	}

	void Var::set_vec3(const String& v)
	{
		if (type)
			destroy();
		float* f = new float[3];
		Tokenize(v, f, 3);
		rvar = f;
		type = VAR_VEC3;
	}

	void Var::set_vec4(const String& v)
	{
		if (type)
			destroy();
		float* f = new float[4];
		Tokenize(v, f, 4);
		rvar = f;
		type = VAR_VEC4;
	}

	void Var::set_mat3(const String& v)
	{
		if (type)
			destroy();
		float* f = new float[9];
		Tokenize(v, f, 9);
		rvar = f;
		type = VAR_MAT3;
	}

	void Var::set_string(const String& v)
	{
		if (type)
			destroy();
		svar = new String(v);
		type = VAR_STRING;
	}

	void Var::set_mat4(const String& v)
	{
		if (type)
			destroy();
		float* f = new float[16];
		Tokenize(v, f, 16);
		rvar = f;
		type = VAR_MAT4;
	}

	inline int Var::get_int() const
	{
		int v(0);
		switch (type) {
			case VAR_INT:
				return static_cast<int>(*ivar);
			case VAR_UINT:
				return static_cast<int>(*uvar);
			case VAR_FLOAT:
				return static_cast<int>(*rvar);
			case VAR_STRING:
				{
					try {
						v = svar->to_i32();// std::stoi((*svar), 0);
					}
					catch (...) {
					}
				}
		}
		return v;
	}

	inline u32 Var::get_uint() const
	{
		u32 v(0);
		switch (type) {
			case VAR_INT:
				return static_cast<u32>(*ivar);
			case VAR_UINT:
				return static_cast<u32>(*uvar);
			case VAR_FLOAT:
				return static_cast<u32>(*rvar);
			case VAR_STRING:
				{
					try {
						v = static_cast<u32>(svar->to_u32());// std::stol((*svar), 0));
					}
					catch (...) {
					}
				}
		}
		return v;
	}

	inline char Var::get_char() const
	{
		char v(0);
		switch (type) {
			case VAR_INT:
				return static_cast<char>(*ivar);
			case VAR_UINT:
				return static_cast<char>(*uvar);
			case VAR_FLOAT:
				return static_cast<char>(*rvar);
			case VAR_STRING:
				{
					try {
						v = static_cast<char>(svar->to_i32()); // std::stoi((*svar), 0));
					}
					catch (...) {
					}
				}
		}
		return v;
	}

	inline u8 Var::get_ubyte() const
	{
		u8 v(0);
		switch (type) {
			case VAR_INT:
				return static_cast<u8>(*ivar);
			case VAR_UINT:
				return static_cast<u8>(*uvar);
			case VAR_FLOAT:
				return static_cast<u8>(*rvar);
			case VAR_STRING:
				{
					try {
						v = static_cast<u8>(svar->to_u32());// std::stol((*svar), 0));
					}
					catch (...) {
					}
				}
		}
		return v;
	}

	inline bool Var::get_bool() const
	{
		bool v(false);
		switch (type) {
			case VAR_INT:
				return static_cast<bool>(*ivar);
			case VAR_UINT:
				return static_cast<bool>(*uvar);
			case VAR_FLOAT:
				return static_cast<bool>(*rvar);
			case VAR_STRING:
				{
					try {
						v = static_cast<bool>(svar->to_i32()); // std::stoi((*svar), 0));
					}
					catch (...) {
					}
				}
		}
		return v;
	}

	inline float Var::get_float() const
	{
		float v(0.0f);
		switch (type) {
			case VAR_INT:
				return static_cast<float>(*ivar);
			case VAR_UINT:
				return static_cast<float>(*uvar);
			case VAR_FLOAT:
				return static_cast<float>(*rvar);
			case VAR_STRING:
				{
					try {
						v = svar->to_f32(); // std::stof((*svar));
					}
					catch (...) {
					}
				}
		}
		return v;
	}

	inline double Var::get_double() const
	{
		double v(0.0);
		switch (type) {
			case VAR_INT:
				return static_cast<double>(*ivar);
			case VAR_UINT:
				return static_cast<double>(*uvar);
			case VAR_FLOAT:
				return static_cast<double>(*rvar);
			case VAR_STRING:
				{
					try {
						v = svar->to_f64(); // std::stod((*svar));
					}
					catch (...) {
					}
				}
		}
		return v;
	}

	inline vec2 Var::get_vec2() const
	{
		switch (type) {
			case VAR_INT:
				return vec2((float)*ivar);
			case VAR_UINT:
				return vec2((float)*uvar);
			case VAR_FLOAT:
				return vec2(rvar[0]);
			case VAR_VEC2:
			case VAR_VEC3:
			case VAR_VEC4:
			case VAR_MAT3:
			case VAR_MAT4:
				return vec2(rvar);
			case VAR_STRING:
				return vec2(svar->to_f32()); // toFloat(svar->c_str()));
		}
		return vec2(0.0f);
	}

	inline vec3 Var::get_vec3() const
	{
		switch (type) {
			case VAR_INT:
				return vec3((float)*ivar);
			case VAR_UINT:
				return vec3((float)*uvar);
			case VAR_FLOAT:
				return vec3(rvar[0]);
			case VAR_VEC2:
				return vec3(rvar[0], rvar[1], 0.0f);
			case VAR_VEC3:
			case VAR_VEC4:
			case VAR_MAT3:
			case VAR_MAT4:
				return vec3(rvar);
			case VAR_STRING:
				return vec3(svar->to_f32()); // toFloat(svar->c_str()));
		}
		return vec3(0.0f);
	}

	inline vec4 Var::get_vec4() const
	{
		switch (type) {
			case VAR_INT:
				return vec4((float)*ivar);
			case VAR_UINT:
				return vec4((float)*uvar);
			case VAR_FLOAT:
				return vec4(rvar[0]);
			case VAR_VEC2:
				return vec4(rvar[0], rvar[1], 0.0f, 0.0f);
			case VAR_VEC3:
				return vec4(rvar[0], rvar[1], rvar[2], 0.0f);
			case VAR_VEC4:
			case VAR_MAT3:
			case VAR_MAT4:
				return vec4(rvar);
			case VAR_STRING:
				return vec4(svar->to_f32()); // toFloat(svar->c_str()));
		}
		return vec4(0.0f);
	}

	inline mat3 Var::get_mat3() const
	{
		switch (type) {
			case VAR_MAT3:
				return mat3(rvar);
			case VAR_MAT4:
				return mat3(rvar);
		}
		return mat3();
	}

	inline mat4 Var::get_mat4() const
	{
		switch (type) {
			case VAR_MAT4:
				return mat4(rvar);
		}
		return mat4();
	}

	inline String Var::get_string() const
	{
		switch (type) {
			case VAR_INT:
				return std::to_string(*ivar);
			case VAR_UINT:
				return std::to_string(*uvar);
			case VAR_FLOAT:
				return std::to_string(*rvar);
			case VAR_VEC2:
				return StringFormat("%f,%f", rvar[0], rvar[1]);
			case VAR_VEC3:
				return StringFormat("%f,%f,%f", rvar[0], rvar[1], rvar[2]);
			case VAR_VEC4:
				return StringFormat("%f,%f,%f,%f", rvar[0], rvar[1], rvar[2], rvar[3]);
			case VAR_MAT3:
				return StringFormat("%f,%f,%f,%f,%f,%f,%f,%f,%f",
									rvar[0], rvar[1], rvar[2],
									rvar[3], rvar[4], rvar[5],
									rvar[6], rvar[7], rvar[8]);
			case VAR_MAT4:
				return StringFormat("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
									rvar[0], rvar[1], rvar[2], rvar[3],
									rvar[4], rvar[5], rvar[6], rvar[7],
									rvar[8], rvar[9], rvar[10], rvar[11],
									rvar[12], rvar[13], rvar[15], rvar[15]);
		}
		return *svar;
	}


	inline int Var::get(int deflt)
	{
		if (type == VAR_INT)
			return *ivar;
		else {
			set(deflt);
			return *ivar;
		}
	}

	inline u32 Var::get(u32 deflt)
	{
		if (type == VAR_UINT)
			return *uvar;
		else {
			set(deflt);
			return *uvar;
		}
	}

	inline float Var::get(float deflt)
	{
		if (type == VAR_FLOAT)
			return *rvar;
		else {
			set(float(deflt));
			return *rvar;
		}
	}

	inline vec2 Var::get(const vec2& deflt)
	{
		if (type == VAR_VEC2)
			return vec2(rvar);
		else {
			set(vec2(deflt));
			return deflt;
		}
	}

	inline vec3 Var::get(const vec3& deflt)
	{
		if (type == VAR_VEC3)
			return vec3(rvar);
		else {
			set(vec3(deflt));
			return deflt;
		}
	}

	inline vec4 Var::get(const vec4& deflt)
	{
		if (type == VAR_VEC4)
			return vec4(rvar);
		else {
			set(vec4(deflt));
			return deflt;
		}
	}

	inline mat3 Var::get(const mat3& deflt)
	{
		if (type == VAR_MAT3)
			return mat3(rvar);
		else {
			set(mat3(deflt));
			return deflt;
		}
	}

	inline mat4 Var::get(const mat4& deflt)
	{
		if (type == VAR_MAT4)
			return mat4(rvar);
		else {
			set(mat4(deflt));
			return deflt;
		}
	}

	inline String Var::get(const String& deflt)
	{
		if (type == VAR_STRING)
			return *svar;
		else {
			set(deflt);
			return *svar;
		}
	}

	inline bool Var::get(int* dst)
	{
		bool ret(type == VAR_INT);
		*dst = 0;
		if (ret) *dst = *ivar;
		return ret;
	}


	inline bool Var::get(u32* dst)
	{
		bool ret(type == VAR_UINT);
		*dst = 0;
		if (ret) *dst = *uvar;
		return ret;
	}


	inline bool Var::get(float* dst)
	{
		bool ret(type == VAR_FLOAT);
		*dst = 0.0f;
		if (ret) *dst = *rvar;
		return ret;
	}


	inline bool Var::get(vec2* dst)
	{
		bool ret(type == VAR_VEC2);
		dst->clear();
		if (ret) *dst = vec2(rvar);
		return ret;
	}


	inline bool Var::get(vec3* dst)
	{
		bool ret(type == VAR_VEC3);
		dst->clear();
		if (ret) *dst = vec3(rvar);
		return ret;
	}


	inline bool Var::get(vec4* dst)
	{
		bool ret(type == VAR_VEC4);
		dst->clear();
		if (ret) *dst = vec4(rvar);
		return ret;
	}


	inline bool Var::get(mat3* dst)
	{
		bool ret(type == VAR_MAT3);
		dst->clear();
		if (ret) *dst = vec3(rvar);
		return ret;
	}


	inline bool Var::get(mat4* dst)
	{
		bool ret(type == VAR_MAT4);
		dst->clear();
		if (ret) *dst = vec4(rvar);
		return ret;
	}


} // namespace sge



