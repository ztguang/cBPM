#ifndef _WAPI_FORMS_H_
#define _WAPI_FORMS_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

extern "C" ENGINE_API char* getFormsList(Response* response);
extern "C" ENGINE_API char* getForm(char* acName, Response* response);
extern "C" ENGINE_API void setForm(char* acName, char* acJsContent, Response* response);

#endif //_WAPI_FORMS_H_


