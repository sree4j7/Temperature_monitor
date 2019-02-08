/*			HEADER
*******************************************************************
***								***
*** Programmer: Chikkappagari Sreekanth				***
***								***
*** File: main_controller.h					***	
***								***
*** Date: 07/02/2019						***
***								***
*******************************************************************
*/
#ifndef MAIN_CONTROLLER_HEADER
#define MAIN_CONTROLLER_HEADER
#include<string>
#include<iostream>
#include"temperature_monitor.h"
#include"ac_monitor.h"
using namespace std;
class CMainController{
    public:
	static void mainController_displayAc( string );
        static void mainController_displayTemp( char, float );
};

#endif
