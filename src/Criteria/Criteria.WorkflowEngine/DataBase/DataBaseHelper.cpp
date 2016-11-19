#include "DataBaseHelper.h"
using namespace DataManager::DataBase;

#include "bOSSystem.h"
using namespace bOS::CoreSystem;

#include "bOSXMLHelper.h"
#include "bOSXMLException.h"
#include "bOSFileSystemException.h"

#include "DBException.h"
using namespace DataManager;

//DataModel
#include "DataBase.h"
#include "Connections.h"
#include "Connection.h"
#include "mySQLConnection.h"
#include "ODBCConnection.h"
#include "SQLiteConnection.h"
#include "FileSystemConnection.h"

#include "DataBaseTemplate.h"

#include "bOSSQLException.h"
#include "bOSSQLConnectionData.h"
#include "bOSmySQLConnectionData.h"
#include "bOSSQLiteConnectionData.h"

#include "bOSUniqueID.h"

using namespace DataManager::Panorama::WorkflowProcesses;
using namespace DataManager::Panorama::Common;
using namespace DataManager::Panorama::WorkflowParticipantsData;
using namespace DataManager::Panorama::WorkflowDataTypes;
using namespace DataManager::Panorama::WorkflowServices;
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "DataBaseTemplate.h"
#include "FileSystemDataBase.h"

DataBaseHelper* DataBaseHelper::_instance = NULL;

String DataBaseHelper::WORKFLOW_EXTENSION	= ".xml";

//useful for GetDirectory
String DataBaseHelper::DATABASE_TAG_DIRECTORY	= "Scenario.DB";

DataBaseHelper* DataBaseHelper::instance()
{
	if ( _instance == NULL ) 
	{
		_instance = new DataBaseHelper();
	}

	return _instance;
}

void DataBaseHelper::deinstance()
{
	if ( _instance != NULL ) 
	{
		delete _instance;
	}

	_instance = NULL;
}

DataBaseHelper::DataBaseHelper()
{
	bOS::XML::XMLHelper::initialize();
	bOpened=false;
}

DataBaseHelper::~DataBaseHelper()
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		vDataBases.at(i)->close();
		delete vDataBases.at(i);
	}

	vDataBases.clear();

	bOS::XML::XMLHelper::terminate();
}

void DataBaseHelper::open(String sConfigurationFile)
{
	CM_CODEBLOCK(DataBaseHelper::open)

	if ( bOpened ) 
	{
		CM_TRACE_WARNING("DataBase already opened!")
		return;
	}

	DataManager::Panorama::DataBase::DataBase dbFile;

	CM_TRACE_INFO("Loading File[" << sConfigurationFile << "]")
		dbFile.load(sConfigurationFile.c_str());

	DataManager::Panorama::DataBase::Connections& vConnections = dbFile.getConnections();
	unsigned int uiSize = vConnections.size();
	CM_TRACE_INFO("Connection Nr[" << uiSize << "]")
	
	DataManager::Panorama::DataBase::Connection* connection = NULL;
	DataBase::DataBaseTemplate* db = NULL;
	
	for ( unsigned int i=0; i<uiSize; i++)
	{
		connection = (DataManager::Panorama::DataBase::Connection*)vConnections.at(i);

		if ( connection->getIdType() == 1 )//mySQL
		{
			CM_TRACE_INFO("Analysing mySQL Connection")

			db = new DataBaseTemplate(bOS::SQL::SQLConnectionManager::MYSQL);
			bOS::SQL::mySQL::mySQLConnectionData mySQLconnectionData;
			DataManager::Panorama::DataBase::mySQLConnection* myConnection = (DataManager::Panorama::DataBase::mySQLConnection*)connection;
			mySQLconnectionData.sHost = myConnection->getHost();
			mySQLconnectionData.iPort = myConnection->getPort();
			mySQLconnectionData.sDB = myConnection->getDataBase();
			mySQLconnectionData.sUser = myConnection->getUser();
			mySQLconnectionData.sPassword = myConnection->getPassword();

			CM_TRACE_INFO("Connecting to mySQL. Host[" << mySQLconnectionData.sHost << "] Port[" << mySQLconnectionData.iPort << "]")
			CM_TRACE_INFO("DataBase[" << mySQLconnectionData.sDB << "] User[" << mySQLconnectionData.sUser << "] Password [" << mySQLconnectionData.sPassword << "]") 

			try
			{
				db->open(&mySQLconnectionData, connection->getPool());
			}
			catch ( bOS::SQL::SQLException& sqlErr)
			{
				throw DBException(sqlErr.getMessage());
			}

		}
		else if ( connection->getIdType() == 2 )//ODBC
		{
			/*db = new DataBaseTemplate(bOS::SQL::SQLConnectionManager::ODBC_INTERFACE);

			bOS::SQL::ODBC::ODBCConnectionData odbcConnectionData;
			DataManager::Panorama::DataBase::ODBCConnection* myODBCConnection = (DataManager::Panorama::DataBase::ODBCConnection*)connection;
			odbcConnectionData.sDsn = myODBCConnection->getDsn();
			odbcConnectionData.sUser = myODBCConnection->getUser();
			odbcConnectionData.sPassword = myODBCConnection->getPassword();

			db->open(&odbcConnectionData, connection->getPool());
			*/

		}
#ifdef _USE_SQLITE3_
		else if ( connection->getIdType() == 3 )//SQLite
		{
			db = new DataBaseTemplate(bOS::SQL::SQLConnectionManager::SQLITE3);

			bOS::SQL::SQLite3::SQLiteConnectionData sqliteConnectionData;
			DataManager::Panorama::DataBase::SQLiteConnection* mySQLiteConnection = (DataManager::Panorama::DataBase::SQLiteConnection*)connection;
			sqliteConnectionData.sDB = mySQLiteConnection->getDataBase();
			sqliteConnectionData.sPath = mySQLiteConnection->getPath();

			db->open(&sqliteConnectionData, connection->getPool());

		}
#endif
		else if ( connection->getIdType() == 4 )//FileSystem
		{
			CM_TRACE_INFO("Analysing FileSsystem Connection")
			db = new FileSystem::FileSystemDataBase();
			db->open((DataManager::Panorama::DataBase::FileSystemConnection*)connection);
		}

		db->setXMLConnection ( connection);
		vDataBases.push_back (db);
	}

	bOpened = true;
}

