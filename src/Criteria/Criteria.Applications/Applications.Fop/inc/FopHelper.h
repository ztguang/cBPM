#ifndef _FOP_HELPER_H_
#define _FOP_HELPER_H_

#include "bOS/bOS.h"
#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "ApplicationTemplate/CallBackFunction.h"

class FopHelper
{
public:
	FopHelper(const String& sClassPath);
	~FopHelper();

	static char* (CALLBACK createPdf)(char*);

private:
	
};

#endif //_FOP_HELPER_H_