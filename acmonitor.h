#ifndef AC_MONITOR_HEADER
#define AC_MONITOR_HEADER

#include<iostream>
#include"observer.h"
class CAcMonitor:public CObserver {
	private:
		int id;
		float temperature;
		char degree;
	public:
		CAcMonitor(int id);
		void update(char degree, float temperature)override;
		static void* threadAc(void *arg);
		void acLevel();
		~CAcMonitor();
};

#endif
