#ifndef _WAPI_WORKFLOW_H_
#define _WAPI_WORKFLOW_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

extern "C" ENGINE_API char* getWorkflowList(Response* response);

extern "C" ENGINE_API char* getWorkflowRunningList(Response* response);

extern "C" ENGINE_API void addWorkflow(char* acWorkflow, Response* response);

#endif //_WAPI_WORKFLOW_H_


