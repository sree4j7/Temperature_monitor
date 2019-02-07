#include<iostream>
#include"temperaturesensor.h"
#include"temperaturemonitor.h"
#include"acmonitor.h"
using namespace std;

int main() {
	CTemperatureSensor *ptr;
	ptr = new CTemperatureSensor();	
	
	CTemperatureMonitor *tptr;
	tptr = new CTemperatureMonitor(1);

	CAcMonitor *aptr;
	aptr = new CAcMonitor(4);
	
	ptr->subscribed(aptr);
	ptr->subscribed(tptr);
//	ptr->unsubscribed(tptr);
	
	ptr->setTemperature();
	ptr->assignData();
	
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

