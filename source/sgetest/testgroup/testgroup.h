#pragma once
#include "sge_defines.h"
#include "testtype/testtype.h"



namespace sgetest
{

	struct SgeTestDef {
		String    Name;
		TestBase* Test;
	};

	class TestGroupBase
	{
	public:
		TestGroupBase(const String& name);
		virtual ~TestGroupBase();
		bool Result();
		String ResultString();
		u32 AddTest(const String& name, TestBase* test);

		String GetName() const { return grp_name; }
		void SetName(const String& name) { grp_name = name; }

	private:
		std::vector<SgeTestDef> grp_tests;
		String                  grp_name;
	};


} // namespace sgetest

#define TEST_GROUP(name) \
sgetest::TestGroupBase TESTGROUP_##name(#name);

#define TEST_DEFINE_EQ(group, name, type, lhs, rhs) \
sgetest::TestEQ<type> *test##name = new sgetest::TestEQ<type>(lhs, rhs); \
TESTGROUP_##group.AddTest(#name, test##name);

#define TEST_DEFINE_LT(group, name, type, lhs, rhs) \
sgetest::TestLT<type> *test##name = new sgetest::TestLT<type>(lhs, rhs); \
TESTGROUP_##group.AddTest(#name, test##name);

#define TEST_DEFINE_GT(group, name, type, lhs, rhs) \
sgetest::TestGT<type> *test##name = new sgetest::TestGT<type>(lhs, rhs); \
TESTGROUP_##group.AddTest(#name, test##name);

#define TEST_DEFINE_LE(group, name, type, lhs, rhs) \
sgetest::TestLE<type> *test##name = new sgetest::TestLE<type>(lhs, rhs); \
TESTGROUP_##group.AddTest(#name, test##name);

#define TEST_DEFINE_GE(group, name, type, lhs, rhs) \
sgetest::TestGE<type> *test##name = new sgetest::TestGE<type>(lhs, rhs); \
TESTGROUP_##group.AddTest(#name, test##name);


// comment to prevent unexpected EOF