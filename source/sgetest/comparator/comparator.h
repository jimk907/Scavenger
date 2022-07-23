#pragma once
#include "sge_defines.h"



namespace sgetest
{

	const float EPSILON(1e-6f);
	const double EPSILOND(1e-9f);

	template <typename T>
	bool EqualsExact(const T& a, const T& b);

	template <typename T>
	bool EqualsCloseEnoughPOD(const T& a, const T& b);

	template <typename T>
	bool EqualsExactPOD(const T& a, const T& b);

	template <typename T>
	bool EqualsObjectInternal(const T& a, const T& b);


	//
	const char* CharTrueFalse(bool b);

	template <typename T>
	const char* CharEqualsExact(const T& a, const T& b);

	template <typename T>
	const char* CharEqualsCloseEnoughPOD(const T& a, const T& b);

	template <typename T>
	const char* CharEqualsExactPOD(const T& a, const T& b);

	template <typename T>
	const char* CharEqualsObjectInternal(const T& a, const T& b);


	template <typename T>
	bool EqualsExact(const T& a, const T& b)
	{
		u32 asize = sizeof(a);
		u32 bsize = sizeof(b);
		if (asize != bsize)
			return false;
		return std::memcmp(a, b, asize) == 0;
	}

	template <typename T>
	bool EqualsCloseEnoughPOD(const T& a, const T& b)
	{
		T diff = a - b;
		return (diff > -EPSILON) && (diff < EPSILON);
	}

	template <typename T>
	bool EqualsExactPOD(const T& a, const T& b)
	{
		return a == b;
	}

	template <typename T>
	bool EqualsObjectInternal(const T& a, const T& b)
	{
		return a == b;
	}

	const char txtTrue[] = "true";
	const char txtFalse[] = "false";

	const char* CharTrueFalse(bool b)
	{

		if (b)
			return txtTrue;
		else
			return txtFalse;
	}

	template <typename T>
	const char* CharEqualsExact(const T& a, const T& b)
	{
		u32 asize = sizeof(a);
		u32 bsize = sizeof(b);
		if (asize != bsize)
			return "false";
		return CharTrueFalse(std::memcmp((&a), (&b), asize) == 0);
	}

	template <typename T>
	const char* CharEqualsCloseEnoughPOD(const T& a, const T& b)
	{
		T diff = a - b;
		return CharTrueFalse((diff > -EPSILON) && (diff < EPSILON));
	}

	template <>
	const char* CharEqualsCloseEnoughPOD<double>(const double& a, const double& b)
	{
		double diff = a - b;
		return CharTrueFalse((diff > -EPSILOND) && (diff < EPSILOND));
	}

	template <typename T>
	const char* CharEqualsExactPOD(const T& a, const T& b)
	{
		return CharTrueFalse(a == b);
	}

	template <typename T>
	const char* CharEqualsObjectInternal(const T& a, const T& b)
	{
		return CharTrueFalse(a == b);
	}




} // namespace sgetest

