#include "CommonDefines.h"

#include "WAPIReport.h"
#include "WAPIError.h"

#include "bOS.h"
#include "bOSStringUtils.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

//DB
#include "DataBaseHelper.h" 
#include "DBException.h"
using namespace DataManager::DataBase;

#include "Report.h"
#include "Reports.h"
using namespace DataManager::Panorama::WorkflowProcesses;

extern "C" ENGINE_API char* getReports(char* processID, Response* response)
{
	CM_CODEBLOCK(getReports)
	Reports vReports;
	vReports.setProcessId ( processID);

	try
	{
		DataBaseHelper::instance()->getReports (vReports);
	}
	catch ( DBException& dbErr)
	{
		CM_TRACE_ERROR("Impossible to retrieve Report.Err[" << dbErr.getMessage() << "]")
		response->iCode = 0;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());
		return NULL;
	}

	return StringUtils::toChar (vReports.getXMLString(0));
}
