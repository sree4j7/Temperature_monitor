#ifndef SUBJECT_HEADER
#define SUBJECT_HEADER 

#include<iostream>
#include"observer.h"
class CSubject {

        public:
                virtual void subscribed(CObserver *observer) = 0;
                virtual void unsubscribed(CObserver *observer) = 0;
                virtual void notify() = 0;
};

#endif

