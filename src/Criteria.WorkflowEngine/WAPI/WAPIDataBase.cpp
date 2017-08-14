#include "CommonDefines.h"

#include "WAPIDataBase.h"
#include "WAPIError.h"

#include "bOS.h"
#include "bOSStringUtils.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

//DB
#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

extern "C" ENGINE_API void ExecuteSQLCommand(Response* response, const char* acSQLCommand)
{
	CM_CODEBLOCK(WAPIDataBase::ExecuteSQLCommand)
	response->iCode = 0;

	try
	{
		int iRecord = DataBaseHelper::instance()->ExecuteSQLCommand (acSQLCommand);
		if ( iRecord == 0)
		{
			response->iCode = 1;
			response->sMsg = StringUtils::toChar ("No record add, update or delete!");
		}
	}
	catch ( DBException& dbErr )
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());
	}
}

