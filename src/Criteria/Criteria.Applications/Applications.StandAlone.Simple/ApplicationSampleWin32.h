#ifndef _APPLICATION_SAMPLE_WIN32_H_
#define _APPLICATION_SAMPLE_WIN32_H_

#include "bOS/bOS.h"
#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "Scenario/CallBackFunction.h"

class ApplicationSampleWin32
{
public:
	ApplicationSampleWin32();
	~ApplicationSampleWin32();

	static char* (CALLBACK one)(char*);
	static char* (CALLBACK two)(char*);

private:

};

#endif //_APPLICATION_SAMPLE_WIN32_H_