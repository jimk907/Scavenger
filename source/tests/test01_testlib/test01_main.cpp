#include "log/logger.h"
#include "utilities/gen_utils.h"

#include "comparator/Comparator.h"
#include "testtype/testtype.h"
#include "testgroup/testgroup.h"


using namespace sge;

char HOLD_CHAR('a');

int main(int argc, char* argv[])
{
	int i0(1324);
	int i1(i0);
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsExactPOD(1324, 1324): %s", sgetest::CharEqualsExactPOD(i0, i1));
	i1 = 1325;
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsExactPOD(1324, 1325): %s", sgetest::CharEqualsExactPOD(i0, i1));
	LOGGER::LINE_LOG(1);
	float f0(3.1415f);
	float f1(3.14151f);
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsExactPOD(3.1415, 3.14151): %s", sgetest::CharEqualsExactPOD(f0, f1));
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsCloseEnoughPOD(3.1415, 3.14151): %s", sgetest::CharEqualsCloseEnoughPOD(f0, f1));
	f1 = 3.141505f;
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsCloseEnoughPOD(3.1415, 3.141505): %s", sgetest::CharEqualsCloseEnoughPOD(f0, f1));
	f1 = 3.141501f;
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsCloseEnoughPOD(3.1415, 3.141501): %s", sgetest::CharEqualsCloseEnoughPOD(f0, f1));
	f1 = 3.14150001f;
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsCloseEnoughPOD(3.1415, 3.14150001): %s", sgetest::CharEqualsCloseEnoughPOD(f0, f1));
	LOGGER::LINE_LOG(1);
	double d0(3.001415);
	double d1(3.0014151);
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsExactPOD(3.001415, 3.0014151): %s", sgetest::CharEqualsExactPOD(d0, d1));
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsCloseEnoughPOD(3.001415, 3.0014151): %s", sgetest::CharEqualsCloseEnoughPOD(d0, d1));
	d1 = 3.00141501;
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsExactPOD(3.001415, 3.00141501): %s", sgetest::CharEqualsExactPOD(d0, d1));
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsCloseEnoughPOD(3.001415, 3.00141501): %s", sgetest::CharEqualsCloseEnoughPOD(d0, d1));
	d1 = 3.001415002;
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsCloseEnoughPOD(3.001415, 3.001415002): %s", sgetest::CharEqualsCloseEnoughPOD(d0, d1));
	d1 = 3.001415001;
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsCloseEnoughPOD(3.001415, 3.001415001): %s", sgetest::CharEqualsCloseEnoughPOD(d0, d1));
	LOGGER::LINE_LOG(1);

	struct test {
		float x;
		float y;
		float z;
	};
	test t0 = { 0.1234f, -123.45f, 12.001f };
	test t1 = { 0.1234f, -123.45f, 12.001f };
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsExact(struct t0, struct t1) expect true: %s", sgetest::CharEqualsExact(t0, t1));
	t1 = { 0.1234f, -123.451f, 12.001f };
	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "EqualsExact(struct t0, struct t1) expect false: %s", sgetest::CharEqualsExact(t0, t1));

	bool bb;
	float f2(1.0f);
	float f3(3.0f - 2.0f);
	sgetest::TestEQ<float> test(f2, f3);
	bb = test.Result();

	u32 u0(0x7FFF);
	u32 u1(32767);
	TESTEQ(mytest, u32, u0, u1);
	bb = mytest.Result();
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "mytest(0x7fff, 32767): %s", mytest.ResultString().to_string().c_str());

	sgetest::TestGroupBase MyGroup0("MyGroup0");
	sgetest::TestEQ<float>* thetest = new sgetest::TestEQ<float>(t0.x, 0.1234f);
	MyGroup0.AddTest("X", thetest);
	bb = MyGroup0.Result();

	TEST_GROUP(MyGroup);
	TEST_DEFINE_EQ(MyGroup, X, float, t0.x, 0.1234f);
	TEST_DEFINE_EQ(MyGroup, Y, float, t0.y, -123.45f);
	TEST_DEFINE_EQ(MyGroup, Z, float, t0.z, 12.001f);

	bb = TESTGROUP_MyGroup.Result();
	LOGGER::ATTN_LOG(SgeLogLevel::INFO, "Group test: 'MyGroup' returned a true result.");

	LOGGER::ATTN_LOG(SgeLogLevel::NONE, "\n** Press '%c' to continue... **", HOLD_CHAR);
	//std::cout << "Press 'a' to end.\n";
	WaitKey(HOLD_CHAR);
	return 0;
}
