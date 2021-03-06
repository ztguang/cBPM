#include "CommonDefines.h"

#include "WAPIProcess.h"

#include "bOSStringUtils.h"

//DB
#include "DataBaseHelper.h"
#include "DBException.h" 
using namespace DataManager::DataBase;

#include "WorkflowProcess.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "Engine.h"
#include "EngineException.h"
using namespace WorkflowEngine::Criteria;

#include "DataTypes.h"
#include "DataType.h"
using namespace DataManager::Panorama::WorkflowDataTypes;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

#include "WAPIError.h"

extern "C" ENGINE_API char* getProcessInstance(char* acProcessID, Response* response)
{
	CM_CODEBLOCK(WAPI::getProcessInstance)
	response->iCode = 0;
	string sProcess = "";

	try
	{
		WorkflowProcess* process = DataBaseHelper::instance()->getProcessInstance (acProcessID);
		sProcess = process->getXMLString(0);
		DataBaseHelper::instance()->releaseProcess (process);
		//delete process;
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Process.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());

		return NULL;
	}

	return StringUtils::toChar(sProcess);

}

extern "C" ENGINE_API char* LoadProcessInstance(char* lProcessID, Response* response)
{
	CM_CODEBLOCK(WAPI::LoadProcessInstance)
	response->iCode = 0;
	string sProcess = "";

	try
	{
		WorkflowProcess* process = DataBaseHelper::instance()->LoadProcessInstance (lProcessID);
		sProcess = process->getXMLString(0);
		delete process;
		//delete process;
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Process.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());

		return NULL;
	}

	return StringUtils::toChar(sProcess);

}


extern "C" ENGINE_API char* getProcessHeader(char* lProcessID, Response* response)
{
	CM_CODEBLOCK(WAPI::getProcessHeader)
	response->iCode = 0;
	string sProcess = "";

	try
	{
		WorkflowProcess* process = DataBaseHelper::instance()->getProcessHeader (lProcessID);
		sProcess = process->getXMLString(0);
		//DataBaseHelper::instance()->releaseProcess (process);
		delete process;
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Process.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());

		return NULL;
	}

	return StringUtils::toChar(sProcess);

}

extern "C" ENGINE_API char* getNewProcessHeader(char* acProcessID, Response* response)
{
	CM_CODEBLOCK(WAPI::getProcessHeader)
	response->iCode = 0;
	string sProcess = "";

	try
	{
		WorkflowProcess* process = DataBaseHelper::instance()->getNewProcessHeader (acProcessID);
		sProcess = process->getXMLString(0);
		//DataBaseHelper::instance()->releaseProcess (process);
		delete process;
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Process.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());

		return NULL;
	}

	return StringUtils::toChar(sProcess);

}

extern "C" ENGINE_API char* getProcessStatus(char* acProcessID, Response* response)
{
	CM_CODEBLOCK(WAPI::getProcessStatus)
	response->iCode = 0;
	string sProcess = "";

	bOS::CoreString::String sStatus;
	try
	{
		 sStatus = DataBaseHelper::instance()->getProcessStatus(acProcessID);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Process.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());

		return NULL;
	}

	return StringUtils::toChar(sStatus);

}

extern "C" ENGINE_API char* getProcessInstanceAttributes(char* processId, Response* response)
{
	CM_CODEBLOCK(WAPI::getProcessInstanceAttributes)

	Attributes vAttributes;
	vAttributes.setProcessId (processId);

	try
	{
		DataBaseHelper::instance()->getAttributes(vAttributes);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Attributes.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());

		return NULL;
	}

	return StringUtils::toChar(vAttributes.getXMLString(0));
}

