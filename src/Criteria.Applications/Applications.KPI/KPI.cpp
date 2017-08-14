#include "KPI.h"

#include "bOS/bOSSQLConnectionManager.h"
#include "bOS/bOSSQLConnectionData.h"
#include "bOS/bOSSQLTable.h"
#include "bOS/bOSSQLCommand.h"
#include "bOS/bOSSQLException.h"
#include "bOS/bOSSQLSmartConnection.h"
#include "bOS/bOSResultSet.h"

#include "Scenario/FormalParameters.h"
#include "Scenario/FormalParameter.h"
using namespace DataManager::Panorama::Common;

#include "Scenario/ApplicationFunction.h"
#include "Scenario/ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "Scenario/ApplicationTemplate.h"

#include "Scenario/DataBaseHelper.h"
#include "Scenario/DBException.h"
using namespace DataManager::DataBase;

#include "bOS/Tracer.h"

const String KPI_NAME = "KPI";
const String KPI_VALUE = "Value";
const String KPI_ID = "ID";

KPI::KPI()
{
}

KPI::~KPI()
{
}

char* KPI::StartKPI(char* acFunction)
{
	long lCode = 0;
	String sMessage="Parametro Manacante";

	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	String sKpiName;
	String sKpiValue;
	String sID;
	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), KPI_NAME.c_str() ) )
		{
			sKpiName = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), KPI_VALUE.c_str() ) )
		{
			sKpiValue = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), KPI_ID.c_str() ) )
		{
			sID = parameter->getValue().c_str();
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.";
		}
	}

	ApplicationFunctionResult result;

	//action
	if ( ( sKpiName.length() > 0) && ( sID.length() > 0) )
	{
		try
		{
			KPI::StartKPI ( sID.c_str(), sKpiName.c_str(), sKpiValue.c_str() );
		}
		catch ( bOS::SQL::SQLException& sqlErr )
		{
			lCode =1000;
			sMessage = sqlErr.getMessage();
		}
	}
	else
	{
		lCode =1000;
		sMessage = "E' necessario passare sia il preventivo che il suo id.";
	}

	
	result.setCode (lCode);
	result.setMessage (sMessage);

	return StringUtils::toChar (result.getXMLString(1));
}


void KPI::StartKPI(const char* acId, const char* acKpiName, const char* acKpiValue)
{
	CM_CODEBLOCK(CriteriaComponent::CreateKPI)

	//utilizza la sessione di Criteria.
	bOS::SQL::SQLConnectionManager& sqlManager = DataBaseHelper::instance()->getManager();

	bOS::SQL::SQLConnection* connection = NULL;
	try
	{
		connection = sqlManager.get();
	}	
	catch ( bOS::SQL::SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw;
	}

	bOS::SQL::SQLSmartConnection smartConnection(&sqlManager, connection);
	StringBuffer sSQL;

	try
	{
		//TODO
		//connection->setAutoCommit (false);
		connection->setAutoCommit (true);
		//connection->beginTrans();
		
		sSQL.clear();
		sSQL.append ("insert into `sf_Kpi` (Id, Name, Value, StartDate) values ('");
		sSQL.append (acId);
		sSQL.append ("','");
		sSQL.append (acKpiName);
		sSQL.append ("','");
		sSQL.append (acKpiValue);
		sSQL.append ("',now());");

		CM_TRACE_DEBUG(sSQL.getData())
		connection->execute (sSQL.getData());

		//connection->commit();
	}
	catch ( bOS::SQL::SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")

		/*try
		{
			
			if ( connection->isConnected () )
				connection->rollback();
		}
		catch ( ... )
		{
		}*/

		throw;
	}
}

char* KPI::StopKPI(char* acFunction)
{
	long lCode = 0;
	String sMessage="Parametro Manacante";

	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	String sKpiName;
	String sKpiValue;
	String sID;
	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), KPI_NAME.c_str() ) )
		{
			sKpiName = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), KPI_VALUE.c_str() ) )
		{
			sKpiValue = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), KPI_ID.c_str() ) )
		{
			sID = parameter->getValue().c_str();
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.";
		}
	}

	ApplicationFunctionResult result;

	//action
	if ( ( sKpiName.length() > 0) && ( sID.length() > 0) )
	{
		try
		{
			KPI::StopKPI ( sID.c_str(), sKpiName.c_str(), sKpiValue.c_str() );
		}
		catch ( bOS::SQL::SQLException& sqlErr )
		{
			lCode =1000;
			sMessage = sqlErr.getMessage();
		}
	}
	else
	{
		lCode =1000;
		sMessage = "E' necessario passare sia il preventivo che il suo id.";
	}

	
	result.setCode (lCode);
	result.setMessage (sMessage);

	return StringUtils::toChar (result.getXMLString(1));
}


void KPI::StopKPI(const char* acId, const char* acKpiName, const char* acKpiValue)
{
	CM_CODEBLOCK(CriteriaComponent::CreateKPI)

	//utilizza la sessione di Criteria.
	bOS::SQL::SQLConnectionManager& sqlManager = DataBaseHelper::instance()->getManager();

	bOS::SQL::SQLConnection* connection = NULL;
	try
	{
		connection = sqlManager.get();
	}	
	catch ( bOS::SQL::SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw;
	}

	bOS::SQL::SQLSmartConnection smartConnection(&sqlManager, connection);
	StringBuffer sSQL;

	try
	{
		//TODO
		//connection->setAutoCommit (false);
		connection->setAutoCommit (true);
		//connection->beginTrans();
		
		sSQL.clear();
		sSQL.append ("update `sf_Kpi` set StopDate=");
		sSQL.append ("now() where Id='");
		sSQL.append (acId);
		sSQL.append ("' and Name='");
		sSQL.append (acKpiName);
		sSQL.append ("' and Value='");
		sSQL.append (acKpiValue);
		sSQL.append ("';");
		

		CM_TRACE_DEBUG(sSQL.getData())
		connection->execute (sSQL.getData());

		//connection->commit();
	}
	catch ( bOS::SQL::SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")

		/*try
		{
			
			if ( connection->isConnected () )
				connection->rollback();
		}
		catch ( ... )
		{
		}*/

		throw;
	}
}

ApplicationTemplate* application = NULL;

extern "C" DLL_CRITERIA_KPI_API void InstanceApplication(char* acApplicationName)
{
	if ( application == NULL)
	{	application = new ApplicationTemplate();
		application->init("KPI");

		/*
		*/
		application->addCallBack("Start", KPI::StartKPI);
		application->addCallBack("Stop", KPI::StopKPI);
	}
}

extern "C" DLL_CRITERIA_KPI_API void DeleteApplication(char* acApplicationName)
{
	//TODO: delete application;
}

extern "C" DLL_CRITERIA_KPI_API char* ExecuteApplicationApi(char* acFunction)
{
	return application->executeApi (acFunction);
}