#ifndef TEMP_SENSOR_TEST_H
#define TEMP_SENSOR_TEST_H

#include<iostream>
#include<gtest/gtest.h>
#include"observer.h"
#include"temperature_sensor.h"
using namespace std;
class TestSensorDummy : public ::testing::Test
{
public:
	TestSensorDummy();
	virtual ~TestSensorDummy();
	static void SetUpTestCase ();
	static void TearDownTestCase ();
	virtual void SetUp ( void );
	virtual void TearDown ( void );

	static int mArgc;
	static char** mArgs;

	static CTemperatureSensor* pSensor;
};
#endif
