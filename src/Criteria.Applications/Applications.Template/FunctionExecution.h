#ifndef _FUNCTION_EXECUTION_H_
#define _FUNCTION_EXECUTION_H_

#include "bOS/bOS.h"
#include "bOS/bOSThread.h"
using namespace bOS::Core;

class SocketWrapper;

#include "CallBackFunction.h"

#include "Criteria/Application.h"
#include "Criteria/ApplicationFunctions.h"
#include "Criteria/ApplicationFunction.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

class FunctionExecution : public Thread
{
public:

	FunctionExecution(SocketWrapper* sock);
	virtual ~FunctionExecution();

	void setSpecialCallBack(CallBackPrimitive* callBack) { CallBackSpecial = callBack;}
	void setCallBacks(CallBackList& callBacks) { vCallBacks = callBacks;}
	void setApplication(Application* _application ) { application=_application;}

private:

	void initialize() {;}
	void run();
	void finalize() {;}

	SocketWrapper* socket;

	CallBackList vCallBacks;
	Application* application;
	CallBackPrimitive* CallBackSpecial;

	//used for returning result if error occurred before invoking callback
	String getXmlResult(long lErrorCode, const char* sErr);
};

#endif //_FUNCTION_EXECUTION_H_