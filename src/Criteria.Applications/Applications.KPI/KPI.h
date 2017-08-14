#ifndef _DLL_CRITERIA_KPI_APPLICATION_H_
#define _DLL_CRITERIA_KPI_APPLICATION_H_

#ifdef DLL_CRITERIA_KPI_EXPORTS
	#define DLL_CRITERIA_KPI_API __declspec(dllexport)
#else
	#define DLL_CRITERIA_KPI_API __declspec(dllimport)
#endif

extern "C" DLL_CRITERIA_KPI_API void InstanceApplication(char*);
extern "C" DLL_CRITERIA_KPI_API void DeleteApplication(char*);
extern "C" DLL_CRITERIA_KPI_API char* ExecuteApplicationApi(char* );

#include "bOS/bOS.h"
#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "Scenario/CallBackFunction.h"

class DLL_CRITERIA_KPI_API KPI
{
public:
	KPI();
	~KPI();

	static char* (CALLBACK StartKPI)(char*);
	static void StartKPI(const char* acId, const char* acKpiName, const char* acKpiValue);

	static char* (CALLBACK StopKPI)(char*);
	static void StopKPI(const char* acId, const char* acKpiName, const char* acKpiValue);



private:

};

#endif //_DLL_CRITERIA_KPI_APPLICATION_H_