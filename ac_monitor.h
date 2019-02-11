/*			HEADER
*******************************************************************
***								***
*** Programmer: Chikkappagari Sreekanth				***
***								***
*** File: ac_monitor.h						***
***								***
*** Date: 07/02/2019						***
***								***
*******************************************************************
*/
#ifndef AC_MONITOR_HEADER
#define AC_MONITOR_HEADER

#include<iostream>
#include"observer.h"
#include<string>
#include"observer.h"
class CAcMonitor:public CObserver {
    private:
	int m_nId;
	float m_fTemperature;
	char m_szDegree;
    public:
	CAcMonitor( int );
	CAcMonitor( float, char, int );
	void obs_update(char, float )override;
	static void* ac_threadAc( void * );
	bool ac_condition( );
	~CAcMonitor();
};

#endif