void DataBaseHelper::close()
{
	CM_CODEBLOCK(DataBaseHelper::close)

	if ( bOpened )
	{
		unsigned int uiSize = vDataBases.size();
		for ( unsigned int i=0; i<uiSize; i++)
		{
			vDataBases.at(i)->close();
		}
	}
	else
	{
		CM_TRACE_WARNING("DataBase not opened!")
	}
}

bOS::IO::FilesList DataBaseHelper::getWorkflowList()
{
	for ( unsigned int i=0; i<vDataBases.size();i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessTemplates() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			return db->getWorkflowList();
		}
	}
}

bOS::IO::FilesList DataBaseHelper::getFormsList()
{
	for ( unsigned int i=0; i<vDataBases.size();i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageForms() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			return db->getFormsList();
		}
	}
}

bOS::CoreString::String DataBaseHelper::getForm(const char* acFormName)
{
	for ( unsigned int i=0; i<vDataBases.size();i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageForms() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			return db->getForm(acFormName);
		}
	}
}

void DataBaseHelper::setForm(const char* acFormName, const char* acJsContent)
{
	for ( unsigned int i=0; i<vDataBases.size();i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageForms() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			return db->setForm(acFormName, acJsContent);
		}
	}
}

String DataBaseHelper::createProcess(const char* acWorkflowName, WorkflowProcess& process, bool b2Prepared)
{
	CM_CODEBLOCK(DataBaseHelper::createProcess)

	WorkflowProcess* workflow = NULL;
	for ( unsigned int i=0; i<vDataBases.size();i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessTemplates() )
			workflow = db->getProcessTemplate(acWorkflowName);
	}
	CM_TRACE_CODEPATH("Process [" << acWorkflowName << "] retrieved. [" << workflow->getProcessId() << "]")

	//TODO: da template ad instance con il parsing xml?
	XMLNode* node = workflow->getXMLNode(0);
	process.init(node);
	delete node;
	delete workflow;

	process.setProcessId ( bOS::Utils::UniqueID::getNewValue().c_str());
	CM_TRACE_CODEPATH("Process Instance created from template. ID[" << process.getProcessId() << "]")

	CM_TRACE_CODEPATH("Retrieving activities from process")
	WorkflowProcesses::Activities& vActivities = process.getActivities();
	unsigned int uiSize = vActivities.size();
	CM_TRACE_CODEPATH("Activities retrieved [" << uiSize <<"]")
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Activity* activity = (Activity*)vActivities.at(i);
		activity->setCreated();
	}
	process.setParentProcess("");
	process.setTaskParentProcess("");
	process.setCreated();
	String processId="";
	for ( unsigned int i=0; i<vDataBases.size();i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);
		if ( db->getXMLConnection().manageProcessInstances() ) {
			db->insertProcess(processId, process, b2Prepared);
		}
	}
	
	return process.getProcessId();
}

