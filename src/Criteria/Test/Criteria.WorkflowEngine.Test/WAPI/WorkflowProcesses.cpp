#include "WAPI/WAPI.h"
#include "WAPI/WAPIWorkflow.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
using namespace DataManager::DataBase;

void GetWorkflowProcesses()
{
	CM_CODEBLOCK(GetWorkflowProcesses)

	Response* response = new Response();
	char* acRet = getWorkflowList(response);
	if ( response->iCode == 0 )
	{
		cout << "WorkflowList[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving WorkflowList.[" << response->sMsg << "]" << endl;
	}
}

