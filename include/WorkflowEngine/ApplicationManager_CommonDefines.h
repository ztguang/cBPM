#ifndef _APPLICATION_MANAGER_COMMONDEFINES_H_
#define _APPLICATION_MANAGER_COMMONDEFINES_H_

//TO_BE_EXPORTED

#ifdef APPLICATIONMANAGER_EXPORTS
	#define APPLICATIONMANAGER_API __declspec(dllexport)
#else
	#define APPLICATIONMANAGER_API __declspec(dllimport)
#endif

#pragma warning (disable: 4786)
#pragma warning (disable: 4251)

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSDateTime.h"
using namespace bOS::Utils;

#endif //_APPLICATION_MANAGER_COMMONDEFINES_H_