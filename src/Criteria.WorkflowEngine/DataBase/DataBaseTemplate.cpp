#include "DataBaseTemplate.h"
using namespace DataManager::DataBase;

#include "bOSCollectionEntry.h"

#include "bOSSQLSmartConnection.h"
#include "bOSResultSet.h"

#include "Grant.h"

using namespace bOS::SQL;

using namespace DataManager::Panorama::DataBase;
using namespace DataManager::Panorama::WorkflowParticipantsData;
using namespace DataManager::Panorama::WorkflowDataTypes;
using namespace DataManager::Panorama::WorkflowProcesses;
using namespace DataManager::Panorama::WorkflowServices;
using namespace DataManager::Panorama::Common;
using namespace DataManager::Panorama::WorkflowApplicationsData;
using namespace DataManager::Panorama::WorkflowRelevantData;

#include "DataBaseHelper.h"
#include "DBException.h"

DataBaseTemplate::DataBaseTemplate()
{
	iRetry = 1;
	iDelay = 1;
}

DataBaseTemplate::DataBaseTemplate(SQLConnectionManager::DataBaseType dbType)
{
	manager.init(dbType);

	iRetry = 1;
	iDelay = 1;
}

DataBaseTemplate::~DataBaseTemplate()
{
}

void DataBaseTemplate::open(SQLConnectionData* data, PoolManager pool)
{
	manager.createPool(data, pool.getMin(), pool.getMax() );

	iRetry = pool.getRetry();
	iDelay = pool.getDelay();
}

void DataBaseTemplate::close()
{
}

void DataBaseTemplate::setXMLConnection (DataManager::Panorama::DataBase::Connection* _connection)
{
	XMLNode* node = _connection->getXMLNode(0);
	xmlConnection.init ( node );
	delete node;
}



