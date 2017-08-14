#include "WAPI/WAPI.h"
#include "WAPI/WAPIReport.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
using namespace DataManager::DataBase;

void GetReports(long lProcessID)
{
	CM_CODEBLOCK(GetReports)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getReports(lProcessID, response);
	if ( response->iCode == 0 )
	{
		cout << "Activity[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getActivityList Error[" << response->sMsg << "]")
	}
}