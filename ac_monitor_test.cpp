#include<gtest/gtest.h>
#include"ac_monitor_test.h"

using namespace std;

int TestAcDummy::mArgc = 0;
char** TestAcDummy::mArgs = NULL;
CAcMonitor* TestAcDummy::pAc = NULL;

TestAcDummy::TestAcDummy(void)
{

}

TestAcDummy::~TestAcDummy(void)
{

}

void TestAcDummy::SetUpTestCase()
{
	cout << "Set up test cases." << endl;

	if ( pAc != NULL )
	{
		delete pAc;
	}

	pAc = new CAcMonitor ( 16, 'c', 1 );
}

void TestAcDummy::TearDownTestCase()
{
	cout << "Tear down test cases." << endl;

	delete pAc;
}

void TestAcDummy::SetUp(void)
{

}

void TestAcDummy::TearDown(void)
{

}

TEST_F ( TestAcDummy, level_1 )
{
    string s = "Cool";
    ASSERT_EQ( s, pAc->ac_condition() );
}

TEST_F ( TestAcDummy, level_2 )
{
    string s = "Medium";
    ASSERT_EQ( s, pAc->ac_condition() );
}

