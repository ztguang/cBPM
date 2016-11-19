#include "CommonDefines.h"

#include "WAPIWorkflow.h"
#include "FileSystemDataBase.h"     //ztg add
using namespace DataManager::DataBase::FileSystem;

#include "bOS.h"
#include "bOSStringUtils.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

#include "bOSFileSystem.h"

#include "bOSXMLNode.h"

//DB
#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "WorkflowProcess.h"
using namespace DataManager::Panorama::WorkflowProcesses;

//Engine
#include "Engine.h"
using namespace WorkflowEngine::Criteria::Core;

#include "WAPIError.h"

extern "C" ENGINE_API char* getWorkflowList(Response* response)
{
	CM_CODEBLOCK(WAPI::getWorkflowList)

	bOS::IO::FilesList vFiles;
	try
	{
		vFiles =  DataBaseHelper::instance()->getWorkflowList();          //ztg del
		//vFiles =  FileSystemDataBase::instance()->getWorkflowList();       //ztg add
	}
	catch (DBException& dbErr )
	{
		CM_TRACE_ERROR(dbErr.getMessage())
		response->iCode = WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND;
		response->sMsg = WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND_DESCR;

	}
	bOS::XML::XMLNode root;

	root.setName (XMLWorkflowProcesses::MAIN_NODE.c_str());

	bOS::XML::XMLNode* nodeChild;
	unsigned int uiSize = vFiles.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		nodeChild = new bOS::XML::XMLNode (XMLWorkflowProcess::MAIN_NODE.c_str(), "") ;
		nodeChild->addAttribute ( new bOS::XML::XMLAttribute ( XMLWorkflowProcess::NAME_ATTRIBUTE.c_str(), vFiles.at(i)) );
		root.addNode ( nodeChild);
	}

	return StringUtils::toChar (root.getXMLText() );
}

extern "C" ENGINE_API char* getWorkflowRunningList(Response* response)
{
	CM_CODEBLOCK(WAPI::getWorkflowRunningList)

	std::vector<String> vWorkflows;
	vWorkflows = Engine::instance()->getWorkflowRunningList();

	String sXml = "<WORKFLOWS>";
	unsigned int uiSize = vWorkflows.size();
	for ( unsigned int i=0;i<uiSize;i++)
	{
		sXml+= "<WORKFLOW>";
		sXml+= vWorkflows.at(i);
		sXml+= "</WORKFLOW>";
	}

	sXml+= "</WORKFLOWS>";

	return StringUtils::toChar (sXml);
}

extern "C" ENGINE_API void addWorkflow(char* acWorkflow, Response* response)
{
	CM_CODEBLOCK(WAPI::addWorkflow)

	assert(acWorkflow != NULL );

	try
	{
		DataBaseHelper::instance()->addWorkflow (acWorkflow);
	}
	catch ( DBException& dbErr)
	{
		CM_TRACE_ERROR(dbErr.getMessage())
		response->iCode = WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND;
		response->sMsg = WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND_DESCR;
	}
}