void DataBaseTemplate::getActivities(Activities& vActivities, String sStatus, String sOwner, bool bOnlyMine)
{
	CM_CODEBLOCK(DataBaseTemplate::getActivities)

	bool bCheckGrant=true;

	StringBuffer sWhere;
	
	if ( sStatus.length() > 0 )
	{
		sWhere.append (SQLActivity::STATUS_FIELD);
		sWhere.append ("='");
		sWhere.append (sStatus);
		sWhere.append ("'");
	}

	if ( sOwner.length() > 0 )
	{
		if ( sStatus.length() > 0 ) 
		{
			sWhere.append ( " AND (");
		}

		if ( bOnlyMine )
		{
			sWhere.append (SQLActivity::OWNER_FIELD );
			sWhere.append ("='");
			sWhere.append (sOwner);
			sWhere.append ("'");

			bCheckGrant=false;
		}
		else
		{
			sWhere.append (SQLActivity::OWNER_FIELD );
			sWhere.append ("='CRITERIA'");
		}

		if ( sStatus.length() > 0 ) 
		{
			sWhere.append ( ")");
		}
	}

	if ( bCheckGrant )
	{
		Activities activities;
		this->executeRecursiveSQLCommands (NULL, &activities, SQLCommand::SELECT, sWhere.getData(), false );

		unsigned int iSize = activities.size();
		for ( unsigned int i=0; i<iSize; i++)
		{
			Activity* activity = (Activity*)activities.at(i);
			Grants& grants = activity->getGrants();

			//verifica dei grants
			if ( DataBaseTemplate::CheckGrant (grants, sOwner.c_str(), DataManager::Panorama::Common::XMLGrant::VISIBLE_TYPE.c_str() ) )
			{
				vActivities.addActivity (*activity);
			}
		}
	}
	else
	{
		this->executeRecursiveSQLCommands (NULL, &vActivities, SQLCommand::SELECT, sWhere.getData(), false );
	}
}
int DataBaseTemplate::ExecuteSQLCommand(const char* acSQL)
{
	CM_CODEBLOCK(ExecuteSQLCommand)

	SQLSmartConnection smartConnection;
	SQLConnection* connection = NULL;
	connection = manager.get(iRetry, iDelay);
	smartConnection.init(&manager, connection);
	connection->setAutoCommit (true);
	int iRecord=0;
	try
	{
		iRecord=connection->execute(acSQL);
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("impossible to perform[" << acSQL << "]. Err[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	return iRecord;
}


void DataBaseTemplate::getAllActivities(Activities& vActivities, String sOwner, bool bNotMine)
{
	CM_CODEBLOCK(getAllActivities)

	StringBuffer sWhere;
	
	sWhere.append ("(");
	sWhere.append (SQLActivity::STATUS_FIELD);
	sWhere.append ("='MANUAL' AND ");
	sWhere.append (SQLActivity::OWNER_FIELD );
	sWhere.append ("='CRITERIA') OR (");
	sWhere.append (SQLActivity::STATUS_FIELD);
	sWhere.append ("!='COMPLETED' AND ");
	sWhere.append (SQLActivity::OWNER_FIELD );
	sWhere.append ("!='CRITERIA' AND ");
	sWhere.append (SQLActivity::OWNER_FIELD );
	sWhere.append ("!=''");

	if ( bNotMine )
	{
		sWhere.append (" AND ");
		sWhere.append (SQLActivity::OWNER_FIELD );
		sWhere.append ("!='");
		sWhere.append (sOwner);
		sWhere.append ("'");

	}

	sWhere.append (")");

	Activities activities;
	this->executeRecursiveSQLCommands (NULL, &activities, SQLCommand::SELECT, sWhere.getData(), false );

	unsigned int iSize = activities.size();
	for ( unsigned int i=0; i<iSize; i++)
	{
		Activity* activity = (Activity*)activities.at(i);
		Grants& grants = activity->getGrants();

		//verifica dei grants
		if ( DataBaseTemplate::CheckGrant (grants, sOwner.c_str(), DataManager::Panorama::Common::XMLGrant::VISIBLE_TYPE.c_str() ) )
		{
			vActivities.addActivity (*activity);
		}
	}
}

void DataBaseTemplate::getAllMyActivities(Activities& vActivities, String sOwner)
{
	CM_CODEBLOCK(getAllMyActivities)

	StringBuffer sWhere;
	
	sWhere.append ("(");
	sWhere.append (SQLActivity::STATUS_FIELD);
	sWhere.append ("='MANUAL' AND ");
	sWhere.append (SQLActivity::OWNER_FIELD );
	sWhere.append ("='CRITERIA') OR (");
	sWhere.append (SQLActivity::STATUS_FIELD);
	sWhere.append ("!='COMPLETED' AND ");
	sWhere.append (SQLActivity::OWNER_FIELD );
	sWhere.append ("='");
	sWhere.append (sOwner);
	sWhere.append ("')");

	Activities activities;
	this->executeRecursiveSQLCommands (NULL, &activities, SQLCommand::SELECT, sWhere.getData(), false );

	unsigned int iSize = activities.size();
	for ( unsigned int i=0; i<iSize; i++)
	{
		Activity* activity = (Activity*)activities.at(i);
		Grants& grants = activity->getGrants();

		//verifica dei grants
		if ( DataBaseTemplate::CheckGrant (grants, sOwner.c_str(), DataManager::Panorama::Common::XMLGrant::VISIBLE_TYPE.c_str() ) )
		{
			vActivities.addActivity (*activity);
		}
	}
}


void DataBaseTemplate::getNotifies(Activities& vActivities, String sOwner)
{
	CM_CODEBLOCK(DataBaseTemplate::getNotifies)

	bool bCheckGrant=true;

	StringBuffer sSQL;
	sSQL.append("SELECT a.* FROM ");
	sSQL.append(SQLActivities::TABLE_NAME);
	sSQL.append(" a, ");
	sSQL.append(SQLAttribute::TABLE_NAME);
	sSQL.append(" b where a.process_id=b.process_id");
	sSQL.append(" and a.activity_id=b.activity_id and a.owner='");
	sSQL.append(sOwner);
	sSQL.append ("' and a.status='RUNNING' and b.Name='");
	sSQL.append (XMLActivity::MARKER_FEATURE);
	sSQL.append ("' and b.Value='");
	sSQL.append (XMLActivity::MARKER_NOTIFY_FEATURE);
	sSQL.append ("'");

	this->executeSQL (NULL, &vActivities, SQLCommand::SELECT, sSQL.getData(), false );
}

void DataBaseTemplate::getActivityRunningNotifies(WorkflowProcesses::Activities& vActivities, String sOwner)
{
	CM_CODEBLOCK(DataBaseTemplate::getActivityRunningNotifies)

	bool bCheckGrant=true;

	StringBuffer sSQL;
	sSQL.append("SELECT a.* FROM ");
	sSQL.append(SQLActivities::TABLE_NAME);
	sSQL.append(" a where a.owner='");
	sSQL.append(sOwner);
	sSQL.append("' and a.status='RUNNING' and a.activity_id not in (");
	sSQL.append("select b.activity_id from ");
	sSQL.append(SQLAttribute::TABLE_NAME);
	sSQL.append(" b where b.process_id = a.process_id");
	sSQL.append(" and a.activity_id=b.activity_id and b.Name='");
	sSQL.append(XMLActivity::MARKER_FEATURE);
	sSQL.append("' and b.Value='");
	sSQL.append(XMLActivity::MARKER_NOTIFY_FEATURE);
	sSQL.append("')");

	this->executeSQL (NULL, &vActivities, SQLCommand::SELECT, sSQL.getData(), false );
}


void DataBaseTemplate::insertProcess(String& lProcessId, WorkflowProcess& process,bool b2Prepared )
{
	CM_CODEBLOCK(DataBaseTemplate::insertProcess)

	SQLConnection* connection = NULL;
	try
	{
		CM_TRACE_CODEPATH("Retrieving Connection with Retry[" << iRetry << "] Delay[" << iDelay << "]") 
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection);

	if ( b2Prepared )
	{
		StringBuffer sSQL;
		sSQL.append("select ");
		sSQL.append(SQLProcessComponent::PROCESS_ID_FIELD);
		sSQL.append(" from ");
		sSQL.append(SQLWorkflowProcess::TABLE_NAME);
		sSQL.append(" where ");
		sSQL.append(SQLWorkflowProcess::STATUS_FIELD);
		sSQL.append("='PRECREATED' and ");
		sSQL.append(SQLWorkflowProcess::NAME_FIELD);
		sSQL.append("='");
		sSQL.append(process.getName());
		sSQL.append("'");

		long lRecordUpdated=0;

		try
		{
			bOS::SQL::ResultSet* rs = connection->executeQuery (sSQL.getData());
			long lRecordManaged = rs->getRecordCount();
			

			while ( lRecordManaged > 0 && (lRecordUpdated==0))
			{
				rs->moveNext ();
				bOS::SQL::ResultSetRecord* record = rs->getRecord();
				bOS::SQL::ResultSetField* field = record->at(0);
				lProcessId = field->sValue.getData();

				sSQL.clear();
				sSQL.append ("update ");
				sSQL.append(SQLWorkflowProcess::TABLE_NAME);
				sSQL.append (" set ");
				sSQL.append(SQLWorkflowProcess::STATUS_FIELD);
				sSQL.append ("='");
				sSQL.append (XMLWorkflowProcess::CREATED_STATUS);
				sSQL.append ("'  where ");
				sSQL.append(SQLProcessComponent::PROCESS_ID_FIELD);
				sSQL.append("=");
				sSQL.append(lProcessId);
				sSQL.append(" and ");
				sSQL.append(SQLWorkflowProcess::STATUS_FIELD);
				sSQL.append("='PRECREATED'");

				lRecordUpdated = connection->execute (sSQL.getData());
			}

			rs->close();
		}
		catch ( bOS::SQL::SQLException& sqlErr)
		{
			CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		} 

		if ( lRecordUpdated > 0 )
		{
			return;
		}
	}

	try
	{
		CM_TRACE_CODEPATH("insert process");
		this->executeSQLCommands (connection, &process, SQLCommand::ADD, NULL, true);
		CM_TRACE_CODEPATH("insert attributes");
		this->executeSQLCommands (connection, &process.getAttributes(), SQLCommand::ADD, NULL, false);

		WorkflowProcesses::Activities& vActivities = process.getActivities();
		unsigned int uiSize = vActivities.size();
		for ( unsigned int i=0; i<uiSize; i++)
		{
			WorkflowProcesses::Activity* activity = (WorkflowProcesses::Activity*)vActivities.at(i);
			CM_TRACE_CODEPATH("insert activity");
			this->executeSQLCommands (connection, activity, SQLCommand::ADD, NULL, false);
			CM_TRACE_CODEPATH("insert activity attributes");
			this->executeSQLCommands (connection, &(activity->getAttributes()), SQLCommand::ADD, NULL, false);
		}
	}
	catch ( ... )
	{
		if ( strcmp(process.getProcessId(),"") )
		{
			process.setError();
			this->executeSQLCommands (connection, &process, SQLCommand::MODIFY, NULL, true);
		}
		throw;
	}
	
	lProcessId = process.getProcessId();	
}


void DataBaseTemplate::executeRecursiveSQLCommands(SQLConnection* connection, SQLTable* sqlTable, SQLCommand::SQLOperation operation, const char* acWhere, bool bMainTable)
{
	CM_CODEBLOCK(DataBaseTemplate::executeRecursiveSQLCommands)
	
	SQLSmartConnection smartConnection;

	if ( connection == NULL ) 
	{
		try
		{
			connection = manager.get(iRetry, iDelay);
		}	
		catch ( SQLException& sqlErr)
		{
			CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
			throw DBException(sqlErr.getMessage());
		}

		smartConnection.init(&manager, connection);
	
		connection->setAutoCommit (false);
	}

	try
	{
		if ( connection->supportTransaction() && smartConnection.isConnectionOwner() )
			connection->beginTrans();

		this->executeSQLCommands (connection, sqlTable, operation, acWhere, bMainTable);

		SQLTablesList vTables = sqlTable->getSQLTables();
		unsigned int iSize = vTables.size();
		
		for ( unsigned int i=0;i<iSize;i++)
		{
			this->executeRecursiveSQLCommands(connection, vTables.at(i), operation , NULL, false);
		}

		if ( connection->supportTransaction() && smartConnection.isConnectionOwner() )
		{
			connection->commit();
		}
	}
	catch ( DBException&)
	{
		if ( connection->supportTransaction() && smartConnection.isConnectionOwner() )
		{
			connection->rollback();
		}

		throw;
	}
}


int DataBaseTemplate::executeSQLCommands(SQLConnection* connection, SQLTable* table, SQLCommand::SQLOperation iOperation, const char* acWhere, bool bMainTable)
{
	CM_CODEBLOCK(DataBaseTemplate::executeSQLCommands)

	SQLCommands vCommands;
	bool bReturnRecordSet=false;
	int iRecord=0;

	switch ( iOperation ) 
	{
	case SQLCommand::ADD:
		table->getInsertSQLCommand(vCommands);
		break;
	case SQLCommand::MODIFY:
		table->getUpdateSQLCommand(vCommands);
		break;
	case SQLCommand::ERASE:
		table->getDeleteSQLCommand(vCommands);
		break;
	case SQLCommand::SELECT:
		table->getSelectSQLCommand(vCommands);
		bReturnRecordSet = true;
		break;
	case SQLCommand::CREATE:
		table->getCreateSQLCommand(vCommands);
		break;
	case SQLCommand::DROP:
		table->getDropSQLCommand(vCommands);
		break;
	}
		
	String sSQL;
	try
	{
		int iSize = vCommands.size();
		
		for ( int i=0;i<iSize;i++)
		{
			SQLCommand* command = vCommands.at(i);

			if ( acWhere != NULL ) 
			{
				command->addWhere ( acWhere );
			}
			sSQL = command->getSQLStringCommand();
			CM_TRACE_DEBUG( sSQL);


			long lRecordManaged=0;
			if ( bReturnRecordSet ) 
			{
				ResultSet* rs = connection->executeQuery (sSQL.c_str());
				lRecordManaged = rs->getRecordCount(); 

				CM_TRACE_DEBUG("Retrivied Record Nr[" << lRecordManaged <<"]")

				if ( lRecordManaged == 0 )
				{			
					rs->close();

					if ( bMainTable )
						throw DBException(DB_RECORD_NOT_FOUND);
				}
				else
				{
					int iNrRecordParsed = 0;
					while ( rs->moveNext () )
					{
						
						if ( !(table->parse ( rs->getRecord() ) ))
						{
							CM_TRACE_ERROR("Impossible to parse Record")
							throw DBException(DB_RECORD_NOT_FOUND);
						}
						iNrRecordParsed++;
					}
					CM_TRACE_CODEPATH("record number parsed [" << iNrRecordParsed << "]")
					rs->close();
				}
			}
			else
			{
				lRecordManaged=connection->execute(sSQL.c_str());

				if ( lRecordManaged == 0 )
				{
					switch ( iOperation) 
					{
						case SQLCommand::ADD:
							if ( bMainTable )
								throw DBException(DB_RECORD_ALREADY_PRESENT);
						case SQLCommand::MODIFY:
						case SQLCommand::ERASE:
							if ( bMainTable )
								throw DBException(DB_RECORD_NOT_FOUND);
					}
				}

				if ( ( iOperation == SQLCommand::ADD)  && ( table->haveAutoIncrementField() ) )
				{
					long lAutoIncrement = connection->getAutoIncrement();
					if ( lAutoIncrement != 0 )
					{
						table->setAutoIncrementField ( lAutoIncrement);
					}
				}
			}
			iRecord += lRecordManaged;
		}
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("impossible to perform[" << sSQL << "]. Err[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	return iRecord;
}

int DataBaseTemplate::executePrepareSQLCommands(SQLConnection* connection, SQLTable* table, SQLCommand::SQLOperation iOperation, const char* acWhere, bool bMainTable)
{
	CM_CODEBLOCK(DataBaseTemplate::executePrepareSQLCommands)

	SQLCommands vCommands;
	bool bReturnRecordSet=false;
	int iRecord=0;

	switch ( iOperation ) 
	{
	case SQLCommand::ADD:
		table->getInsertSQLCommand(vCommands);
		break;
	case SQLCommand::MODIFY:
		table->getUpdateSQLCommand(vCommands);
		break;
	case SQLCommand::ERASE:
		table->getDeleteSQLCommand(vCommands);
		break;
	case SQLCommand::SELECT:
		table->getSelectSQLCommand(vCommands);
		bReturnRecordSet = true;
		break;
	case SQLCommand::CREATE:
		table->getCreateSQLCommand(vCommands);
		break;
	case SQLCommand::DROP:
		table->getDropSQLCommand(vCommands);
		break;
	}
	
	long lRecordManaged=0;
	try
	{
		int iSize = vCommands.size();
		String sSQL;
		for ( int i=0;i<iSize;i++)
		{
			SQLCommand* command = vCommands.at(i);

			if ( acWhere != NULL ) 
			{
				command->addWhere ( acWhere );
			}

			CM_TRACE_DEBUG(command->getSQLStringCommand())
		}

		lRecordManaged=connection->executePrepare(vCommands);

		/*if ( bReturnRecordSet ) 
		{

			ResultSet* rs = connection->executeQuery (sSQL.c_str());
			lRecordManaged = rs->getRecordCount(); 

			CM_TRACE_DEBUG("Retrivied Record Nr[" << lRecordManaged <<"]")

			if ( lRecordManaged == 0 )
			{			
				rs->close();

				if ( bMainTable )
					throw DBException(DB_RECORD_NOT_FOUND);
			}
			else
			{
				while ( rs->moveNext () )
				{
					if ( !(table->parse ( rs->getRecord() ) ))
					{
						CM_TRACE_ERROR("Impossible to parse Record")
						throw DBException(DB_RECORD_NOT_FOUND);
					}
				}
				rs->close();
			}
		}
		else
		{*/
			if ( lRecordManaged == 0 )
			{
				switch ( iOperation) 
				{
					case SQLCommand::ADD:
						if ( bMainTable )
							throw DBException(DB_RECORD_ALREADY_PRESENT);
					case SQLCommand::MODIFY:
					case SQLCommand::ERASE:
						if ( bMainTable )
							throw DBException(DB_RECORD_NOT_FOUND);
				}
			}

			if ( ( iOperation == SQLCommand::ADD)  && ( table->haveAutoIncrementField() ) )
			{
				long lAutoIncrement = connection->getAutoIncrement();
				if ( lAutoIncrement != 0 )
				{
					table->setAutoIncrementField ( lAutoIncrement);
				}
			}
		//}
	}
	catch ( SQLException& sqlErr)
	{
		//CM_TRACE_ERROR("impossible to perform[" << sSql << "]. Err[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	return lRecordManaged;
}


int DataBaseTemplate::executeSQL(SQLConnection* connection, SQLTable* table, SQLCommand::SQLOperation iOperation, const char* acSQL, bool bMainTable)
{
	CM_CODEBLOCK(executeSQL)

	SQLSmartConnection smartConnection;

	if ( connection == NULL ) 
	{
		try
		{
			connection = manager.get(iRetry, iDelay);
		}	
		catch ( SQLException& sqlErr)
		{
			CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
			throw DBException(sqlErr.getMessage());
		}

		smartConnection.init(&manager, connection);

		connection->setAutoCommit (false);
	}

	SQLCommands vCommands;
	bool bReturnRecordSet=false;
	int iRecord=0;

	switch ( iOperation ) 
	{
	case SQLCommand::ADD:
	case SQLCommand::MODIFY:
	case SQLCommand::ERASE:
	case SQLCommand::CREATE:
	case SQLCommand::DROP:
		break;
	case SQLCommand::SELECT:
		bReturnRecordSet = true;
		break;
	}
		
	try
	{
		long lRecordManaged=0;
		if ( bReturnRecordSet ) 
		{
			CM_TRACE_DEBUG(acSQL)
			ResultSet* rs = connection->executeQuery (acSQL);
			lRecordManaged = rs->getRecordCount(); 

			CM_TRACE_DEBUG("Retrivied Record Nr[" << lRecordManaged <<"]")

			if ( lRecordManaged == 0 )
			{			
				rs->close();

				if ( bMainTable )
					throw DBException(DB_RECORD_NOT_FOUND);
			}
			else
			{
				while ( rs->moveNext () )
				{
					if ( !(table->parse ( rs->getRecord() ) ))
					{
						CM_TRACE_ERROR("Impossible to parse Record")
						throw DBException(DB_RECORD_NOT_FOUND);
					}
				}
				rs->close();
			}
		}
		else
		{
			lRecordManaged=connection->execute(acSQL);

			if ( lRecordManaged == 0 )
			{
				switch ( iOperation) 
				{
					case SQLCommand::ADD:
						if ( bMainTable )
							throw DBException(DB_RECORD_ALREADY_PRESENT);
					case SQLCommand::MODIFY:
					case SQLCommand::ERASE:
						if ( bMainTable )
							throw DBException(DB_RECORD_NOT_FOUND);
				}
			}

			if ( ( iOperation == SQLCommand::ADD)  && ( table->haveAutoIncrementField() ) )
			{
				long lAutoIncrement = connection->getAutoIncrement();
				if ( lAutoIncrement != 0 )
				{
					table->setAutoIncrementField ( lAutoIncrement);
				}
			}
		}
		iRecord += lRecordManaged;
	}
	catch ( SQLException& sqlErr)
	{
		//CM_TRACE_ERROR("impossible to perform[" << sSql << "]. Err[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	return iRecord;
}



//Users
void DataBaseTemplate::getUser(User& user)
{
	CM_CODEBLOCK(getUser)

	executeRecursiveSQLCommands(NULL, &user, SQLCommand::SELECT, NULL, true);
}

void DataBaseTemplate::getUsers(DataManager::Panorama::WorkflowParticipantsData::Users& vUsers)
{
	CM_CODEBLOCK(getUsers)

	StringBuffer sSQL;
	sSQL.append("SELECT * FROM ");
	sSQL.append(SQLUser::TABLE_NAME);

	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection); 

	ResultSet* rsUsers = connection->executeQuery(sSQL.getData());
	
	while ( rsUsers->moveNext() )
	{
		User* user = new User();
		user->parse(rsUsers->getRecord() );

		vUsers.add ((bOS::Collections::CollectionEntry*)user);
	}

	rsUsers->close();
}

void DataBaseTemplate::addUser(const char* acUser)
{
	CM_CODEBLOCK(getUser)

	User user;
	user.init(acUser);

	this->executeRecursiveSQLCommands ( NULL, &user, SQLCommand::ADD, NULL, true);
}

void DataBaseTemplate::updateUser(const char* acUser)
{
	CM_CODEBLOCK(updateUser)

	User user;
	user.init(acUser);

	this->executeRecursiveSQLCommands ( NULL, &user, SQLCommand::MODIFY, NULL, true);
}

void DataBaseTemplate::deleteUser(const char* acUserKey)
{
	CM_CODEBLOCK(deleteUser)

	User user;
	user.setKey(acUserKey);

	this->executeRecursiveSQLCommands ( NULL, &user, SQLCommand::ERASE, NULL, true);
}

//Roles
void DataBaseTemplate::getRole(DataManager::Panorama::WorkflowParticipantsData::Role& role)
{
	CM_CODEBLOCK(getRole)

	this->executeRecursiveSQLCommands(NULL, &role, SQLCommand::SELECT, NULL, true);
}

void DataBaseTemplate::getRoles(DataManager::Panorama::WorkflowParticipantsData::Roles& vRoles)
{
	CM_CODEBLOCK(getRoles)

	StringBuffer sSQL;
	sSQL.append("SELECT * FROM ");
	sSQL.append(SQLRole::TABLE_NAME);

	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection); 

	ResultSet* rsRoles = connection->executeQuery(sSQL.getData());
	
	while ( rsRoles->moveNext() )
	{
		Role* role = new Role();
		role->parse(rsRoles->getRecord() );

		vRoles.add ((bOS::Collections::CollectionEntry*)role);
	}

	rsRoles->close();
}

void DataBaseTemplate::addRole(const char* acRole)
{
	Role role;
	role.init(acRole);

	this->executeRecursiveSQLCommands(NULL, &role, SQLCommand::ADD, NULL, true);
}

void DataBaseTemplate::updateRole(const char* acRole)
{
	Role role;
	role.init(acRole);

	this->executeRecursiveSQLCommands(NULL, &role, SQLCommand::MODIFY, NULL, true);
}

void DataBaseTemplate::deleteRole(const char* acRoleKey)
{
	Role role;
	role.setKey(acRoleKey);

	this->executeRecursiveSQLCommands(NULL, &role, SQLCommand::ERASE, NULL, true);
}

void DataBaseTemplate::addUserToRole(const char* acUser, const char* acRoleKey)
{
	Role role;
	role.setKey ( acRoleKey);

	try
	{
		this->getRole(role);
	}
	catch (DBException&)
	{
		throw;
	}

	Users& vUsers = role.getUsers();
	if ( vUsers.addUser(acUser) )
	{
		this->executeRecursiveSQLCommands(NULL, &role, SQLCommand::MODIFY, NULL, true);
	}
	else
	{
		throw DBException(DB_RECORD_ALREADY_PRESENT);
	}
}

void DataBaseTemplate::deleteUserFromRole(const char* acUserKey, const char* acRoleKey)
{
	Role role;
	role.setKey ( acRoleKey);

	try
	{
		this->getRole(role);
	}
	catch (DBException&)
	{
		throw;
	}

	Users& vUsers = role.getUsers();
	if ( vUsers.deleteUser(acUserKey) )
	{
		this->executeRecursiveSQLCommands(NULL, &role, SQLCommand::MODIFY, NULL, true);
	}
	else
	{
		throw DBException(DB_RECORD_NOT_FOUND);
	}

}

void DataBaseTemplate::getRolesByUser(const char* acUserKey, DataManager::Panorama::WorkflowParticipantsData::Roles& roles)
{
	Roles vRoles;
	this->getRoles (vRoles);

	if ( !(vRoles.getRolesByUser(acUserKey, &roles)) )
	{
		throw DBException(DB_RECORD_NOT_FOUND);
	}
}

//DataTypes
void DataBaseTemplate::getDataTypes(DataManager::Panorama::WorkflowDataTypes::DataTypes& vDataTypes)
{
	CM_CODEBLOCK(getDataTypes)

	//TODO: SQLTable interface to implement for DataTypes.
	StringBuffer sSQL;
	sSQL.append("SELECT * FROM ");
	sSQL.append(SQLDataTypes::TABLE_NAME);

	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection); 

	ResultSet* rsDataType = connection->executeQuery(sSQL.getData());
	
	while ( rsDataType->moveNext() )
	{
		DataType* datatype = new DataType();
		datatype->parse(rsDataType->getRecord() );

		vDataTypes.add ((bOS::Collections::CollectionEntry*)datatype);
	}

	rsDataType->close();
}

void DataBaseTemplate::getDataType(DataManager::Panorama::WorkflowDataTypes::DataType& datatype)
{
	CM_CODEBLOCK(getDataType)

	this->executeRecursiveSQLCommands(NULL, &datatype, SQLCommand::SELECT, NULL, true);
}

//Services
void DataBaseTemplate::getServices(DataManager::Panorama::WorkflowServices::Services& vServices)
{
	CM_CODEBLOCK(getServices)

	StringBuffer sSQL;
	sSQL.append("SELECT * FROM ");
	sSQL.append(SQLServices::TABLE_NAME);

	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection); 

	ResultSet* rsServices = connection->executeQuery(sSQL.getData());
	
	while ( rsServices->moveNext() )
	{
		Service* service = new Service();
		service->parse(rsServices->getRecord() );

		vServices.add ((bOS::Collections::CollectionEntry*)service);
	}

	rsServices->close();
}

//Services
void DataBaseTemplate::getServicesForUser(const char* acUser, DataManager::Panorama::WorkflowServices::Services& vServices)
{
	CM_CODEBLOCK(getServices)
	assert(acUser != NULL );

	Roles userRoles;
	this->getRolesByUser(acUser, userRoles);

	StringBuffer sSQL;
	sSQL.append("SELECT * FROM ");
	sSQL.append(SQLServices::TABLE_NAME);

	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection); 

	ResultSet* rsServices = connection->executeQuery(sSQL.getData());
	
	while ( rsServices->moveNext() )
	{
		Service* service = new Service();
		service->parse(rsServices->getRecord() );

		Users& users = service->getUsers();
		Roles& roles = service->getRoles();

		if ( ((users.size() == 0 ) && ( roles.size()==0) ) || users.checkUser(acUser) || roles.checkRoles(&userRoles) )
		{
			vServices.add ((bOS::Collections::CollectionEntry*)service);
		}
		else
			delete service;
	}

	rsServices->close();
}

void DataBaseTemplate::insertReport(WorkflowProcesses::Report& report)
{
	CM_CODEBLOCK(DataBaseTemplate::insertReport)
	this->executeRecursiveSQLCommands(NULL, &report, SQLCommand::ADD, NULL, true);
}

void DataBaseTemplate::getReports (WorkflowProcesses::Reports& vReports)
{
	CM_CODEBLOCK(DataBaseTemplate::getReports)

	StringBuffer sWhere;
	sWhere.append (SQLProcessComponent::PROCESS_ID_FIELD);
	sWhere.append ("='");
	sWhere.append (vReports.getProcessId());
	sWhere.append ("'");

	this->executeRecursiveSQLCommands (NULL, &vReports, SQLCommand::SELECT, sWhere.getData(), false );
}

void DataBaseTemplate::addService(const char* acService)
{
	Service service(acService);

	this->executeRecursiveSQLCommands(NULL, &service, SQLCommand::ADD, NULL, true);
}

void DataBaseTemplate::deleteService(const char* acServiceName)
{
	Service service;
	service.setName(acServiceName);

	this->executeRecursiveSQLCommands(NULL, &service, SQLCommand::ERASE, NULL, true);
}

void DataBaseTemplate::getProcesses(WorkflowProcesses::Processes& vProcesses)
{
	CM_CODEBLOCK(DataBaseTemplate::getProcesses)

	StringBuffer sSQL;
	sSQL.append("SELECT * FROM ");
	sSQL.append(SQLWorkflowProcess::TABLE_NAME);

	SQLSmartConnection smartConnection;
	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	smartConnection.init(&manager, connection);

	connection->setAutoCommit (false);

	SQLCommands vCommands;

	try
	{
		CM_TRACE_DEBUG(sSQL.getData())
		ResultSet* rs = connection->executeQuery (sSQL.getData());
		long lRecordManaged = rs->getRecordCount(); 

		CM_TRACE_DEBUG("Retrivied Record Nr[" << lRecordManaged <<"]")

		if ( lRecordManaged == 0 )
		{			
			rs->close();
		}
		else
		{
			while ( rs->moveNext () )
			{
				WorkflowProcess* process = new WorkflowProcess();

				if ( !(process->parse ( rs->getRecord() ) ))
				{
					CM_TRACE_ERROR("Impossible to parse Record")
					throw DBException(DB_RECORD_NOT_FOUND);
				}

				vProcesses.push_back( process );
			}
			rs->close();
		}
	}
	catch ( SQLException& sqlErr)
	{
		//CM_TRACE_ERROR("impossible to perform[" << sSql << "]. Err[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}
}

bOS::CoreString::String DataBaseTemplate::getProcessStatus(const char* processId)
{
	CM_CODEBLOCK(DataBaseTemplate::getProcessStatus)

	StringBuffer sSQL;
	sSQL.append("select status from ");
	sSQL.append(SQLWorkflowProcess::TABLE_NAME);
	sSQL.append(" where process_id='");
	sSQL.append(processId);
	sSQL.append("'");

	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection); 

	ResultSet* rsUsers = connection->executeQuery(sSQL.getData());
	
	bOS::CoreString::String sStatus;
	while ( rsUsers->moveNext() )
	{
		sStatus = rsUsers->getRecord()->at (0)->sValue.getData(); 
		break;
	}

	rsUsers->close();

	return sStatus;
}

void DataBaseTemplate::getProcessHeader(WorkflowProcess& process)
{
	CM_CODEBLOCK(DataBaseTemplate::getProcessHeader)

	SQLConnection* connection = NULL;
	try
	{
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection);

	this->executeSQLCommands (connection, &process, SQLCommand::SELECT, NULL, true);
}

void DataBaseTemplate::getNewProcessHeader(WorkflowProcess& process)
{
	CM_CODEBLOCK(DataBaseTemplate::getNewProcessHeader)

	StringBuffer sSQL;
	sSQL.append("select Name, Status, Description, ParentProcess, ActivityParentProcess, Exit2Manage from ");
	sSQL.append(SQLWorkflowProcess::TABLE_NAME);
	sSQL.append(" where process_id='");
	sSQL.append(process.getProcessId());
	sSQL.append("'");

	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection); 

	ResultSet* rsUsers = connection->executeQuery(sSQL.getData());
	
	while ( rsUsers->moveNext() )
	{
		process.parse (rsUsers->getRecord () );
		break;
	}

	rsUsers->close();

}

