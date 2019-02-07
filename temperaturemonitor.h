#ifndef TEMPERATURE_MONITOR_HEADER
#define TEMPERATURE_MONITOR_HEADER

#include<iostream>
#include"observer.h"
class CTemperatureMonitor:public CObserver {
	private:
		int id;
		float temperature;
		char degree;
	public:
		CTemperatureMonitor();
		CTemperatureMonitor(int temp);
		void update(char degree, float temperature)override;
		void convertTemperature();
		static void* thread(void *arg);
		~CTemperatureMonitor();
};

#endif

