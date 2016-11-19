#include "CriteriaComponent.h"

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

const String IDMASTER_PARAMETER		= "IdMaster";
const String NRSLAVES_PARAMETER		= "NrSlaves";
const String IDSLAVE_PARAMETER		= "IdSlave";
const String ALLRELEASED_PARAMETER	= "AllReleased";


const String KPI_NAME = "KPI";
const String KPI_VALUE = "Value";
const String KPI_ID = "ID";

CriteriaComponent::CriteriaComponent()
{
}

CriteriaComponent::~CriteriaComponent()
{
}

char* CriteriaComponent::MakeSlaves(char* acFunction)
{
	long lCode = 0;
	String sMessage="Parametro Manacante";

	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	int iNrSlaves=0;
	String sIdMaster;
	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), IDMASTER_PARAMETER.c_str() ) )
		{
			sIdMaster = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), NRSLAVES_PARAMETER.c_str() ) )
		{
			iNrSlaves = atoi(parameter->getValue().c_str());
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.";
		}
	}

	ApplicationFunctionResult result;

	//action
	if ( ( sIdMaster.length() > 0) && (iNrSlaves > 0 ) )
	{
		try
		{
			CriteriaComponent::MakeSlaves ( sIdMaster.c_str(), iNrSlaves );
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

void CriteriaComponent::MakeSlaves(const char* idMaster, int nrSlave)
{
	CM_CODEBLOCK(CriteriaComponent::MakeSlaves)

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
		
		for ( unsigned int i=0; i<nrSlave; i++)
		{
			sSQL.clear();
			sSQL.append ("insert into `ProcessMasterSlave` (IdMaster, IdSlave, IsBusy) values ('");
			sSQL.append (idMaster);
			sSQL.append ("',");
			sSQL.append ((int)i);
			sSQL.append (",0)");

			CM_TRACE_DEBUG(sSQL.getData())
			connection->execute (sSQL.getData());
		}

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

char* CriteriaComponent::GetSlave(char* acFunction)
{
	CM_CODEBLOCK(CriteriaComponent::GetSlave)

	long lCode = 0;
	String sMessage="";

	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	String sIdMaster;
	int iIdSlave = 0;
	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), IDMASTER_PARAMETER.c_str() ) )
		{
			sIdMaster = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), IDSLAVE_PARAMETER.c_str() ) )
		{
			iIdSlave = atoi(parameter->getValue().c_str());
		} 
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.";
		}
	}

	ApplicationFunctionResult result;

	if ( sIdMaster.length() > 0 ) 
	{
		
		try
		{
			CriteriaComponent::GetSlave(sIdMaster.c_str(), iIdSlave);
			/*
			FormalParameter parameter(ORDER_PARAMETER, sOrder );
			parameter.setXMLType();
			result.getParameters().addParameter ( parameter);
			*/
			CM_TRACE_DEBUG("Slave[" << iIdSlave << "]")
			result.getParameters().addParameter ( FormalParameter(IDSLAVE_PARAMETER, StringUtils::toString ( iIdSlave) ));
		}
		catch ( bOS::SQL::SQLException& sqlErr )
		{
			lCode =1000;
			sMessage = sqlErr.getMessage();
		}
	}
	else
	{
		lCode = 1000;
		sMessage = "E' necessario indicare IdPreventivo.";
	}

	
	result.setCode (lCode);
	result.setMessage (sMessage);

	CM_TRACE_DEBUG(result.getXMLString(1))

	return StringUtils::toChar (result.getXMLString(1));
}

