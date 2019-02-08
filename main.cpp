/*			HEADER
*******************************************************************
***								***
*** Programmer: Chikkappagari Sreekanth				***
***								***
*** File: main.cpp 						***
***								***
*** Date: 07/02/2019						***
***								***
*******************************************************************
*/
#include<iostream>
#include"temperature_sensor.h"
#include"temperature_monitor.h"
#include"ac_monitor.h"
using namespace std;

int main() {
    CTemperatureSensor *ptr;
    ptr = new CTemperatureSensor();	

    CTemperatureMonitor *tptr;
    tptr = new CTemperatureMonitor(1);
 
    CAcMonitor *aptr;
    aptr = new CAcMonitor(4);
	
    ptr->sub_subscribed(aptr);
    ptr->sub_subscribed(tptr);
//  ptr->sub_unsubscribed(tptr);

    ptr->sensor_setTemperature();
    ptr->sensor_assignData();
	
    return 0;
}




























/*
//	CAcMonitor four(4), five(5);
	CTemperatureSensor  obj;
	obj.subscribed(&one);
	obj.subscribed(&two);
	obj.subscribed(&three);
	obj.subscribed(&four);
	obj.subscribed(&five);

	
	
	obj.setTemperature();
	obj.assignData();
	
	obj.unsubscribed(&one);
	obj.subscribed(&five);
	obj.unsubscribed(&five);

	obj.setTemperature();
	obj.assignData();
*/

