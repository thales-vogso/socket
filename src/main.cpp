/****************************************************************************
*	@Copyright(c)	2015,Vogso
*	@desc	主程序
*	@date	2015-9-30
*	@author	minamoto
*	@E-mail	jiangtai@wushuang.me
*	@file	main.cpp
******************************************************************************/

#include <iostream>
#include <string>
#include "SocketServer.h"
#include "SocketException.h"
using namespace std;

int main()
{
	cout<<"Running server..."<<endl;
	try
	{
		SocketServer server(8843);
		server.run();
	}
	catch(SocketException& ex)
	{
		cout << "Exception was caught:" << ex.Description() << "\nExiting.\n";
	}
	return 0;
}
