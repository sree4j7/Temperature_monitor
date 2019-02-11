/*			HEADER
*******************************************************************
***								***
*** Programmer: Chikkappagari Sreekanth				***
***								***
*** File: main_controller.cpp					***
***								***
*** Date: 07/02/2019						***
***								***
*******************************************************************
*/
#include<iostream>
#include<fstream>
#include<string>
#include"main_controller.h"
using namespace std;

/**** Putting the ac level into file ****/
void CMainController::mainController_displayAc( string strCondition )
{
    ofstream fout;
    fout.open( "final.txt", ios::out | ios::app );
    fout << "AC Level : " << strCondition << endl;
    fout.close();
}

/**** Putting the converted temperature data into file ****/
bool CMainController::mainController_displayTemp( char szDeg, float fTemp )
{
    ofstream fout;
    fout.open("final.txt", ios::out | ios::app );
    fout  << "Degree : " << szDeg << "\t" << "Temperature : " << fTemp  << endl; 
    fout.close();
    return true;
}


