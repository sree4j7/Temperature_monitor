#include<gtest/gtest.h>
#include"main_controller_test.h"

using namespace std;

int TestMainDummy::mArgc = 0;
char** TestMainDummy::mArgs = NULL;
CMainController* TestMainDummy::pMain= NULL;

TestMainDummy::TestMainDummy( void )
{

}

TestMainDummy::~TestMainDummy( void )
{

}

void TestMainDummy::SetUpTestCase()
{
	cout << "Set up test cases." << endl;

	if ( pMain != NULL )
	{
		delete pMain;
	}

	pMain = new CMainController();
}

void TestMainDummy::TearDownTestCase()
{
	cout << "Tear down test cases." << endl;

	delete pMain;
}

void TestMainDummy::SetUp(void)
{

}

void TestMainDummy::TearDown(void)
{

}

TEST_F(TestMainDummy, main_1 )
{
	bool bRet = pMain->mainController_displayTemp('f', 98.4);
	cout << "Return vlaue " << bRet << endl;
        ASSERT_TRUE( bRet );
}
