#include"maincontroller.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/**** Putting the ac level into file ****/
void CMainController::displayAc(string str)
{
ofstream fout;
fout.open("final.txt",ios::out|ios::app);
fout << "AC Level : " << str << endl;
}

/**** Putting the converted temperature data into file ****/
void CMainController::displayTemp(char deg,float temp)
{
ofstream fout;
fout.open("final.txt",ios::out|ios::app);
fout  << "Degree : " << deg << "\t" << "Temperature : " <<temp  << endl; 
}