void DataBaseTemplate::getProcessInstance(WorkflowProcess& process)
{
	CM_CODEBLOCK(DataBaseTemplate::getProcessInstance)

	//this->executeRecursiveSQLCommands(NULL, &process, SQLCommand::SELECT, NULL, true);
	SQLConnection* connection = NULL;
	try
	{
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection);

	this->executeSQLCommands (connection, &process, SQLCommand::SELECT, NULL, true);
	this->executeSQLCommands (connection, &(process.getAttributes()), SQLCommand::SELECT, NULL, false);

	WorkflowProcesses::Activities& vActivities = process.getActivities();
	this->executeSQLCommands (connection, &vActivities, SQLCommand::SELECT, NULL, false);
	unsigned int uiSize = vActivities.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		WorkflowProcesses::Activity* activity = (WorkflowProcesses::Activity*)vActivities.at(i);
		activity->setProcessId ( process.getProcessId() );
		this->executeSQLCommands (connection, &(activity->getAttributes()), SQLCommand::SELECT, NULL, false);
	}
}


void DataBaseTemplate::updateProcess(DataManager::Panorama::WorkflowProcesses::WorkflowProcess* process)
{
	CM_CODEBLOCK(DataBaseTemplate::updateProcess)

	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}


	SQLSmartConnection smartConnection(&manager, connection);

	this->executeSQLCommands (connection, process, SQLCommand::MODIFY, NULL, true);
}