void DataBaseHelper::addWorkflow(const char* acWorkflow)
{
	CM_CODEBLOCK(DataBaseHelper::addWorkflow)

	WorkflowProcess workflow;
	workflow.init (acWorkflow);

	for ( unsigned int i=0; i<vDataBases.size();i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);
		if ( db->getXMLConnection().manageProcessTemplates() ) {
			db->addWorkflow(&workflow);
		}
	}

	throw DBException(XFS_FILE_NOT_WRITE);
}


//Users
void DataBaseHelper::getUser(User& user)
{
	for ( unsigned int i=0; i<vDataBases.size();i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageUsers() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getUser(user);
			break;
		}
	}
}

void DataBaseHelper::getUsers(DataManager::Panorama::WorkflowParticipantsData::Users& vUsers)
{
	for ( unsigned int i=0; i<vDataBases.size();i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageUsers() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getUsers(vUsers);
			break;
		}
	}
}

void DataBaseHelper::addUser(const char* acUser)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageUsers() )
		{
			db->addUser(acUser);
		}
	}
}

void DataBaseHelper::updateUser(const char* acUser)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageUsers() )
		{
			db->updateUser(acUser);
		}
	}
}

void DataBaseHelper::deleteUser(const char* acUserKey)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageUsers() )
		{
			db->deleteUser(acUserKey);
		}
	}
}

//Roles
void DataBaseHelper::getRoles(DataManager::Panorama::WorkflowParticipantsData::Roles& vRoles)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageRoles() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getRoles(vRoles);
			break;
		}
	}
}

void DataBaseHelper::getRole(DataManager::Panorama::WorkflowParticipantsData::Role& role)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageRoles() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getRole(role);
			break;
		}
	}
}

void DataBaseHelper::addRole(const char* acRole)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageRoles() )
		{
			db->addRole(acRole);
		}
	}
}

void DataBaseHelper::updateRole(const char* acRole)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageRoles() )
		{
			db->updateRole(acRole);
		}
	}
}

void DataBaseHelper::deleteRole(const char* acRoleKey)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageRoles() )
		{
			db->deleteRole(acRoleKey);
		}
	}
}

void DataBaseHelper::addUserToRole(const char* acUser, const char* acRoleKey)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageRoles() )
		{
			db->addUserToRole(acUser, acRoleKey);
		}
	}
}

void DataBaseHelper::deleteUserFromRole(const char* acUserKey, const char* acRoleKey)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageRoles() )
		{
			db->deleteUserFromRole(acUserKey, acRoleKey);
		}
	}
}

void DataBaseHelper::getRolesByUser(const char* acUserKey, DataManager::Panorama::WorkflowParticipantsData::Roles& roles)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageRoles() )
		{
			db->getRolesByUser(acUserKey, roles);
		}
	}
}

//
void DataBaseHelper::getDataTypes(DataManager::Panorama::WorkflowDataTypes::DataTypes& vDataTypes)
{
	CM_CODEBLOCK(DataBaseHelper::getDataTypes)

	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageDataTypes() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getDataTypes(vDataTypes);
			break;
		}
	}
}

void DataBaseHelper::getDataType(DataManager::Panorama::WorkflowDataTypes::DataType& datatype)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageDataTypes() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getDataType(datatype);
			break;
		}
	}
}

string DataBaseHelper::GetValueFromDataType(const string& sDataType, const String& sValueKey)
{
	WorkflowDataTypes::DataType dataType;
	dataType.setKey ( sDataType);

	this->getDataType(dataType);

	DataTypeValue* rValue = dataType.getDataTypeValues().getValue(sValueKey);

	if ( rValue == NULL )
	{
		throw DBException("Impossible to retrieve ValueKey");
	}

    return rValue->getValue();
}


//
void DataBaseHelper::getServices(DataManager::Panorama::WorkflowServices::Services& vServices)
{
	CM_CODEBLOCK(DataBaseHelper::getServices)

	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageServices() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getServices(vServices);
			break;
		}
	}

}

void DataBaseHelper::getServicesForUser(const char* acUser, DataManager::Panorama::WorkflowServices::Services& vServices)
{
	CM_CODEBLOCK(DataBaseHelper::getServicesForUser)

	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageServices() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getServicesForUser(acUser, vServices);
			break;
		}
	}
}

