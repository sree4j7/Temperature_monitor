/*			HEADER
*******************************************************************
***								***
*** Programmer: Chikkappagari Sreekanth				***
***								***
*** File: temperature_monitor.cpp				***
***								***
*** Date: 07/02/2019						***
***								***
*******************************************************************
*/
#include"main_controller.h"
#include"temperature_monitor.h"
#include<pthread.h>
using namespace std;

CTemperatureMonitor::CTemperatureMonitor(int nTemp)
{
	m_nId = nTemp;
}

CTemperatureMonitor::CTemperatureMonitor(float fTemp, char szCh, int nNum)
{
    m_fTemperature = fTemp;
    m_szDegree = szCh;
    m_nId = nNum;
}

/*** Update the data in temperature monitor ****/
void CTemperatureMonitor::obs_update( char szCh, float fTemp){
    m_fTemperature = fTemp;
    m_szDegree = szCh;
    cout << "Temperature in temp monitor= " << m_fTemperature << endl;
    cout << "Degree in temp monitor = " << m_szDegree << endl;
    pthread_t pid;
    pthread_create( &pid, NULL, temperature_thread, ( void* )this );
    pthread_join( pid, NULL );
}

void* CTemperatureMonitor::temperature_thread( void *arg )
{
    CTemperatureMonitor *mt = static_cast< CTemperatureMonitor* >( arg );
    mt -> temperature_convert( );
    return 0;
}

/**** Convert the temperature *****/
float CTemperatureMonitor::temperature_convert(){
    char szConvertedDegree;
    float fConvertedTemperature;
    cout << "user id : " << m_nId << endl;
    if( m_szDegree == 'C' || m_szDegree == 'c' )
    {
        fConvertedTemperature = ( m_fTemperature*9.0 )/5.0 + 32;
        szConvertedDegree = 'F';
        cout << "Converted Temperature : " << fConvertedTemperature << " F" << endl;
    }
    else if( m_szDegree == 'F' || m_szDegree == 'f' ) 
    {
 	fConvertedTemperature = ( m_fTemperature -32 )*5/9;
	szConvertedDegree = 'C';
	cout << "Converted Temperature : " << fConvertedTemperature << " C" << endl;
    }
   else
    {
	cout << "Invalid key to convert" << endl;
    }

    return fConvertedTemperature;	
    CMainController::mainController_displayTemp( szConvertedDegree, fConvertedTemperature );
}


CTemperatureMonitor::~CTemperatureMonitor()
{

}