void CriteriaComponent::GetSlave(const char* idMaster, int& idSlave)
{
	CM_CODEBLOCK(CriteriaComponent::GetSlave)

	//
	if ( idSlave != 0 )
	{
		return;
	}

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

	int idSlaveFromDB;
	StringBuffer sSQL_select;
	
	sSQL_select.append ("select IdSlave from ProcessMasterSlave where IdMaster='");
	sSQL_select.append (idMaster);
	sSQL_select.append ("' and ");
	if ( idSlave == 0 )
	{
		sSQL_select.append ("IsBusy=0");
	}
	else
	{
		sSQL_select.append ("idSlave=");
		sSQL_select.append(idSlave);
	}

	long lRecordManaged=0;
	do 
	{
		try
		{
			CM_TRACE_DEBUG(sSQL_select.getData())
			bOS::SQL::ResultSet* rs = connection->executeQuery (sSQL_select.getData());
			lRecordManaged = rs->getRecordCount(); 

			CM_TRACE_DEBUG("Retrivied Record Nr[" << lRecordManaged <<"]")

			if ( lRecordManaged == 0 )
			{
				//Error
				rs->close();
				throw bOS::SQL::SQLException(DB_RECORD_NOT_FOUND);
			}
			
			rs->moveNext ();
			bOS::SQL::ResultSetRecord* record = rs->getRecord();
			unsigned int uiSize = record->size();

			for ( unsigned int i=0;i<uiSize;i++)
			{
				bOS::SQL::ResultSetField* field = record->at(i);

				/*if ( !strcmp(field->sName.c_str(), "XmlOrder") )
				{
					sOrder = field->sValue.getData();
				}
				else */if ( !strcmp(field->sName.c_str(), "IdSlave") )
				{
					idSlaveFromDB = atoi(field->sValue.getData());
				}
			}
			rs->close();

			StringBuffer sSQL_update;

			if ( idSlave == 0 )
			{
				sSQL_update.append("update ProcessMasterSlave set IsBusy=1 where IdSlave =");
				sSQL_update.append (idSlaveFromDB);
				sSQL_update.append (" and IdMaster='");
				sSQL_update.append (idMaster);
				sSQL_update.append ("'");

				CM_TRACE_DEBUG(sSQL_update.getData())
				lRecordManaged=connection->execute (sSQL_update.getData());
			}
		}
		catch ( bOS::SQL::SQLException& sqlErr)
		{
			CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
			throw;
		}
	} while ( lRecordManaged == 0);

	idSlave = idSlaveFromDB ;

	//return sOrder;
}

char* CriteriaComponent::ReleaseSlave(char* acFunction)
{
	long lCode = 0;
	String sMessage="";

	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	String sIdMaster;
	int iIdSlave=-1;
	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), IDMASTER_PARAMETER.c_str() ) )
		{
			sIdMaster = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), IDSLAVE_PARAMETER.c_str() ) )
		{
			iIdSlave = atoi(parameter->getValue().c_str());
		} 
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.";
		}
	}

	ApplicationFunctionResult result;

	if ( sIdMaster.length() > 0 && (iIdSlave >= 0)) 
	{
		string sAllReleased = "0";
		try
		{
			bool bNoOrder = CriteriaComponent::ReleaseSlave(sIdMaster.c_str(), iIdSlave);
			if (bNoOrder) 
			{
				sAllReleased ="1";
				sMessage = "Ordini Evasi";
			}

			Common::FormalParameter released(ALLRELEASED_PARAMETER, sAllReleased);
			result.getParameters().addParameter ( released);
		}
		catch ( bOS::SQL::SQLException& sqlErr )
		{
			lCode =1000;
			sMessage = sqlErr.getMessage();
		}
	}
	else
	{
		lCode = 1000;
		sMessage = "E' necessario indicare IdPreventivo.";
	}

	
	result.setCode (lCode);
	result.setMessage (sMessage);

	return StringUtils::toChar (result.getXMLString(1));
}