void DataBaseHelper::addService (const char* acService)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageServices() )
		{
			db->addService(acService);
		}
	}
}


void DataBaseHelper::deleteService(const char* acServiceName)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageServices() )
		{
			db->deleteService(acServiceName);
		}
	}
}

//
void DataBaseHelper::getApplications(DataManager::Panorama::WorkflowApplicationsData::Applications& vApplications)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageApplications() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getApplications(vApplications);
			break;
		}
	}
}

void DataBaseHelper::getApplication(DataManager::Panorama::WorkflowApplicationsData::Application& application)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageApplications() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			Applications vApplications;
			db->getApplications(vApplications);

			Application* _application = vApplications.get(application.getName().c_str() );

			if ( _application == NULL ) 
			{
				throw DBException(DB_RECORD_NOT_FOUND);
			}

			XMLNode* node = _application->getXMLNode(0);
			application.init ( node );
			delete node;

			break;
		}
	}
}

DataManager::Panorama::WorkflowProcesses::WorkflowProcess* DataBaseHelper::getProcessInstance(const char* processId)
{
	CM_CODEBLOCK(DataBaseHelper::getProcessInstance)

	WorkflowProcess* process = NULL;
	
	CM_TRACE_DEBUG("Retrieving Process[" << processId << "]")
	//modify by mfarina on 05/12/2015 to avoid attributes setted to old value
	//process=processesHandler.loadProcess(processId);
	if ( process == NULL )
	{
		CM_TRACE_DEBUG("Load Process[" << processId << "]");

		process = new WorkflowProcess();
		process->setProcessId (processId );
		
		try
		{
			unsigned int uiSize = vDataBases.size();
			for ( unsigned int i=0; i<uiSize; i++)
			{
				DataBaseTemplate* db = vDataBases.at(i);

				if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
				{
					db->getProcessInstance(*process);
					break;
				}
			}
		}
		catch ( DBException&) 
		{
			throw;
		}

		processesHandler.addProcess(process);
	}

	return process;
}

DataManager::Panorama::WorkflowProcesses::WorkflowProcess* DataBaseHelper::LoadProcessInstance(const char* processId)
{
	CM_CODEBLOCK(DataBaseHelper::LoadProcessInstance)

	WorkflowProcess* process = NULL;
	
	CM_TRACE_DEBUG("Retrieving Process[" << processId << "]")
	process=processesHandler.loadProcess(processId);
	bool bProcessToLoad = false;
	if ( process == NULL )
	{
		CM_TRACE_DEBUG("Load Process[" << processId << "]");

		process = new WorkflowProcess();
		process->setProcessId (processId );

		bProcessToLoad = true;
		
	}
		
	try
	{
		unsigned int uiSize = vDataBases.size();
		for ( unsigned int i=0; i<uiSize; i++)
		{
			DataBaseTemplate* db = vDataBases.at(i);

			if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
			{
				db->getProcessInstance(*process);
				break;
			}
		}
	}
	catch ( DBException&) 
	{
		throw;
	}

	if ( bProcessToLoad )
	{
		processesHandler.addProcess(process);
	}

	return process;
}


bOS::CoreString::String DataBaseHelper::getProcessStatus(const char* processId)
{
	CM_CODEBLOCK(DataBaseHelper::getProcessStatus)

	try
	{
		unsigned int uiSize = vDataBases.size();
		for ( unsigned int i=0; i<uiSize; i++)
		{
			DataBaseTemplate* db = vDataBases.at(i);

			if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
			{
				return db->getProcessStatus(processId);
			}
		}
	}
	catch ( DBException&) 
	{
		throw;
	}

	throw new DBException("Process not found");
}


DataManager::Panorama::WorkflowProcesses::WorkflowProcess* DataBaseHelper::getProcessHeader(const char* processId)
{
	CM_CODEBLOCK(DataBaseHelper::getProcessHeader)

	WorkflowProcess* process = NULL;
	
	CM_TRACE_DEBUG("Retrieving Process[" << processId << "]")
	//process=processesHandler.loadProcess(lProcessId);
	if ( process == NULL )
	{
		CM_TRACE_DEBUG("Load Process[" << processId << "]");

		process = new WorkflowProcess();
		process->setProcessId (processId );
		
		try
		{
			unsigned int uiSize = vDataBases.size();
			for ( unsigned int i=0; i<uiSize; i++)
			{
				DataBaseTemplate* db = vDataBases.at(i);

				if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
				{
					db->getProcessHeader(*process);
					break;
				}
			}
		}
		catch ( DBException&) 
		{
			throw;
		}

		//processesHandler.addProcess(process);
	}

	return process;
}