void DataBaseTemplate::updateAttributes(WorkflowRelevantData::Attributes& vAttributes)
{
	CM_CODEBLOCK(DataBaseTemplate::updateAttributes)

	SQLConnection* connection = NULL;
	try
	{
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection);

	/*
	this->executeSQLCommands (connection, &vAttributes, SQLCommand::ERASE, NULL, false);
	this->executeSQLCommands (connection, &vAttributes, SQLCommand::ADD, NULL, true);
	*/

	WorkflowRelevantData::Attributes vAttributes2Search;
	vAttributes2Search.setProcessId ( vAttributes.getProcessId());
	vAttributes2Search.setActivityId (vAttributes.getActivityId().c_str());

	WorkflowRelevantData::Attributes vAttributes2Add;
	

	WorkflowRelevantData::Attributes vAttributes2Update;
	

	this->executeRecursiveSQLCommands(connection, &vAttributes2Search,SQLCommand::SELECT, NULL,false);

	for ( unsigned int i=0; i<vAttributes.size(); i++)
	{
		Attribute* attribute = (Attribute*)vAttributes[i];

		Attribute* attr2Search = (Attribute*)vAttributes2Search.get(attribute->getName().c_str());

		if ( attr2Search == NULL )
		{
			vAttributes2Add.add(*attribute);
		}
		else if ( strcmp(attribute->getValue().c_str(), attr2Search->getValue().c_str()) )
		{
			vAttributes2Update.add(*attribute);
		}
	}

	vAttributes2Add.setProcessId ( vAttributes.getProcessId());
	vAttributes2Add.setActivityId (vAttributes.getActivityId().c_str());
	vAttributes2Update.setProcessId ( vAttributes.getProcessId());
	vAttributes2Update.setActivityId (vAttributes.getActivityId().c_str());
	this->executeSQLCommands (connection, &vAttributes2Update, SQLCommand::MODIFY, NULL, false);
	this->executeSQLCommands(connection, &vAttributes2Add, SQLCommand::ADD, NULL, true);
	
	//this->executePrepareSQLCommands(connection, &vAttributes2Add, SQLCommand::ADD, NULL, true);

}

