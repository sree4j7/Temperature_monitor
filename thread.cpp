#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;
class test
{
	public:
		static void* set_data(void * arg)
		{
			int x=45;
			cout << "In set data x= " << x << endl;
		}
		void call()
		{
			pthread_t pt;
			pthread_create(&pt,0,set_data,this);
		}
};
int main()
{
	test t1;
	t1.call();
	sleep(1);
}