extern "C" ENGINE_API char* getNextActivityList(char* lProcessID, char* acActivityName, Response* response)
{
	CM_CODEBLOCK(WAPI::getNextActivityList)

	CM_TRACE_CODEPATH("Invoked with Process[" << lProcessID << "] Activity[" << acActivityName << "]")
	WorkflowProcess* process = NULL;
	try
	{
		process = DataBaseHelper::instance()->getProcessInstance(lProcessID);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Attributes.[" << dbErr.getMessage() << "]")
		CM_TRACE_ERROR("Process Id[" << lProcessID << "] not found.")
		response->iCode	= WAPIERR_PROCESS_NOT_FOUND;
		response->sMsg	= WAPIERR_PROCESS_NOT_FOUND_DESCR;

		return NULL;
	}

	ActivitiesList activityList = process->getNextActivityList(acActivityName);
	DataBaseHelper::instance()->releaseProcess (process);

	Activities vActivities;

	unsigned int uiSize = activityList.size();
	for ( unsigned int i=0; i<activityList.size(); i++)
	{
		Activity* activity = process->getActivities().get(activityList.at(i));
		vActivities.addActivity (*activity);
	}

	return StringUtils::toChar (vActivities.getXMLString(0));
}

extern "C" ENGINE_API char* getActivityResultList(char* lProcessId, char* acActivityName, Response* response)
{
	CM_CODEBLOCK(WAPI::getActivityResultList)
	CM_TRACE_CODEPATH("Invoked with Process[" << lProcessId << "] Activity[" << acActivityName << "]")

	WorkflowProcess* process = NULL;
	try
	{
		process = DataBaseHelper::instance()->getProcessInstance(lProcessId);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Attributes.[" << dbErr.getMessage() << "]")
		CM_TRACE_ERROR("Process Id[" << lProcessId << "] not found.")
		response->iCode	= WAPIERR_PROCESS_NOT_FOUND;
		response->sMsg	= WAPIERR_PROCESS_NOT_FOUND_DESCR;

		return NULL;
	}

	String sActivityName = acActivityName;
	Activity* activity = process->getActivities().get(sActivityName);
	String sDataTypeId = activity->getBehaviour().getDataType();

	DataBaseHelper::instance()->releaseProcess (process);

	DataTypes vDataTypes;
	try
	{
		DataBaseHelper::instance()->getDataTypes (vDataTypes);
	}
	catch ( DBException& dbErr) 
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
		return NULL;
	}

	DataType datatype;
	datatype.setKey ( sDataTypeId);

	DataType* datetype2Search = (DataType*)vDataTypes.get ((CollectionEntry*)&datatype);

	if ( datetype2Search == NULL )
	{
		response->iCode = WAPIERR_DATATYPE_NOTFOUND;
		response->sMsg = WAPIERR_DATATYPE_NOTFOUND_DESCR;
		return NULL;
	}
	else
	{
		return StringUtils::toChar (datetype2Search->getXMLString(0));
	}
}

extern "C" ENGINE_API char* PrepareProcessInstance(char* acProcess, char* acWorkflowName, Response* response )
{
	CM_CODEBLOCK(WAPI::PrepareProcessInstance)
	WorkflowProcess process;
	try
	{
		CM_TRACE_CODEPATH("Creating Process from Workflow[" << acWorkflowName << "]")
		DataBaseHelper::instance()->createProcess (acWorkflowName, process, true);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to create Process.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_PROCESS;
		response->sMsg = WAPIERR_PROCESS_DESCR;

		return NULL;
	}

	acProcess = StringUtils::toChar(process.getProcessId());
	return StringUtils::toChar(process.getXMLString(0));

}

extern "C" ENGINE_API char* createNewProcessInstance(const char* acWorkflowName, char* acProcess, Response* response )
{
	CM_CODEBLOCK(WAPI::createNewProcessInstance)
	CM_TRACE_CODEPATH("Creating Process from Workflow[" << acWorkflowName << "]")

	WorkflowProcess process;
	try
	{
		DataBaseHelper::instance()->createProcess(acWorkflowName, process, true);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to insert Process.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_USERS_USERKEY_ALREADY_EXIST;
		response->sMsg = WAPIERR_USERS_USERKEY_ALREADY_EXIST_DESCR;

		return NULL;
	}
	CM_TRACE_CODEPATH("Process Created correctly!")

	strcpy(acProcess,process.getProcessId());
	return StringUtils::toChar(process.getXMLString(0).c_str());
}