/*
void DataBaseTemplate::updateAttributes(DataManager::Panorama::WorkflowProcesses::Activity& activity)
{
	CM_CODEBLOCK(updateAttributes)

	SQLConnection* connection = NULL;
	try
	{
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection);

	StringBuffer sSQL;
	sSQL.append ("delete from ");
	sSQL.append (SQLActivities::TABLE_NAME);
	sSQL.append (" where ");
	sSQL.append (actiity.acGetWhere());
	this->executeSQL(connection, null, SQLCommand::ERASE, acSQL, false);

	DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes = activity.getAttributes();
	vAttributes
	this->executeSQLCommands (connection, &vAttributes, SQLCommand::ADD, NULL, true);

}
*/

void DataBaseTemplate::updateActivityCheckStatus(DataManager::Panorama::WorkflowProcesses::Activity* activity, string sStatus2Check)
{
	CM_CODEBLOCK(updateActivityCheckStatus)

	SQLConnection* connection = NULL;
	try
	{
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection);

	StringBuffer sWhere;
	sWhere.append (SQLActivity::STATUS_FIELD);
	sWhere.append ("='");
	sWhere.append (sStatus2Check);
	sWhere.append("'");

	this->executeSQLCommands (connection, activity, SQLCommand::MODIFY, sWhere.getData(), true);
}

