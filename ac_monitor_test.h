#ifndef AC_MONITOR_H
#define AC_MONITOR_H

#include<iostream>
#include<gtest/gtest.h>
#include"ac_monitor.h"

using namespace std;
class TestAcDummy : public ::testing::Test
{
public:
    TestAcDummy();
    static void SetUpTestCase ();
    static void TearDownTestCase ();
    virtual void SetUp ( void ); 
    virtual void TearDown ( void );

    static int mArgc;
    static char** mArgs;

    static CAcMonitor* pAc;
};

#endif

