/*
*******************************************************************
***								***
*** Programmer: Chikkappagari Sreekanth				***
***								***
*** File: temperature_monitor.h					***
***								***
*** Date: 07/02/2019						***
***								***
*******************************************************************
*/
#ifndef TEMPERATURE_MONITOR_HEADER
#define TEMPERATURE_MONITOR_HEADER

#include<iostream>
#include"observer.h"
class CTemperatureMonitor:public CObserver {
    private:
	int m_nId;
	float m_fTemperature;
	char m_szDegree;
    public:
	CTemperatureMonitor( );
	CTemperatureMonitor( int );
	CTemperatureMonitor( float, char, int );
	void obs_update( char, float )override;
	float temperature_convert( void );
	static void* temperature_thread( void * );
	~CTemperatureMonitor( );
};

#endif

