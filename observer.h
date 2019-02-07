#ifndef OBSERVER_HEADER
#define OBSERVER_HEADER

#include<iostream>
class CObserver {

	public:
		virtual void update(char degree, float temperature) = 0;

};

#endif
