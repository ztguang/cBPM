#include "FileSystemDataBase.h"
using namespace DataManager::DataBase::FileSystem;

#include "bOSXMLException.h"
#include "DBException.h"

#include "bOSXMLHelper.h"
using namespace bOS::XML;

#include "bOSFileSystem.h"
#include "bOSFileSystemException.h"

#include "WorkflowProcess.h"
#include "Grants.h"
#include "Grant.h"

using namespace bOS::Core;

using namespace DataManager::Panorama::DataBase;
using namespace DataManager::Panorama::WorkflowParticipantsData;
using namespace DataManager::Panorama::WorkflowDataTypes;
using namespace DataManager::Panorama::WorkflowProcesses;
using namespace DataManager::Panorama::Common;
using namespace DataManager::Panorama::WorkflowServices;
using namespace DataManager::Panorama::WorkflowApplicationsData;

FileSystemDataBase::FileSystemDataBase() : DataBaseTemplate()
{
}

FileSystemDataBase::~FileSystemDataBase()
{
	;
}

void FileSystemDataBase::open(DataManager::Panorama::DataBase::FileSystemConnection* fs)
{
	CM_CODEBLOCK(FileSystemDataBase::open)

	XMLNode* node = fs->getXMLNode(0);
	
	
	fsConnection.init( node);
	delete node;

	String sFile;
	
	try
	{
		sFile = fsConnection.getRolesFile();
		CM_TRACE_INFO("Reading Role File [" << sFile << "]")
		vRoles.init( bOS::IO::File(sFile.c_str()) );
		CM_TRACE_INFO("Role File [" << sFile << "] acquired")

		CM_TRACE_INFO("Reading ProcessInstance folder [" << fsConnection.getProcessInstancesFolder() << "]")
		vProcesses.init(fsConnection.getProcessInstancesFolder().c_str(), true);
		CM_TRACE_INFO("ProcessInstance folder acquired")

		this->getDataTypes (vDataTypes);
	
	}
	catch( XMLException& xe)
	{
		CM_TRACE_FATAL("Error opening database. Err[" << xe.getMessage() << "]")
		throw xe;
	}
}

void FileSystemDataBase::close()
{
}

