#include "CommonDefines.h"

#include "WAPIForms.h"

#include "bOS/bOS.h"
#include "bOS/bOSStringUtils.h"
#include "bOS/bOSStringBuffer.h"
using namespace bOS::CoreString;

#include "bOS/bOSFileSystem.h"

#include "bOS/bOSXMLNode.h"

//DB
#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

//Engine
#include "Engine.h"
using namespace WorkflowEngine::Criteria::Core;

#include "WAPIError.h"

extern "C" ENGINE_API char* getFormsList(Response* response)
{
	CM_CODEBLOCK(WAPI::getFormsList)

	bOS::IO::FilesList vFiles;
	try
	{
		vFiles =  DataBaseHelper::instance()->getFormsList();
	}
	catch (DBException& dbErr )
	{
		CM_TRACE_ERROR(dbErr.getMessage())
		response->iCode = WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND;
		response->sMsg = WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND_DESCR;

	}
	bOS::XML::XMLNode root;
	root.setName ("Forms");

	bOS::XML::XMLNode* nodeChild;
	unsigned int uiSize = vFiles.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		nodeChild = new bOS::XML::XMLNode ("Form", "") ;
		nodeChild->addAttribute ( new bOS::XML::XMLAttribute ( "Name", vFiles.at(i)) );
		root.addNode ( nodeChild);
	}

	return StringUtils::toChar (root.getXMLText() );
}

extern "C" ENGINE_API char* getForm(char* acName, Response* response)
{
	CM_CODEBLOCK(getForm)
	assert(response!=NULL);

	//DataTypes vDataTypes;
	try
	{
		String sForm = DataBaseHelper::instance()->getForm(acName);
		return StringUtils::toChar (sForm);
	}
	catch ( DBException& dbErr)
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
		return NULL;
	}
}

extern "C" ENGINE_API void setForm(char* acName, char* acJsContent, Response* response)
{
	CM_CODEBLOCK(setForm)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->setForm(acName, (const char*)acJsContent);
	}
	catch ( DBException& dbErr)
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
	}
}
