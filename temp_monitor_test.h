#ifndef TEMP_MONITOR_H
#define TEMP_MONITOR_H

#include<iostream>
#include<gtest/gtest.h>
#include"temperature_sensor.h"
#include"temperature_monitor.h"
#include"observer.h"
#include"subject.h"
#include"ac_monitor.h"
#include"main_controller.h"
using namespace std;


class TestTempDummy : public ::testing::Test
{
public:
    TestTempDummy();
    virtual ~TestTempDummy();
    static void SetUpTestCase ();
    static void TearDownTestCase ();
    virtual void SetUp ( void );
    virtual void TearDown ( void );

    static int mArgc;
    static char** mArgs;

    static CTemperatureMonitor* pTemp;
};

#endif
