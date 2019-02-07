#include"acmonitor.h"
#include"maincontroller.h"
#include<string>
using namespace std;

CAcMonitor::CAcMonitor(int temp)
{
	id = temp;
}

/**** Updating the data into AC monitor ****/
void CAcMonitor::update(char ch, float temp) {
	temperature = temp;
	degree = ch;
	cout <<"Temperature in ac : " << temperature << endl;
	cout << "Degree in ac : " << degree << endl;
	pthread_t pt;
	pthread_create(&pt,NULL,threadAc,(void*)this);
	pthread_join(pt,NULL);
}
void* CAcMonitor::threadAc(void *arg)
{
	CAcMonitor *mt = static_cast<CAcMonitor*>(arg);
	mt -> acLevel();
	return 0;
}

/**** Finding the AC Level *****/
void CAcMonitor::acLevel()
{
	cout << "user id : " << id << endl;
	string str;
	if(degree == 'C' || degree == 'c')
	{
		if (temperature >= 16 && temperature <= 19){
			cout << "AC Level : Cool" << endl;
			str = "Cool" ;
		}
		else if (temperature >=19.1 && temperature <= 26){
			cout << "AC Level : Medium" << endl;
			str = "Medium" ;
		}
		else{
			cout << "AC Level : Warm" << endl;
			str = "Warm" ;
		}
	}
	else if(degree == 'F' || degree == 'f')
	{
		if(temperature >= 60.8 && temperature <= 66.2){
			cout << "AC Level : Cool" << endl;			
			 str = "Cool" ;
		}
		else if (temperature >= 66.3 && temperature <= 78.8){
			cout << "AC Level : Medium" << endl;
			str = "Medium" ;
		}
		else{
			 cout << "AC Level : Warm" << endl;
			str = "Warm" ;
		}

	}
CMainController::displayAc(str);
}

CAcMonitor::~CAcMonitor()
{

}