DataManager::Panorama::WorkflowProcesses::WorkflowProcess* DataBaseHelper::getNewProcessHeader(const char* processId)
{
	CM_CODEBLOCK(DataBaseHelper::getProcessHeader)

	WorkflowProcess* process = NULL;
	
	CM_TRACE_DEBUG("Retrieving Process[" << processId << "]")
	//process=processesHandler.loadProcess(lProcessId);
	if ( process == NULL )
	{
		CM_TRACE_DEBUG("Load Process[" << processId << "]");

		process = new WorkflowProcess();
		process->setProcessId (processId );
		
		try
		{
			unsigned int uiSize = vDataBases.size();
			for ( unsigned int i=0; i<uiSize; i++)
			{
				DataBaseTemplate* db = vDataBases.at(i);

				if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
				{
					db->getNewProcessHeader(*process);
					break;
				}
			}
		}
		catch ( DBException&) 
		{
			throw;
		}

		//processesHandler.addProcess(process);
	}

	return process;
}

void DataBaseHelper::getProcesses(WorkflowProcesses::Processes& vProcesses)
{
	CM_CODEBLOCK(DataBaseHelper::getProcesses)

	try
	{
		unsigned int uiSize = vDataBases.size();
		for ( unsigned int i=0; i<uiSize; i++)
		{
			DataBaseTemplate* db = vDataBases.at(i);

			if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
			{
				db->getProcesses(vProcesses);
				break;
			}
		}
	}
	catch ( DBException&) 
	{
		throw;
	}
}

void DataBaseHelper::releaseProcess(WorkflowProcess* process)
{
	CM_CODEBLOCK(releaseProcess)
	processesHandler.releaseProcess(process->getProcessId(), false);
}

WorkflowProcess* DataBaseHelper::addUsersToProcess(WorkflowProcess* process)
{
	processesHandler.loadProcess(process->getProcessId());

	return process;
}

void DataBaseHelper::updateProcess(WorkflowProcess* process)
{
	CM_CODEBLOCK(DataBaseHelper::updateProcess)

	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() )
		{
			db->updateProcess(process);
		}
	}
}

void DataBaseHelper::insertReport(WorkflowProcesses::Report& report)
{
	CM_CODEBLOCK(DataBaseHelper::insertReport)
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageReports() )
		{
			db->insertReport(report);
		}
	}
}

void DataBaseHelper::getReports (WorkflowProcesses::Reports& vReports)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageReports() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getReports(vReports);
			break;
		}
	}
}



void DataBaseHelper::updateAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes)
{
	CM_CODEBLOCK(DataBaseHelper::updateAttributes)

	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() )
		{
			db->updateAttributes(vAttributes);
		}
	}
}

void DataBaseHelper::SetAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes)
{
	CM_CODEBLOCK(DataBaseHelper::SetAttributes)

	if ( vAttributes.size() == 0 )
		return;

	DataManager::Panorama::WorkflowRelevantData::Attribute* attribute = (DataManager::Panorama::WorkflowRelevantData::Attribute*)vAttributes.at(0);
	if ( attribute == NULL )
		return;

	//checking for Process inside ProcessHelper.
	WorkflowProcess* process = processesHandler.loadProcess(attribute->getProcessId() );
	if ( process != NULL )
	{
		CM_TRACE_DEBUG("Updating Process-InMemory Attribute")
		if ( attribute->getActivityId() == "" ) 
		{
			DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes2Update = process->getAttributes();
			vAttributes2Update.updateAttributes(vAttributes);

		}
		else
		{
			DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes2Update = process->getActivities().get(attribute->getActivityId())->getAttributes();
			vAttributes2Update.updateAttributes(vAttributes);
		}

		processesHandler.releaseProcess(attribute->getProcessId(), false);
	}

	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() )
		{
			db->updateAttributes(vAttributes);
		}
	}
}

void DataBaseHelper::updateActivity(DataManager::Panorama::WorkflowProcesses::Activity* activity, bool bRecursive)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() )
		{
			db->updateActivity(activity,bRecursive);
		}
	}
}

