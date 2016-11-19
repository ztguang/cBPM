#ifndef _BASE_APPLICATION_DATAMODEL_H_
#define _BASE_APPLICATION_DATAMODEL_H_

//TO_BE_EXPORTED

#ifdef APPLICATIONDATAMODEL_EXPORTS
    #define APPLICATIONENGINE_API __declspec(dllexport)
#else
    #define APPLICATIONENGINE_API __declspec(dllimport)
#endif

#include "bOS.h"
#include "bOSString.h"
using namespace bOS::CoreString;

#endif //_BASE_APPLICATION_DATAMODEL_H_