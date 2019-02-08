/*			HEADER
*******************************************************************
***								***
*** Programmer: Chikkappagari Sreekanth				***
***								***
*** File: temperature_sensor.h					***
***								***
*** Date: 07/02/2019						***
***								***
*******************************************************************
*/
#ifndef TEMPERATURE_SENSOR_HEADER
#define TEMPERATURE_SENSOR_HEADER

#include<iostream>
#include<vector>
#include<algorithm>
#include"subject.h"
#include"observer.h"
using namespace std;
class CTemperatureSensor:public CSubject {
    private:
	float m_fTemperature;
	char m_szDegree;
    public:
	CTemperatureSensor();
        vector<CObserver *> observers;
        void sub_subscribed(CObserver *observer)override;
        void sub_unsubscribed(CObserver *observer)override;
        void sub_notify()override;
        void sensor_setTemperature(void);
        void sensor_assignData(void);
	~CTemperatureSensor();
};

#endif