void DataBaseHelper::updateActivityCheckStatus(DataManager::Panorama::WorkflowProcesses::Activity* activity, string sStatus2Check)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() )
		{
			db->updateActivityCheckStatus(activity, sStatus2Check);
		}
	}
}

void DataBaseHelper::updateActivityNoOwner(DataManager::Panorama::WorkflowProcesses::Activity* activity)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() )
		{
			db->updateActivityNoOwner(activity);
		}
	}
}

void DataBaseHelper::getActivities(DataManager::Panorama::WorkflowProcesses::Activities& vActivities, String sStatus, String sOwner, bool bOnlyMine)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getActivities(vActivities, sStatus, sOwner, bOnlyMine);
			break;
		}
	}
}

int DataBaseHelper::ExecuteSQLCommand(const char* acSQL)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			return db->ExecuteSQLCommand(acSQL);
			break;
		}
	}

	return 0;
}


void DataBaseHelper::getAllActivities(WorkflowProcesses::Activities& vActivities, String sOwner, bool bNotMine)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getAllActivities(vActivities,  sOwner, bNotMine);
			break;
		}
	}
}

void DataBaseHelper::getAllMyActivities(WorkflowProcesses::Activities& vActivities, String sOwner)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getAllMyActivities(vActivities,  sOwner);
			break;
		}
	}
}

void DataBaseHelper::getNotifies(DataManager::Panorama::WorkflowProcesses::Activities& vActivities, String sOwner)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getNotifies(vActivities, sOwner);
			break;
		}
	}
}

void DataBaseHelper::getActivityRunningNotifies(DataManager::Panorama::WorkflowProcesses::Activities& vActivities, String sOwner)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getActivityRunningNotifies(vActivities, sOwner);
			break;
		}
	}
}

void DataBaseHelper::getAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getAttributes(vAttributes);
			break;
		}
	}
}

void DataBaseHelper::getProcessAttribute(const char* processId, WorkflowRelevantData::Attribute& attributes)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getProcessAttribute(processId, attributes);
			break;
		}
	}
}

void DataBaseHelper::getActivity(DataManager::Panorama::WorkflowProcesses::Activity& activity)
{
	CM_CODEBLOCK(DataBaseHelper::getActivity)

	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->getActivity(activity);
			break;
		}
	}
}
//Messages
void DataBaseHelper::saveMessageFlow(WorkflowProcesses::Message* message)
{
	CM_CODEBLOCK(DataBaseHelper::saveMessageFlow)

	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageProcessInstances() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			db->saveMessageFlow(message);
			break;
		}
	}
}


//Events
WorkflowEvents::Event* DataBaseHelper::getEventDefinition(const String& sEventId)
{
	//TODO:getEventDefinition
	return NULL;
}

void DataBaseHelper::addOccurredEvent(WorkflowEvents::OccurredEvent* event)
{
	//TODO:addOccurredEvent
}

void DataBaseHelper::addWaitingActivity(WorkflowEvents::Event* event, WorkflowEvents::WaitingActivity* activity)
{
	//TODO:addWaitingActivity
}

WorkflowEvents::WaitingActivities* DataBaseHelper::getWaitingForActivities(const String& sEventId)
{
	//TODO:getWaitingForActivities
	return NULL;
}

WorkflowEvents::OccurredEvent* DataBaseHelper::getUnmanagedEvent(bool bManaging)
{
	//TODO:getUnmanagedEvent
	return NULL;
}

void DataBaseHelper::updateOccurredEvent(WorkflowEvents::OccurredEvent* event)
{
	//TODO:updateOccurredEvent
}

void DataBaseHelper::updateWaitingActivity(WorkflowEvents::WaitingActivity* activity)
{
	//TODO:updateWaitingActivity
}

//
bOS::SQL::SQLConnectionManager& DataBaseHelper::getManager()
{
	//TODO:
	DataBaseTemplate* db = vDataBases.at(0);
	
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageApplicationsDataBase() )
		{
			return db->getManager();
		}
	}
}

//Roles
bool DataBaseHelper::CheckGrant(DataManager::Panorama::Common::Grants& vGrants, const char* acUser, const char* acGrantType)
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageRoles() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			return db->CheckGrant(vGrants, acUser, acGrantType);
		}
	}

	return false;
}

String DataBaseHelper::getCheckListFolder()
{
	unsigned int uiSize = vDataBases.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseTemplate* db = vDataBases.at(i);

		if ( db->getXMLConnection().manageCheckList() &&  ( db->getXMLConnection().isPrimary() ) )
		{
			return db->getCheckListFolder();
		}
	}
}
