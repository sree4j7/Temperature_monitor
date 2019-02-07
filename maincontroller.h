#ifndef MAIN_CONTROLLER_HEADER
#define MAIN_CONTROLLER_HEADER
#include<string>
#include<iostream>
#include"temperaturemonitor.h"
#include"acmonitor.h"
using namespace std;
class CMainController{
	public:
		static void displayAc(string);
                static void displayTemp(char,float);
};

#endif
