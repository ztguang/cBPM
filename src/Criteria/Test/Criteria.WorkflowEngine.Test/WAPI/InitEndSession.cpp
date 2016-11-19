#include "WAPI\WAPI.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include <iostream>
using namespace std;

void InitSessionWithTrace()
{
	CM_CODEBLOCK(InitSessionWithTrace)
	Response* response = new Response();
	response->iCode= 0;

	cout << "InitSession......." << endl;
	InitSessionWithTrace(response, "InitSessionWithTrace", CodeManager::CodeTracer::CODEBLOCK_LEVEL);

	if ( response->iCode != 0 ) 
	{
		cout << "Initializing [KO].Error[" << response->sMsg << "]. Exit." << endl;
		return;
	}

	cout << "EndSession......." << endl;
	EndSession(response);
	if ( response->iCode == 0 ) 
	{
		cout << "Initializing [OK]" << endl;
	}
	else 
	{
		cout << "Terminating [KO].Err[" << response->sMsg << "]" << endl;
	}
}

void TestInitEnd(int iMax)
{
	CM_CODEBLOCK(TestInitEnd)
	Response* response = new Response();
	response->iCode= 0;

	for ( int i=0; i<iMax; i++)
	{
		cout << "InitSession.......[" << i << "]" << endl;
		InitSession(response);

		if ( response->iCode != 0 ) 
		{
			cout << "Initializing [KO].Error[" << response->sMsg << "]. Exit." << endl;
			return;
		}

		cout << "EndSession......." << endl;
		EndSession(response);
		if ( response->iCode == 0 ) 
		{
			cout << "Terminating [OK]" << endl;
		}
		else 
		{
			cout << "Terminating [KO].Err[" << response->sMsg << "]" << endl;
		}
	}
}

void TestEndWithoutInit()
{
	CM_CODEBLOCK(TestEndWithoutInit)
	Response* response = new Response();
	response->iCode= 0;

	cout << "EndSession......." << endl;
	EndSession(response);
	if ( response->iCode == 0 ) 
	{
		cout << "Terminating [OK]" << endl;
	}
	else 
	{
		cout << "Terminating [KO].Err[" << response->sMsg << "]" << endl;
	}
}
