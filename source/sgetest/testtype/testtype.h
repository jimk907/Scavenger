#pragma once
#include "sge_defines.h"
#include "string/string.h"


namespace sgetest
{
	using namespace sge;


	class TestBase
	{
	public:
		TestBase()
		{}
		virtual ~TestBase()
		{}
		virtual bool Result()
		{
			return false;
		}
		virtual String ResultString()
		{
			return "false";
		}
	};

	// TestEQ specializations
	template <typename T>
	class TestEQ : public TestBase
	{
	public:
		TestEQ(T a, T b)
			: a_(a)
			, b_(b)
			, EPS(0)
		{}
		~TestEQ()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			return (a_ == b_);
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		T a_;
		T b_;
		T EPS;
	};

	template <>
	class TestEQ<float> : public TestBase
	{
	public:
		TestEQ(float a, float b)
			: a_(a)
			, b_(b)
			, EPS(1e-6f)
		{}
		~TestEQ()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			float d = a_ - b_;
			return (d > -EPS && d < EPS);
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		float a_;
		float b_;
		float EPS;
	};

	template <>
	class TestEQ<double> : public TestBase
	{
	public:
		TestEQ(double a, double b)
			: a_(a)
			, b_(b)
			, EPS(1e-9)
		{}
		~TestEQ()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			double d = a_ - b_;
			return (d > -EPS && d < EPS);
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		double a_;
		double b_;
		double EPS;
	};

	// TestLT specializations
	template <typename T>
	class TestLT : public TestBase
	{
	public:
		TestLT(T a, T b)
			: a_(a)
			, b_(b)
			, EPS(0)
		{}
		~TestLT()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			return (a_ < b_);
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		T a_;
		T b_;
		T EPS;
	};

	// TestLE specializations
	template <typename T>
	class TestLE : public TestBase
	{
	public:
		TestLE(T a, T b)
			: a_(a)
			, b_(b)
			, EPS(0)
		{}
		~TestLE()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			return (a_ <= b_);
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		T a_;
		T b_;
		T EPS;
	};

	template <>
	class TestLE<float> : public TestBase
	{
	public:
		TestLE(float a, float b)
			: a_(a)
			, b_(b)
			, EPS(1e-6f)
		{}
		~TestLE()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			float d = a_ - b_;
			if (d > -EPS && d < EPS) return true;
			return a_ < b_;
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		float a_;
		float b_;
		float EPS;
	};

	template <>
	class TestLE<double> : public TestBase
	{
	public:
		TestLE(double a, double b)
			: a_(a)
			, b_(b)
			, EPS(1e-9)
		{}
		~TestLE()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			double d = a_ - b_;
			if (d > -EPS && d < EPS) return true;
			return a_ < b_;
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		double a_;
		double b_;
		double EPS;
	};

	// TestGT specializations
	template <typename T>
	class TestGT : public TestBase
	{
	public:
		TestGT(T a, T b)
			: a_(a)
			, b_(b)
			, EPS(0)
		{}
		~TestGT()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			return (a_ > b_);
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		T a_;
		T b_;
		T EPS;
	};

	// TestGE specializations
	template <typename T>
	class TestGE : public TestBase
	{
	public:
		TestGE(T a, T b)
			: a_(a)
			, b_(b)
			, EPS(0)
		{}
		~TestGE()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			return (a_ >= b_);
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		T a_;
		T b_;
		T EPS;
	};

	template <>
	class TestGE<float> : public TestBase
	{
	public:
		TestGE(float a, float b)
			: a_(a)
			, b_(b)
			, EPS(1e-6f)
		{}
		~TestGE()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			float d = a_ - b_;
			if (d > -EPS && d < EPS) return true;
			return a_ > b_;
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		float a_;
		float b_;
		float EPS;
	};

	template <>
	class TestGE<double> : public TestBase
	{
	public:
		TestGE(double a, double b)
			: a_(a)
			, b_(b)
			, EPS(1e-9)
		{}
		~TestGE()
		{}
		bool Result() override
		{
			return InternalResult();
		}
		String ResultString() override
		{
			return InternalResultString();
		}
	protected:
		bool InternalResult()
		{
			double d = a_ - b_;
			if (d > -EPS && d < EPS) return true;
			return a_ > b_;
		}
		String InternalResultString()
		{
			if (InternalResult())
				return "true";
			else
				return "false";
		}
	private:
		double a_;
		double b_;
		double EPS;
	};


} // namespace sgetest

#define TESTEQ(name, T, lhs, rhs) sgetest::TestEQ<T> ##name(lhs, rhs);

