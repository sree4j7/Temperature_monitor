#include"temperaturesensor.h"
#include<cstring>
#include<fstream>
using namespace std;

/****** Subscribed users pushing into vector ******/
void CTemperatureSensor::subscribed(CObserver *observer)
{
	observers.push_back(observer);
}

/**** finding and removing the unsubscribed users *******/
void CTemperatureSensor::unsubscribed(CObserver *observer) {
	auto iterator = find(observers.begin(), observers.end(), observer);

	if (iterator != observers.end()) {
		observers.erase(iterator);
	}
}

/***** notify to the observers *****/
void CTemperatureSensor::notify() {
	for (CObserver *observer : observers) {
		observer->update(degree,temperature);
	}
}

/***** Fetching the data from the file.txt *****/
vector< pair <char,float> > project;
void CTemperatureSensor::setTemperature() 
{
	char c;
	float temp;
	string line,al;
	ifstream fin;
	fin.open("file.txt");
	while(!fin.eof())
	{    
		getline(fin,line,':')&&getline(fin,al);
		if(fin)
		{
			temp = std::stof(line);
			char char_array[al.length()+1];
			strcpy(char_array, al.c_str());
			c = char_array[0];
			project.push_back(make_pair(c,temp));
		}
	}

}

void CTemperatureSensor::assignData()
{
	for(unsigned long int i = 0;i<project.size();i++)
	{
//		cout << project[i].first << "\t" << project[i].second << endl;
		degree = project[i].first;
		temperature = project[i].second;
		notify();
	}
}

CTemperatureSensor::CTemperatureSensor()
{

}

CTemperatureSensor::~CTemperatureSensor()
{
}
