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
		float temperature;
		char degree;
        public:
		CTemperatureSensor();
                vector<CObserver *> observers;
                void subscribed(CObserver *observer)override;
                void unsubscribed(CObserver *observer)override;
                void notify()override;
                void setTemperature();
		void assignData();
		~CTemperatureSensor();
};

#endif

