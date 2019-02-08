/*			HEADER
*******************************************************************
***								***
*** Programmer: Chikkappagari Sreekanth				***
***								***
*** File: m_fTemperature_sensor.cpp				***
***								***
*** Date: 07/02/2019						***
***								***
*******************************************************************
*/
#include"temperature_sensor.h"
#include<cstring>
#include<fstream>
using namespace std;

/****** Subscribed users pushing into vector ******/
void CTemperatureSensor::sub_subscribed(CObserver *observer)
{
    observers.push_back(observer);
}

/**** finding and removing the unsubscribed users *******/
void CTemperatureSensor::sub_unsubscribed(CObserver *observer) {
    auto iterator = find(observers.begin(), observers.end(), observer);

    if (iterator != observers.end()) {
 	observers.erase(iterator);
    }
}

/***** notify to the observers *****/
void CTemperatureSensor::sub_notify(void) {
    for (CObserver *observer : observers) {
	observer->obs_update(m_szDegree,m_fTemperature);
    }
}

/***** Fetching the data from the file.txt *****/
vector< pair <char,float> > vect_project;
void CTemperatureSensor::sensor_setTemperature(void) 
{
    char szCh;
    float fTemp;
    string strTemp;
    string strDeg;
    ifstream fin;
    fin.open("file.txt");
    if(fin.fail())
    {
	cout << "File is not preaent" << endl;
	return;
    }
   while(!fin.eof())
   {    
	getline(fin,strTemp,':')&&getline(fin,strDeg);
	if(fin)
	{
            fTemp = std::stof(strTemp);
	    char szChar_array[strDeg.length()+1];
	    strcpy(szChar_array, strDeg.c_str());
	    szCh = szChar_array[0];
	    vect_project.push_back(make_pair(szCh,fTemp));
	}
    }
}

void CTemperatureSensor::sensor_assignData(void)
{
    for(unsigned long int i = 0;i<vect_project.size();i++)
    {
	m_szDegree = vect_project[i].first;
	m_fTemperature = vect_project[i].second;
 	sub_notify();
    }
}

CTemperatureSensor::CTemperatureSensor()
{

}

CTemperatureSensor::~CTemperatureSensor()
{

}
