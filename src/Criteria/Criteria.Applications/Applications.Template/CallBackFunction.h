#ifndef _CALL_BACK_FUNCTION_H_
#define _CALL_BACK_FUNCTION_H_

//TO_BE_EXPORTED

#include "Criteria/ApplicationFunction.h"
#include "Criteria/ApplicationFunctionResult.h"

typedef char* (CALLBACK *CallBackFunction)(char*);

class CallBackPrimitive
{
public:
	CallBackPrimitive(const String& sFunctionName, CallBackFunction callback) 
	{
		sFunction=sFunctionName;
		function=callback;
	}

	~CallBackPrimitive() {;}

	String sFunction;
	CallBackFunction function;
};

typedef vector<CallBackPrimitive> CallBackList;

#endif //_CALL_BACK_FUNCTION_H_