void DataBaseTemplate::updateActivityNoOwner(DataManager::Panorama::WorkflowProcesses::Activity* activity)
{
	CM_CODEBLOCK(updateActivityCheckStatus)

	SQLConnection* connection = NULL;
	try
	{
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection);

	StringBuffer sWhere;
	sWhere.append ("(");
	sWhere.append (SQLActivity::OWNER_FIELD);
	sWhere.append ("='CRITERIA' OR ");
	sWhere.append (SQLActivity::OWNER_FIELD);
	sWhere.append("='')");

	this->executeSQLCommands (connection, activity, SQLCommand::MODIFY, sWhere.getData(), true);
}

void DataBaseTemplate::updateActivity(DataManager::Panorama::WorkflowProcesses::Activity* activity, bool bRecursive)
{
	CM_CODEBLOCK(updateActivity)

	SQLConnection* connection = NULL;
	try
	{
		connection = manager.get(iRetry, iDelay);
	}	
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}


	SQLSmartConnection smartConnection(&manager, connection);

	if ( bRecursive )
	{
		this->executeRecursiveSQLCommands (connection, activity, SQLCommand::MODIFY, NULL, true);
	}
	else
	{
		this->executeSQLCommands (connection, activity, SQLCommand::MODIFY, NULL, true);
	}
}