extern "C" ENGINE_API void createWorkflowProcess(const char* acWorkflowName, char* acProcessId, Response* response )
{
	CM_CODEBLOCK(WAPI::createWorkflowProcess)
	CM_TRACE_CODEPATH("Creating Process [" << acWorkflowName << "]")

	WorkflowProcess process;
	try
	{
		DataBaseHelper::instance()->createProcess(acWorkflowName, process, true);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to insert Process.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND;
		response->sMsg = WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND_DESCR;
		return;
	}

	strcpy(acProcessId, process.getProcessId());
}

extern "C" ENGINE_API void startProcessInstance(const char* acProcessID, Response* response)
{
	CM_CODEBLOCK(WAPI::startProcessInstance)
	CM_TRACE_CODEPATH("Executing Process Id[" << acProcessID << "]")

	try
	{
		Core::Engine::instance()->startWorkFlow(acProcessID);
	}
	catch ( Core::EngineException& feErr)
	{
		CM_TRACE_ERROR("Impossible to execute ProcessId[" << acProcessID << "]. Err[" << feErr.getMessage() << "]")

		response->iCode = feErr.getErrorCode();
		response->sMsg=StringUtils::toChar(feErr.getMessage());
	}
}

extern "C" ENGINE_API void startProcessInSynchWay(const char* acProcessID, Response* response)
{
	CM_CODEBLOCK(WAPI::startProcessInSynchWay)
	CM_TRACE_CODEPATH("Executing Process Id[" << acProcessID << "]")

	try
	{
		Core::Engine::instance()->startWorkFlowInSynchWay(acProcessID);
	}
	catch ( Core::EngineException& feErr)
	{
		CM_TRACE_ERROR("Impossible to execute ProcessId[" << acProcessID << "]. Err[" << feErr.getMessage() << "]")

		response->iCode = feErr.getErrorCode();
		response->sMsg=StringUtils::toChar(feErr.getMessage());
	}
}

extern "C" ENGINE_API void restartProcessInstance(char* acProcessID, char* acStatus, Response* response )
{
	CM_CODEBLOCK(WAPI::restartProcessInstance)
	CM_TRACE_CODEPATH("Executing Process Id[" << acProcessID << "] from Task[" << acStatus << "]")

	try
	{
		Core::Engine::instance()->restartWorkFlow(acProcessID, acStatus);
	}
	catch ( EngineException& feErr)
	{
		CM_TRACE_ERROR("Impossible to execute ProcessId[" << acProcessID << "] from Task[" << acStatus << "]. Err[" << feErr.getMessage() << "]")

		response->iCode = feErr.getErrorCode();
		response->sMsg=StringUtils::toChar(feErr.getMessage());
	}
}

extern "C" ENGINE_API void restartProcessInSynchWay(char* acProcessID, char* acStatus, Response* response )
{
	CM_CODEBLOCK(WAPI::restartProcessInSynchWay)
	CM_TRACE_CODEPATH("Executing Process Id[" << acProcessID << "] from Task[" << acStatus << "]")

	try
	{
		Core::Engine::instance()->restartWorkFlowInSynchWay(acProcessID,acStatus);
	}
	catch ( EngineException& feErr)
	{
		CM_TRACE_ERROR("Impossible to execute ProcessId[" << acProcessID << "] from Task[" << acStatus << "]. Err[" << feErr.getMessage() << "]")

		response->iCode = feErr.getErrorCode();
		response->sMsg=StringUtils::toChar(feErr.getMessage());
	}
}

