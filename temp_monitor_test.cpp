#include<gtest/gtest.h>
#include"temp_monitor_test.h"

using namespace std;

int TestTempDummy::mArgc = 0;
char** TestTempDummy::mArgs = NULL;
CTemperatureMonitor* TestTempDummy::pTemp = NULL;

TestTempDummy::TestTempDummy(void)
{

}

TestTempDummy::~TestTempDummy(void)
{

}

void TestTempDummy::SetUpTestCase()
{
    cout << "Set up test cases." << endl;
    if ( pTemp != NULL )
    {
	delete pTemp;
    }
    pTemp = new CTemperatureMonitor(30, 'c', 1);
}

void TestTempDummy::TearDownTestCase()
{
    cout << "Tear down test cases." << endl;

    delete pTemp;
}

void TestTempDummy::SetUp(void)
{

}

void TestTempDummy::TearDown(void)
{

}

TEST_F ( TestTempDummy, convert_1 )
{
    float s = 68;
    ASSERT_EQ( s, pTemp->temperature_convert() );
}

TEST_F ( TestTempDummy, convert_2 )
{
    float s = 86;
    ASSERT_EQ( s, pTemp->temperature_convert() );
} 