void DataBaseTemplate::getAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes)
{
	CM_CODEBLOCK(getAttributes)

	this->executeRecursiveSQLCommands (NULL, &vAttributes, SQLCommand::SELECT, NULL, true);
}

void DataBaseTemplate::getProcessAttribute(const char* processId, WorkflowRelevantData::Attribute& attribute)
{
	CM_CODEBLOCK(DataBaseTemplate::getProcessAttribute)

	StringBuffer sSQL;
	sSQL.append("select * from ");
	sSQL.append(SQLAttribute::TABLE_NAME);
	sSQL.append(" where process_id='");
	sSQL.append(processId);
	sSQL.append("' and activity_id='' and name='");
	sSQL.append(attribute.getName());
	sSQL.append("'");

	SQLConnection* connection = NULL;

	try
	{
		connection = manager.get(iRetry, iDelay);
	}
	catch ( SQLException& sqlErr)
	{
		CM_TRACE_ERROR("Connection Error[" << sqlErr.getMessage() << "]")
		throw DBException(sqlErr.getMessage());
	}

	SQLSmartConnection smartConnection(&manager, connection); 

	ResultSet* rsUsers = connection->executeQuery(sSQL.getData());
	
	while ( rsUsers->moveNext() )
	{
		attribute.parse ( rsUsers->getRecord());
	}

	rsUsers->close();
}


