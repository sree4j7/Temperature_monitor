#include"temperaturemonitor.h"
#include"maincontroller.h"
#include<pthread.h>
using namespace std;

/*** Update the data in temperature monitor ****/
void CTemperatureMonitor::update(char ch, float temp){
	temperature = temp;
	degree = ch;
	cout << "Temperature in temp monitor= " << temperature << endl;
	cout << "Degree in temp monitor = " << degree << endl;
	pthread_t pt;
	pthread_create(&pt,NULL,thread,(void*)this);
	pthread_join(pt,NULL);
}
void* CTemperatureMonitor::thread(void *arg)
{
	CTemperatureMonitor *mt = static_cast<CTemperatureMonitor*>(arg);
	mt -> convertTemperature();
	return 0;
}

/**** Convert the temperature *****/
void CTemperatureMonitor::convertTemperature(){
	char convertedDegree;
	float converted;
	cout << "user id : " << id << endl;
	if(degree == 'C' || degree == 'c')
	{
		converted = (temperature*9.0)/5.0 + 32;
		convertedDegree = 'F';
		cout << "Converted Temperature : " << converted << " F" << endl;
	}
	else if(degree == 'F' || degree == 'f')
	{
		converted = (temperature -32)*5/9;
		convertedDegree = 'C';
		cout << "Converted Temperature : " << converted << " C" << endl;
	}
	else
	{
		cout << "Invalid key to convert" << endl;
	}
	
CMainController::displayTemp(convertedDegree,converted);
	

}

CTemperatureMonitor::CTemperatureMonitor(int temp)
{
	id = temp;
}

CTemperatureMonitor::~CTemperatureMonitor()
{

}
