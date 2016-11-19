#ifndef _APPLICATION_TEMPLATE_H_
#define _APPLICATION_TEMPLATE_H_

//TO_BE_EXPORTED

#ifdef APPLICATIONTEMPLATE_EXPORTS
	#define APPLICATIONTEMPLATE_API __declspec(dllexport)
#else
	#define APPLICATIONTEMPLATE_API __declspec(dllimport)
#endif

#include "bOS/bOS.h"
#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "Criteria/ApplicationFunctionResult.h"
#include "Criteria/Application.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "CallBackFunction.h"

class APPLICATIONTEMPLATE_API ApplicationTemplate 
{
public:

	ApplicationTemplate();
	virtual ~ApplicationTemplate();

	void startup(const String& sApplicationName);
	bool init(const String& sApplicationName);
	char* executeApi(char*);

	void addCallBack(const String& sFunctionName, CallBackFunction);
	void addSpecialCallBack(const String& sFunctionName, CallBackFunction);

private:

	CallBackList vCallBacks;
	CallBackPrimitive* CallBackSpecial;

	Application application;

};

extern "C" APPLICATIONTEMPLATE_API ApplicationTemplate* CreateClass();
extern "C" APPLICATIONTEMPLATE_API void DeleteClass( ApplicationTemplate* instance );
extern "C" APPLICATIONTEMPLATE_API void StartUp( ApplicationTemplate* instance, char* acApplicationName );
extern "C" APPLICATIONTEMPLATE_API void AddCallBack( ApplicationTemplate* instance, CallBackFunction function, char* acFunctionName );
extern "C" APPLICATIONTEMPLATE_API void AddSpecialCallBack( ApplicationTemplate* instance, CallBackFunction function, char* acFunctionName );

//parameter and result
typedef struct 
{
	char* acName;
	char* acValue; 
} FunctionParameter;

extern "C" APPLICATIONTEMPLATE_API void GetFunctionParameters( char* acFunction, int* pSize, FunctionParameter** ppStruct );


extern "C" APPLICATIONTEMPLATE_API ApplicationFunctionResult* CreateResultClass(char* acMessage, int iCode);
extern "C" APPLICATIONTEMPLATE_API void DeleteResultClass(ApplicationFunctionResult* instance);
extern "C" APPLICATIONTEMPLATE_API void AddResultParameter(ApplicationFunctionResult* instance, char* acName, char* acValue);
extern "C" APPLICATIONTEMPLATE_API void AddResultParameterType(ApplicationFunctionResult* instance, char* acName, char* acValue, char* acType);
extern "C" APPLICATIONTEMPLATE_API char* GetResultXml(ApplicationFunctionResult* instance);

#endif //_APPLICATION_TEMPLATE_H_