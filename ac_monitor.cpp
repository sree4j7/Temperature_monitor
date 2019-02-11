/*			HEADER
*******************************************************************
***								***
*** Programmer: Chikkappagari Sreekanth				***
***								***
*** File: ac_monitor.cpp					***
***								***
*** Date: 07/02/2019						***
***								***
*******************************************************************
*/
#include"ac_monitor.h"
#include"main_controller.h"
#include<string>
using namespace std;

CAcMonitor::CAcMonitor( int nTemp )
{
    m_nId = nTemp;
}

CAcMonitor::CAcMonitor(float fTemp, char szCh, int nNum)
{
    m_fTemperature = fTemp;
    m_szDegree = szCh;
    m_nId = nNum;    
}
 /*
 *  CAcMonitor::update - This function is called from temperature sensor class
 *  to process the temperature and created a thread for calling function
 */ 
void CAcMonitor::obs_update( char szCh, float fTemp ) {
    m_fTemperature = fTemp;
    m_szDegree = szCh;
    cout <<"Temperature in ac : " << m_fTemperature << endl;
    cout << "Degree in ac : " << m_szDegree << endl;
    pthread_t pid;
    pthread_create(&pid, NULL, ac_threadAc ,( void* )this );
    pthread_join( pid ,NULL );
}

void* CAcMonitor::ac_threadAc( void *arg )
{
    CAcMonitor *mt = static_cast< CAcMonitor* >( arg );
    mt -> ac_condition( );
    return 0;
}

bool CAcMonitor::ac_condition( )
{
    cout << "user id : " << m_nId << endl;
    string strCondition;
    if( m_szDegree == 'C' || m_szDegree == 'c' )
    {
	if ( m_fTemperature >= 16 && m_fTemperature <= 19){
	    cout << "AC Level : Cool" << endl;
	    strCondition = "Cool";
	}
	else if ( m_fTemperature >= 19.1 && m_fTemperature <= 26 ){
            cout << "AC Level : Medium" << endl;
	    strCondition = "Medium";
	}
	else{
            cout << "AC Level : Warm" << endl;
	    strCondition = "Warm";
	}
    }
    else if( m_szDegree == 'F' || m_szDegree == 'f')
    {
        if( m_fTemperature >= 60.8 && m_fTemperature <= 66.2 ){
            cout << "AC Level : Cool" << endl;			
	    strCondition = "Cool";
	}
	else if( m_fTemperature >= 66.3 && m_fTemperature <= 78.8 ){
            cout << "AC Level : Medium" << endl;
	    strCondition = "Medium";
	}
	else{
	    cout << "AC Level : Warm" << endl;
	    strCondition = "Warm";
	}
    }
    CMainController::mainController_displayAc( strCondition );
    return true;
}

CAcMonitor::~CAcMonitor()
{

}