void FileSystemDataBase::getUser(User& user)
{
	try
	{
		vUsers.init( bOS::IO::File(fsConnection.getUsersFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	bool bFound = vUsers.getUser(&user);
	
	if ( !bFound )
		throw DBException(DB_RECORD_NOT_FOUND);
}

void FileSystemDataBase::getUsers(Users& _Users)
{
	try
	{
		_Users.init( bOS::IO::File(fsConnection.getUsersFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}
}

void FileSystemDataBase::addUser(const char* acUser)
{
	try
	{
		vUsers.init( bOS::IO::File(fsConnection.getUsersFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	bool bRet  = vUsers.addUser(acUser);
	
	if ( !bRet )
		throw DBException(DB_RECORD_ALREADY_PRESENT);

	XMLNode* node = vUsers.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getUsersFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::updateUser(const char* acUser)
{
	CM_CODEBLOCK(FileSystemDataBase::updateUser)

	try
	{
		vUsers.init( bOS::IO::File(fsConnection.getUsersFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	bool bRet = vUsers.updateUser(acUser);

	if ( !bRet )
		throw DBException(DB_RECORD_NOT_FOUND);

	XMLNode* node = vUsers.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getUsersFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::deleteUser(const char* acUserKey)
{
	try
	{
		vUsers.init( bOS::IO::File(fsConnection.getUsersFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	bool bRet = vUsers.deleteUser(acUserKey);

	if ( !bRet )
		throw DBException(DB_RECORD_NOT_FOUND);

	XMLNode* node = vUsers.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getUsersFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::getRole(Role& role)
{
	try
	{
		vRoles.init( bOS::IO::File(fsConnection.getRolesFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	bool bFound = vRoles.getRole(&role);
	
	if ( !bFound )
		throw DBException(DB_RECORD_NOT_FOUND);
}

bOS::IO::FilesList FileSystemDataBase::getWorkflowList()
{
	CM_CODEBLOCK(getWorkflowList)

	bOS::IO::FilesList files;

	try
	{
		CM_TRACE_CODEPATH("TemplatesFolder [" << fsConnection.getProcessTemplatesFolder().c_str() << "]")    //ztg add
		//bOS::IO::FileSystem::ls(fsConnection.getProcessTemplatesFolder().c_str(), files,".xml");
		bOS::IO::FileSystem::ls("/usr/share/nginx/html/database/processTemplate/", files,".xml");
	}
	catch ( bOS::Exception::FileSystemException& fsErr)
	{
		CM_TRACE_ERROR("Impossible to retrive WorkflowProcesses List.Err[" << fsErr.getMessage() << "]")
		throw DBException(DB_DIRECTORY_NOT_FOUND);
	}

	return files;
}

bOS::IO::FilesList FileSystemDataBase::getFormsList()
{
	CM_CODEBLOCK(getFormsList)

	bOS::IO::FilesList files;

	try
	{
		bOS::IO::FileSystem::ls(fsConnection.getFormsFolder().c_str(), files,".js");
	}
	catch ( bOS::Exception::FileSystemException& fsErr)
	{
		CM_TRACE_ERROR("Impossible to retrive Forms List.Err[" << fsErr.getMessage() << "]")
		throw DBException(DB_DIRECTORY_NOT_FOUND);
	}

	return files;
}

bOS::CoreString::String FileSystemDataBase::getForm(const char* acFormName)
{
	CM_CODEBLOCK(FileSystemDataBase::getForm)

	StringBuffer sWorkflowFile;
	sWorkflowFile.append(fsConnection.getFormsFolder().c_str());
	sWorkflowFile.append(SLASH);
	sWorkflowFile.append(acFormName);

	try
	{
		CM_TRACE_INFO("Try to Open[" << sWorkflowFile.getData() << "]")
		return bOS::IO::FileSystem::getStringFile(sWorkflowFile.getData());
	}
	catch ( XMLException& xmlErr )
	{
		CM_TRACE_ERROR("Impossible to open[" << sWorkflowFile.getData() << "]. Err[" << xmlErr.getMessage() << "]")
		throw DBException(XFS_FILE_NOT_FOUND);
	}
}

void FileSystemDataBase::setForm(const char* acFormName, const char* acJsContent) 
{
	CM_CODEBLOCK(FileSystemDataBase::setForm)

	StringBuffer sWorkflowFile;
	sWorkflowFile.append(fsConnection.getFormsFolder().c_str());
	sWorkflowFile.append(SLASH);
	sWorkflowFile.append(acFormName);

	try
	{
		CM_TRACE_INFO("Try to Save[" << sWorkflowFile.getData() << "]")
		bOS::CoreString::String jsContent = acJsContent;
		bOS::IO::FileSystem::saveStringFile(sWorkflowFile.getData(), jsContent);
	}
	catch ( XMLException& xmlErr )
	{
		CM_TRACE_ERROR("Impossible to open[" << sWorkflowFile.getData() << "]. Err[" << xmlErr.getMessage() << "]")
		throw DBException(XFS_FILE_NOT_FOUND);
	}
}


String FileSystemDataBase::getCheckListFolder()
{
	CM_CODEBLOCK(getCheckListFolder)
	return fsConnection.getCheckListFolder();
}

void FileSystemDataBase::getRoles(Roles& _Roles)
{
	try
	{
		_Roles.init( bOS::IO::File(fsConnection.getRolesFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}
}

void FileSystemDataBase::addRole(const char* acRole)
{
	try
	{
		vRoles.init( bOS::IO::File(fsConnection.getRolesFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	bool bRet  = vRoles.addRole(acRole);
	
	if ( !bRet )
		throw DBException(DB_RECORD_ALREADY_PRESENT);

	XMLNode* node = vRoles.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getRolesFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::updateRole(const char* acRole)
{
	try
	{
		vRoles.init( bOS::IO::File(fsConnection.getRolesFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	bool bRet = vRoles.updateRole(acRole);

	if ( !bRet )
		throw DBException(DB_RECORD_NOT_FOUND);

	XMLNode* node = vRoles.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getRolesFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::deleteRole(const char* acRoleKey)
{
	try
	{
		vRoles.init( bOS::IO::File(fsConnection.getRolesFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	bool bRet = vRoles.deleteRole(acRoleKey);

	if ( !bRet )
		throw DBException(DB_RECORD_NOT_FOUND);

	XMLNode* node = vRoles.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getRolesFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::addUserToRole(const char* acUser, const char* acRoleKey)
{
	try
	{
		vRoles.init( bOS::IO::File(fsConnection.getRolesFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	Role role;
	role.setKey (acRoleKey);

	bool bRet = vRoles.getRole(&role);

	if ( !bRet )
		throw DBException(DB_RECORD_NOT_FOUND);

	Users& users = role.getUsers();

	bRet = users.addUser(acUser);
	if ( !bRet )
		throw DBException(DB_RECORD_ALREADY_PRESENT);

	XMLNode* node = vRoles.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getRolesFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::deleteUserFromRole(const char* acUserKey, const char* acRoleKey)
{
	try
	{
		vRoles.init( bOS::IO::File(fsConnection.getRolesFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	Role role;
	role.setKey (acRoleKey);

	bool bRet = vRoles.getRole(&role);

	if ( !bRet )
		throw DBException(DB_RECORD_NOT_FOUND);

	Users& users = role.getUsers();

	users.deleteUser(acUserKey);
	if ( !bRet )
		throw DBException(DB_RECORD_NOT_FOUND);

	XMLNode* node = vRoles.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getRolesFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::getRolesByUser(const char* acUserKey, DataManager::Panorama::WorkflowParticipantsData::Roles& roles)
{
	try
	{
		vRoles.init( bOS::IO::File(fsConnection.getRolesFile().c_str()) );
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	bool bRet = vRoles.getRolesByUser(acUserKey, &roles);

	if ( !bRet )
		throw DBException(DB_RECORD_NOT_FOUND);
}

void FileSystemDataBase::getDataTypes(DataTypes& _DataTypes)
{
	CM_CODEBLOCK(FileSystemDataBase::getDataTypes)

	DataBaseObject* dbObj = fsConnection.getObject(XMLDataBaseObject::DATATYPES_TYPE);
	
	try
	{
		if ( (dbObj == NULL) || dbObj->isFileRepository() )  {
			CM_TRACE_DEBUG("Reading File [" << fsConnection.getResultTypeFile().c_str() << "]")
			_DataTypes.init( bOS::IO::File(fsConnection.getResultTypeFile().c_str()) );
		} else {
			CM_TRACE_DEBUG("Reading Folder [" << fsConnection.getResultTypeFile().c_str() << "]")

			bOS::IO::FilesList files;
			try
			{
				bOS::IO::FileSystem::ls(fsConnection.getResultTypeFile().c_str(), files,".xml");
			}
			catch ( bOS::Exception::FileSystemException& fsErr)
			{
				CM_TRACE_ERROR("Impossible to retrive WorkflowProcesses List.Err[" << fsErr.getMessage() << "]")
				throw DBException(DB_DIRECTORY_NOT_FOUND);
			}
			CM_TRACE_CODEPATH("[" << files.size() << "] DataTypes file to read")
			for ( unsigned int i=0; i<files.size(); i++) {
				StringBuffer file2Read;
				file2Read.append(fsConnection.getResultTypeFile());
				file2Read.append(SLASH);
				file2Read.append(files.at(i));

				CM_TRACE_CODEPATH("DataType file [" << file2Read.getData() << "] reading")
				_DataTypes.addFile(bOS::IO::File(file2Read.getData()));
				CM_TRACE_CODEPATH("DataType file [" << file2Read.getData() << "] readen")
			}
		}
	}
	catch( XMLException& xeErr)
	{
		CM_TRACE_ERROR("Error Retrieving DataTypes[" << xeErr.getMessage() << "]")

		throw DBException(xeErr.getMessage());
	}
}

void FileSystemDataBase::getDataType(DataType& _DataType)
{
	CM_CODEBLOCK(FileSystemDataBase::getDataType)

	/*
	DataTypes vDataTypes;
	this->getDataTypes (vDataTypes);
	*/

	DataType* datatype = vDataTypes.getDataType ( _DataType.getKey() );

	//TODO: Aggiungere la possibilit?di rileggerlo da files.
	if ( datatype == NULL )
		throw DBException(DB_RECORD_NOT_FOUND);

	XMLNode* node = datatype->getXMLNode(0);
	_DataType.init ( node );
	delete node;
}

void FileSystemDataBase::getActivities(Activities& vActivities, String sStatus, String sOwner, bool bOnlyMine)
{
	CM_CODEBLOCK(FileSystemDataBase::getActivities)
	vActivities.clear();

	bOS::IO::FilesList files;
	StringBuffer sPath;
	sPath.append(fsConnection.getProcessInstancesFolder());

	bOS::IO::FileSystem::ls(sPath.getData(), files,".xml");
	
	unsigned int iSize = files.size();
	StringBuffer sProcessFile;
	for ( unsigned int i=0; i<iSize;i++)
	{
		String s=files.at(i);

		CM_TRACE_CODEPATH("Process File[" << s << "]")

		if ( s == "table.xml" )
			continue;

		sProcessFile.clear();
		sProcessFile.append (sPath.getData());
		sProcessFile.append(SLASH);
		sProcessFile.append(s);
		WorkflowProcess process;
		try
		{
			process.load( sProcessFile.getData() );
		}
		catch ( XMLException xmlErr) 
		{
			CM_TRACE_ERROR("Impossible to load process[" << sProcessFile.getData() << "]");
		}

		Activities& activities = process.getActivities();
		unsigned int iSize = activities.size();
		bool bAddActivity;
		for ( unsigned int i=0; i<iSize; i++)
		{
			bAddActivity = false;
			Activity* activity = (Activity*)activities.at(i);

			//only form Administrator.
			if ( sOwner.length() == 0 )
			{
				bAddActivity = true;
			}
			else
			{
				if ( (sOwner == activity->getOwner()) && bOnlyMine )
				{
					bAddActivity = true;
				}
				else if ( !bOnlyMine && (activity->getOwner() == "CRITERIA") )
				{
					Grants& grants = activity->getGrants();

					//TODO: Ricavare il ruolo.
					if ( grants.check (sOwner.c_str(), NULL, XMLGrant::VISIBLE_TYPE.c_str()) )
					{
						bAddActivity = true;
					}
				}
			}

			if ( bAddActivity ) 
			{
				if ( sStatus.length() == 0 )
				{
					//all
					bAddActivity = true;
				}
				else
				{
					if ( sStatus == activity->getStatus() )
					{
						bAddActivity = true;
					}
					else
						bAddActivity = false;
				}
			}

			if ( bAddActivity )
			{
				activity->setProcessId ( process.getProcessId() );
				vActivities.addActivity (*activity);
			}

		}
	}
}

void FileSystemDataBase::getAllActivities(WorkflowProcesses::Activities&, String sStatus, String sOwner, bool bNotMine)
{
	//TODO:
}

void FileSystemDataBase::getAllMyActivities(WorkflowProcesses::Activities&, String sStatus, String sOwner)
{
	//TODO:
}

void FileSystemDataBase::getNotifies(WorkflowProcesses::Activities&, String sOwner)
{
	//TODO:
}

void FileSystemDataBase::getActivityRunningNotifies(WorkflowProcesses::Activities&, String sOwner)
{
	//TODO:
}

void FileSystemDataBase::insertProcess(String& lProcessId, WorkflowProcess& process, bool b2Prepared)
{
	CM_CODEBLOCK(DataBaseHelper::createProcess)
	if ( lProcessId.compare("") == 0 )
	{
		lProcessId = vProcesses.insert(&process, true);
	}
	else
	{
		vProcesses.insert(&process, process.getFileName(), false);
	}
}

//Services
void FileSystemDataBase::getServices(DataManager::Panorama::WorkflowServices::Services& _Services)
{
	CM_CODEBLOCK(FileSystemDataBase::getServices)

	try
	{
		CM_TRACE_DEBUG("Getting service list from [" << fsConnection.getServicesFile() << "]")
		_Services.init( bOS::IO::File(fsConnection.getServicesFile().c_str()) );
		CM_TRACE_DEBUG("Service list retrieved. Nr Service[" << _Services.size() << "]")
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}
}

void FileSystemDataBase::getServicesForUser(const char* acUser, DataManager::Panorama::WorkflowServices::Services& vServices)
{
	CM_CODEBLOCK(FileSystemDataBase::getServicesForUser)

	CM_TRACE_DEBUG("Retrieving Service for user[" << acUser << "]")

	Roles roles;
	this->getRolesByUser(acUser, roles);

	Services _Services;

	this->getServices(_Services);
	unsigned int uiSize = _Services.size();

	for ( unsigned int i=0; i<uiSize; i++)
	{
		Service* service = (Service*)_Services.at(i);

		Users& users = service->getUsers();
		Roles& serviceRoles = service->getRoles();

		CM_TRACE_DEBUG("Service retrieved[" << service->getName() <<"]. Now check the grants")
		if ( ((users.size() == 0 ) && ( serviceRoles.size()==0) ) || users.checkUser(acUser) || serviceRoles.checkRoles(&roles) )
		{
			//TODO: Service: CopyConstructor
			Service* service2Ret = new Service();

			XMLNode* node = service->getXMLNode(0);
			service2Ret->init( node);
			delete node;

			CM_TRACE_DEBUG("Add Service[" << service->getName() << "] to list.")

			vServices.add ((bOS::Collections::CollectionEntry*)service2Ret);
		}
	}
}

void FileSystemDataBase::addService(const char* acService)
{
	Services vServices;

	this->getServices(vServices);

	bool bRet  = vServices.addService(acService);
	
	if ( !bRet )
		throw DBException(DB_RECORD_ALREADY_PRESENT);

	XMLNode* node = vServices.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getServicesFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::deleteService(const char* acServiceName)
{
	Services vServices;

	this->getServices(vServices);

	bool bRet = vServices.deleteService(acServiceName);

	if ( !bRet )
		throw DBException(DB_RECORD_NOT_FOUND);

	XMLNode* node = vServices.getXMLNode(0);
	XMLHelper::saveToFile (fsConnection.getServicesFile().c_str(), node);
	delete node;
}

void FileSystemDataBase::getApplications(Applications& _Applications)
{
	CM_CODEBLOCK(FileSystemDataBase::getApplications)

	DataBaseObject* dbObj = fsConnection.getObject(XMLDataBaseObject::APPLICATIONS_TYPE);
	
	try
	{
		if ( (dbObj == NULL) || dbObj->isFileRepository() )  {
			CM_TRACE_DEBUG("Reading File [" << fsConnection.getApplicationsFile().c_str() << "]")
			_Applications.init( bOS::IO::File(fsConnection.getApplicationsFile().c_str()) );
		} else {
			CM_TRACE_DEBUG("Reading Folder [" << fsConnection.getApplicationsFile().c_str() << "]")

			bOS::IO::FilesList files;
			try
			{
				bOS::IO::FileSystem::ls(fsConnection.getApplicationsFile().c_str(), files,".xml");
			}
			catch ( bOS::Exception::FileSystemException& fsErr)
			{
				CM_TRACE_ERROR("Impossible to retrive WorkflowProcesses List.Err[" << fsErr.getMessage() << "]")
				throw DBException(DB_DIRECTORY_NOT_FOUND);
			}
			CM_TRACE_CODEPATH("[" << files.size() << "] Applications file to read")
			for ( unsigned int i=0; i<files.size(); i++) {
				StringBuffer file2Read;
				file2Read.append(fsConnection.getApplicationsFile());
				file2Read.append(SLASH);
				file2Read.append(files.at(i));

				CM_TRACE_CODEPATH("Applications file [" << file2Read.getData() << "] reading")
				_Applications.addFile(bOS::IO::File(file2Read.getData()));
				CM_TRACE_CODEPATH("Applications file [" << file2Read.getData() << "] readen")
			}
		}
	}
	catch( XMLException& xeErr)
	{
		CM_TRACE_ERROR("Error Retrieving DataTypes[" << xeErr.getMessage() << "]")

		throw DBException(xeErr.getMessage());
	}
}

void FileSystemDataBase::getProcessInstance(DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process)
{
	try
	{
		vProcesses.get(&process);
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}
}

void FileSystemDataBase::getProcessHeader(DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process)
{
	try
	{
		vProcesses.get(&process);
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}
}

void FileSystemDataBase::getProcesses(WorkflowProcesses::Processes& vProcesses)
{
	//TODO:
	return;
}

void FileSystemDataBase::updateProcess(DataManager::Panorama::WorkflowProcesses::WorkflowProcess* process)
{
	try
	{
		vProcesses.update(process);
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}
}

void FileSystemDataBase::getAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes)
{
	WorkflowProcess process;
	process.setProcessId ( vAttributes.getProcessId());
	try
	{
		vProcesses.get(&process);
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	if ( vAttributes.getActivityId().length() > 0 )
	{
		Activity* activity = process.getActivities().get (vAttributes.getActivityId());
		vAttributes.add ( activity->getAttributes()) ;

	}
	else
	{
		vAttributes.add ( process.getAttributes()) ;
	}

}

void FileSystemDataBase::getProcessAttribute(const char* processId,DataManager::Panorama::WorkflowRelevantData::Attribute& attribute)
{
	//TODO
}


void FileSystemDataBase::updateAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes)
{
	//TODO: FileSystemDataBase::updateAttributes	
}

void FileSystemDataBase::updateActivity(DataManager::Panorama::WorkflowProcesses::Activity* activity, bool bRecursive)
{
	//TODO: FileSystemDataBase::updateActivity
}

void FileSystemDataBase::updateActivityCheckStatus(DataManager::Panorama::WorkflowProcesses::Activity* activity, string sStatus2Check)
{
	//TODO: FileSystemDataBase::updateActivity
}

void FileSystemDataBase::updateActivityNoOwner(DataManager::Panorama::WorkflowProcesses::Activity* activity)
{
	//TODO: FileSystemDataBase::updateActivity
}

void FileSystemDataBase::insertReport(WorkflowProcesses::Report& report)
{
	//TODO: non ?necessario
}

void FileSystemDataBase::getReports (WorkflowProcesses::Reports& vReports)
{
	WorkflowProcess process;
	process.setProcessId ( vReports.getProcessId());
	try
	{
		vProcesses.get(&process);
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	XMLNode* node = process.getReports().getXMLNode(0);
	vReports.init ( node);
	delete node;
}

void FileSystemDataBase::getActivity(DataManager::Panorama::WorkflowProcesses::Activity& activity)
{
	WorkflowProcess process;
	process.setProcessId ( activity.getProcessId());
	try
	{
		vProcesses.get(&process);
	}
	catch( XMLException& xeErr)
	{
		throw DBException(xeErr.getMessage());
	}

	Activity* activity2Ret = process.getActivities().get (activity.getActivityName());
	if ( activity2Ret == NULL )
	{
		throw DBException(DB_RECORD_NOT_FOUND);
	}

	XMLNode* node = activity2Ret->getXMLNode(0);
	activity.init ( node);
	delete node;
}

void FileSystemDataBase::saveMessageFlow(WorkflowProcesses::Message* message)
{
}


DataManager::Panorama::WorkflowProcesses::WorkflowProcess* FileSystemDataBase::getProcessTemplate(const char* acWorkflowName)
{
	CM_CODEBLOCK(FileSystemDataBase::getProcessTemplate)

	StringBuffer sWorkflowFile;
	sWorkflowFile.append(fsConnection.getProcessTemplatesFolder().c_str());
	sWorkflowFile.append(SLASH);
	sWorkflowFile.append(acWorkflowName);
	sWorkflowFile.append(".xml");

	DataManager::Panorama::WorkflowProcesses::WorkflowProcess* workflow = NULL;
	workflow = new DataManager::Panorama::WorkflowProcesses::WorkflowProcess();
	try
	{
		CM_TRACE_CODEPATH("Retrieving WorkflowFile[" << sWorkflowFile.getData() << "]")
		XMLFile::loadAndInit(sWorkflowFile.getData(), workflow);
	}
	catch ( XMLException& xmlErr )
	{
		CM_TRACE_ERROR("Impossible to open[" << sWorkflowFile.getData() << "]. Err[" << xmlErr.getMessage() << "]")
		throw DBException(XFS_FILE_NOT_FOUND);
	}

	return workflow;
}

void FileSystemDataBase::addWorkflow (WorkflowProcesses::WorkflowProcess* workflow) {
	
	CM_CODEBLOCK(FileSystemDataBase::addWorkflow)
	
		try
	{
		StringBuffer sFile;
		sFile.append (fsConnection.getCheckListFolder());
		sFile.append (SLASH);
		sFile.append (workflow->getName());
		sFile.append (".xml");

		CM_TRACE_DEBUG("Add Process[" << sFile.getData() << "]")
		workflow->write2File (sFile.getData());
	}
	catch ( XMLException& xmlErr )
	{
		CM_TRACE_ERROR("Impossible to write process.[" << xmlErr.getMessage() << "]")
		throw DBException(XFS_FILE_NOT_WRITE);
	}

}