extern "C" ENGINE_API char* setProcessInstanceAttributes(const char* acProcessID, const char* xmlAttributes, Response* response)
{
	CM_CODEBLOCK(WAPI::setProcessInstanceAttributes)
	
	/*
	WorkflowProcess* process = NULL;
	try
	{
		process = DataBaseHelper::instance()->getProcessInstance(lProcessId);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Attributes.[" << dbErr.getMessage() << "]")
		CM_TRACE_ERROR("Process Id[" << lProcessId << "] not found.")
		response->iCode	= WAPIERR_PROCESS_NOT_FOUND;
		response->sMsg	= WAPIERR_PROCESS_NOT_FOUND_DESCR;

		return NULL;
	}
	Attributes& vAttributes = process->getAttributes();
	*/
	Attributes vAttributes;
	vAttributes.setProcessId (acProcessID);

	try
	{
		DataBaseHelper::instance()->getAttributes(vAttributes);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Attributes.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());

		return NULL;
	}


	Attributes vAttributes2Set;
	vAttributes2Set.init (xmlAttributes);
	Attributes vAttributesNotFound;

	unsigned int uiSize = vAttributes2Set.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Attribute* attribute2Set = (Attribute*)vAttributes2Set.at(i);
		Attribute* attribute = vAttributes.get(attribute2Set->getName().c_str());

		if ( attribute != NULL ) 
		{
			attribute->setValue(attribute2Set->getValue());
		}
		else
		{
			vAttributesNotFound.add(*attribute2Set);
		}
	}

	DataBaseHelper::instance()->updateAttributes(vAttributes);
	//DataBaseHelper::instance()->releaseProcess (process);
	
	return StringUtils::toChar (vAttributesNotFound.getXMLString(0));
}

extern "C" ENGINE_API void UpdateProcessInstanceAttributes(char* acProcessId, char* xmlAttributes, Response* response)
{
	CM_CODEBLOCK(WAPI::UpdateProcessInstanceAttributes)
	
	Attributes vAttributes2Set;
	vAttributes2Set.init (xmlAttributes);

	vAttributes2Set.setProcessId (acProcessId);

	try
	{
		//Modify by mfarina on 24/01/06 for manage "Process" in memory
		//DataBaseHelper::instance()->updateAttributes(vAttributes2Set);
		DataBaseHelper::instance()->SetAttributes(vAttributes2Set);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to Update Process.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());
	}
}

extern "C" ENGINE_API long getNumberRunningWorkflow(Response* response)
{
	//CM_CODEBLOCK(WAPI::getNumberRunningWorkflow)
	long lWorkflow = 0;

	try
	{
		lWorkflow=Core::Engine::instance()->numberWorkflowRunning();
	}
	catch ( EngineException& feErr)
	{
		//CM_TRACE_ERROR("Impossible to retrieve running workflow number]. Err[" << feErr.getMessage() << "]")

		response->iCode = feErr.getErrorCode();
		response->sMsg=StringUtils::toChar(feErr.getMessage());
	}

	return lWorkflow;
}

extern "C" ENGINE_API char* getProcesses(Response* response)
{
	CM_CODEBLOCK(WAPI::getProcesses)

	WorkflowProcesses::Processes vProcesses;
	try
	{
		DataBaseHelper::instance()->getProcesses(vProcesses);
	}
	catch ( DBException& dbErr)
	{
		//CM_TRACE_ERROR("Impossible to retrieve running workflow number]. Err[" << feErr.getMessage() << "]")

		response->iCode = WAPIERR_PROCESS;
		response->sMsg=StringUtils::toChar(dbErr.getMessage());
		return NULL;
	}

	StringBuffer sXML;
	sXML.append ("<WorkflowsProcesses>");
	
	for ( unsigned int i=0; i<vProcesses.size(); i++)
	{
		WorkflowProcess* process = (WorkflowProcess*)vProcesses.at(i);
		sXML.append ( process->getXMLString(0));

		delete process;

	}

	sXML.append ("</WorkflowsProcesses>");

	return StringUtils::toChar(sXML.getData());
}

extern "C" ENGINE_API char* getProcessAttribute(char* acProcess, char* acAttributeName, Response* response )
{
	CM_CODEBLOCK(WAPI::getProcessAttribute)

	string sXML;
	try
	{
		Attribute attribute;
		attribute.setName (acAttributeName);
		DataBaseHelper::instance()->getProcessAttribute(acProcess, attribute);
		sXML = attribute.getValue();
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to insert Process.[" << dbErr.getMessage() << "]")
		//TODO: Error to define
		response->iCode = WAPIERR_USERS_USERKEY_ALREADY_EXIST;
		response->sMsg = WAPIERR_USERS_USERKEY_ALREADY_EXIST_DESCR;

		return NULL;
	}

	return StringUtils::toChar(sXML.c_str());

}
