#include "testgroup.h"



namespace sgetest
{

	TestGroupBase::TestGroupBase(const String& name)
		: grp_name(name)
	{
	}

	TestGroupBase::~TestGroupBase()
	{
		for (u32 i = 0; i < grp_tests.size(); i++) {
			delete grp_tests[i].Test;
		}
		grp_tests.clear();
	}

	bool TestGroupBase::Result()
	{
		bool b(false);
		for (u32 i = 0; i < grp_tests.size(); i++) {
			b = grp_tests[i].Test->Result();
			if (!b)
				break;
		}
		return b;
	}

	String TestGroupBase::ResultString()
	{
		bool b(Result());
		if (b)
			return String("true");
		else
			return String("false");

	}

	u32 TestGroupBase::AddTest(const String& name, TestBase* test)
	{
		SgeTestDef def = { name, test };
		grp_tests.push_back(def);
		return (u32)grp_tests.size();
	}


} // namespace sgetest

