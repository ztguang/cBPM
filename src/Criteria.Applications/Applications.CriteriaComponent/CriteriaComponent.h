#ifndef _DLL_CRITERIA_COMPONENT_APPLICATION_H_
#define _DLL_CRITERIA_COMPONENT_APPLICATION_H_

#ifdef DLL_CRITERIA_COMPONENT_EXPORTS
	#define DLL_CRITERIA_COMPONENT_API __declspec(dllexport)
#else
	#define DLL_CRITERIA_COMPONENT_API __declspec(dllimport)
#endif

extern "C" DLL_CRITERIA_COMPONENT_API void InstanceApplication(char*);
extern "C" DLL_CRITERIA_COMPONENT_API void DeleteApplication(char*);
extern "C" DLL_CRITERIA_COMPONENT_API char* ExecuteApplicationApi(char* );

#include "bOS/bOS.h"
#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "Scenario/CallBackFunction.h"

class DLL_CRITERIA_COMPONENT_API CriteriaComponent
{
public:
	CriteriaComponent();
	~CriteriaComponent();

	static char* (CALLBACK MakeSlaves)(char*);
	static void MakeSlaves(const char* idMaster, int nrSlave);

	static char* (CALLBACK GetSlave)(char*);
	static void GetSlave(const char* idMaster, int& idSlave);

	static char* (CALLBACK ReleaseSlave)(char*);
	static bool ReleaseSlave(const char* idMaster, int idSlave);

	static char* (CALLBACK NoSlave)(char*);
	static bool NoSlave(const char* idMaster);

private:

};

#endif //_DLL_CRITERIA_COMPONENT_APPLICATION_H_