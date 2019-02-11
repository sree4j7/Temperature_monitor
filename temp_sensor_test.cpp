#include<gtest/gtest.h>
#include"temp_sensor_test.h"

using namespace std;

int TestSensorDummy::mArgc = 0;
char** TestSensorDummy::mArgs = NULL;
CTemperatureSensor* TestSensorDummy::pSensor= NULL;

TestSensorDummy::TestSensorDummy( void )
{

}

TestSensorDummy::~TestSensorDummy( void )
{

}

void TestSensorDummy::SetUpTestCase()
{
	cout << "Set up test cases." << endl;

	if ( pSensor != NULL )
	{
		delete pSensor;
	}

	pSensor = new CTemperatureSensor();
}

void TestSensorDummy::TearDownTestCase()
{
	cout << "Tear down test cases." << endl;

	delete pSensor;
}

void TestSensorDummy::SetUp(void)
{

}

void TestSensorDummy::TearDown(void)
{

}

TEST_F(TestSensorDummy, File_open_1 )
{
	bool bRet = pSensor->sensor_setTemperature();
	cout << "Return vlaue " << bRet << endl;
        ASSERT_FALSE( bRet );
}
