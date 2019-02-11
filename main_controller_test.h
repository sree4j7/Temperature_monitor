#ifndef MAIN_CONTROLLER_TEST_H
#define MAIN_CONTROLLER_TEST_H

#include<iostream>
#include<gtest/gtest.h>
#include"observer.h"
#include"temperature_sensor.h"
#include"main_controller.h"
using namespace std;
class TestMainDummy : public ::testing::Test
{
public:
	TestMainDummy();
	virtual ~TestMainDummy();
	static void SetUpTestCase ();
	static void TearDownTestCase ();
	virtual void SetUp ( void );
	virtual void TearDown ( void );

	static int mArgc;
	static char** mArgs;

	static CMainController* pMain;
};
#endif