char* CriteriaComponent::NoSlave(char* acFunction)
{
	long lCode = 0;
	String sMessage="";

	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	String sIdMaster;
	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), IDMASTER_PARAMETER.c_str() ) )
		{
			sIdMaster = parameter->getValue().c_str();
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.";
		}
	}

	ApplicationFunctionResult result;

	if ( sIdMaster.length() > 0 ) 
	{
		string sAllReleased = "0";
		try
		{
			bool bNoOrder = CriteriaComponent::NoSlave(sIdMaster.c_str());
			if (bNoOrder) 
			{
				sAllReleased ="1";
				sMessage = "Ordini Evasi";
			}

			Common::FormalParameter released(ALLRELEASED_PARAMETER, sAllReleased);
			result.getParameters().addParameter ( released);
		}
		catch ( bOS::SQL::SQLException& sqlErr )
		{
			lCode =1000;
			sMessage = sqlErr.getMessage();
		}
	}
	else
	{
		lCode = 1000;
		sMessage = "E' necessario indicare IdPreventivo.";
	}

	
	result.setCode (lCode);
	result.setMessage (sMessage);

	return StringUtils::toChar (result.getXMLString(1));
}

bool CriteriaComponent::ReleaseSlave(const char* idMaster, int idSlave)
{
	CM_CODEBLOCK(CriteriaComponent::ReleaseSlave)

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
	sSQL.append ("delete from ProcessMasterSlave where IdSlave=");
	sSQL.append(idSlave);
	sSQL.append(" and IdMaster='");
	sSQL.append(idMaster);
	sSQL.append("'");

	long lRecord=0;
	try
	{
		lRecord = connection->execute (sSQL.getData());
	}
	catch ( bOS::SQL::SQLException&)
	{
		//error
		throw;
	}

	if ( lRecord == 0 )
	{
		throw bOS::SQL::SQLException("NO Record");
	}

	sSQL.clear();
	sSQL.append ("select count(IdMaster) from ProcessMasterSlave Where IdMaster='");
	sSQL.append(idMaster);
	sSQL.append("'");

	lRecord=0;
	try
	{
		bOS::SQL::ResultSet* rs = connection->executeQuery (sSQL.getData());
		rs->moveNext();
		lRecord = atoi(rs->getRecord()->at(0)->sValue.getData());
		rs->close();
	}
	catch ( bOS::SQL::SQLException&)
	{
		//error
		throw;
	}

	return ( lRecord == 0 );
}

bool CriteriaComponent::NoSlave(const char* idMaster)
{
	CM_CODEBLOCK(CriteriaComponent::NoSlave)

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
	sSQL.append ("select count(IdMaster) from ProcessMasterSlave Where IdMaster='");
	sSQL.append(idMaster);
	sSQL.append("'");

	long lRecord=0;
	try
	{
		CM_TRACE_DEBUG(sSQL.getData())
		bOS::SQL::ResultSet* rs = connection->executeQuery (sSQL.getData());
		rs->moveNext();
		lRecord = atoi(rs->getRecord()->at(0)->sValue.getData());
		rs->close();
	}
	catch ( bOS::SQL::SQLException&)
	{
		//error
		throw;
	}

	return ( lRecord == 0 );
}

ApplicationTemplate* application = NULL;

extern "C" DLL_CRITERIA_COMPONENT_API void InstanceApplication(char* acApplicationName)
{
	if ( application == NULL)
	{	application = new ApplicationTemplate();
		application->init("CriteriaComponent");

		/*
		*/
		application->addCallBack("MakeSlaves", CriteriaComponent::MakeSlaves);
		application->addCallBack("GetSlave", CriteriaComponent::GetSlave);
		application->addCallBack("ReleaseSlave", CriteriaComponent::ReleaseSlave);
		application->addCallBack("NoSlave", CriteriaComponent::NoSlave);
	}
}

extern "C" DLL_CRITERIA_COMPONENT_API void DeleteApplication(char* acApplicationName)
{
	//TODO: delete application;
}

extern "C" DLL_CRITERIA_COMPONENT_API char* ExecuteApplicationApi(char* acFunction)
{
	return application->executeApi (acFunction);
}