void DataBaseTemplate::getActivity(DataManager::Panorama::WorkflowProcesses::Activity& activity)
{
	CM_CODEBLOCK(DataBaseTemplate::getActivity)

	this->executeRecursiveSQLCommands (NULL, &activity, SQLCommand::SELECT, NULL, true);
}

bool DataBaseTemplate::CheckGrant(DataManager::Panorama::Common::Grants& vGrants, const char* acUser, const char* acGrantType)
{
	CM_CODEBLOCK(DataBaseTemplate::CheckGrant)

	Grant* grant=NULL;

	bool bRetYes = true;
	bool bRetNo = false;

	unsigned int uiSize = vGrants.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		grant = (Grant*)(vGrants.at(i));

		if ( !strcmp(grant->getType().c_str(),acGrantType) ) 
		{
			Users& users = grant->getUsers();
			Roles& roles = grant->getRoles();

			if ( grant->isEnabled() ) 
			{
				if ( users.checkUser(acUser) )
				{
					return true;
				}
				else
				{
					unsigned int uiRoleSize = roles.size();
					Role* role = NULL;
					bool bNotInRole = true;
					for ( unsigned int uiRole=0; uiRole<uiRoleSize; uiRole++)
					{
						role = (Role*) roles.at(uiRole);

						try
						{
							DataBaseHelper::instance()->getRole(*role);
							if ( role->getUsers().checkUser(acUser) )
							{
								bRetYes=true;
								bNotInRole=false;
							}
						}
						catch (DBException dbErr) 
						{
							CM_TRACE_ERROR("Impossible to retrieve Role[" << role->getKey() << "].Err[" << dbErr.getMessage() << "]")
						}

						
					}

					if ( bNotInRole )
						return false;
				}
			}
			else
			{
				if ( users.checkUser(acUser) )
				{
					return false;
				}
				else 
				{
					unsigned int uiRoleSize = roles.size();
					Role* role = NULL;
					for ( unsigned int uiRole=0; uiRole<uiRoleSize; uiRole++)
					{
						role = (Role*) roles.at(uiRole);

						DataBaseHelper::instance()->getRole(*role);

						if ( role->getUsers().checkUser(acUser) )
						{
							bRetNo = true;
						}
					}
				}
			}
		}
	}

	return bRetYes && !bRetNo;
}

void DataBaseTemplate::saveMessageFlow(WorkflowProcesses::Message* message)
{
	this->executeRecursiveSQLCommands(NULL, message, SQLCommand::ADD, NULL, true);
}

//TODO: Da sviluppare
bOS::IO::FilesList DataBaseTemplate::getWorkflowList() 
{
	throw DBException("Da sviluppare");
}

//TODO: Da sviluppare
bOS::IO::FilesList DataBaseTemplate::getFormsList() 
{
	throw DBException("Da sviluppare");
}

bOS::CoreString::String DataBaseTemplate::getForm(const char* acFormName) 
{
	throw DBException("Da sviluppare");
}

void DataBaseTemplate::setForm(const char* acFormName, const char* acJsContent) 
{
	throw DBException("Da sviluppare");
}


//TODO: Da sviluppare
String DataBaseTemplate::getCheckListFolder() 
{
	throw DBException("Da sviluppare");
}

WorkflowProcesses::WorkflowProcess* DataBaseTemplate::getProcessTemplate(const char* acWorkflowName) 
{
	throw DBException("Da sviluppare");
}

void DataBaseTemplate::addWorkflow (WorkflowProcesses::WorkflowProcess *) {
	throw DBException("Da sviluppare");
}
