#include<iostream>
#include<gtest/gtest.h>
#include"temperature_monitor.h"
#include"ac_monitor.h"
int main (int argc, char ** argv)
{

	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();

}
