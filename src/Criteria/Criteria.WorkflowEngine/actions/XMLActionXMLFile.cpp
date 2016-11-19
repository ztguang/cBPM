#include "CommonDefines.h"

#include "XMLActionXMLFile.h"
using namespace WorkflowEngine::Criteria::BasicTask::XML::Action;

#include "bOS.h"
#include "bOSFileSystem.h"
#include "bOSFileSystemException.h"
#include "bOSXSLTManager.h"

#include "bOSFileSystem.h"
using namespace bOS::IO;

String XMLActionXMLFile::XMLFILE		= "XMLFILE";
String XMLActionXMLFile::XMLATTRIBUTE	= "XMLATTRIBUTE";


XMLActionXMLFile::XMLActionXMLFile( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, bool _ReadFile ) 
    : XMLAction(process, task) 
{
	bReadFile = _ReadFile;
}

XMLActionXMLFile::~XMLActionXMLFile() 
{
}

int XMLActionXMLFile::action( String& result )
{
	CM_CODEBLOCK(action)

    int feErr = this->evaluateAction();
    
	if ( feErr != FE_OK)
	{
		CM_TRACE_CODEPATH( "No Action performed.")
        return feErr;
	}

	bool bRet=true;

	if ( bReadFile )
	{
		StringBuffer sFileBody;
		try
		{
			bOS::IO::FileSystem::getStringFile (sFile.c_str(), sFileBody);
		}
		catch ( bOS::Exception::FileSystemException& fsErr)
		{
			CM_TRACE_ERROR("Impossible to read[" << sFile << "]. Err[" << fsErr.getMessage() << "]")
			return FE_TASK_TASKACTION_ERROR;
			
		}

		WorkflowRelevantData::Attribute* attribute = NULL;
		attribute = _varsContext.add(sAttribute.c_str(), WorkflowRelevantData::XMLAttribute::XML_TYPE.c_str());
		attribute->setValue (sFileBody.getData());
	}
	else
	{
		try
		{
			bOS::IO::FileSystem::saveStringFile(sFile.c_str(), sAttribute);
		}
		catch ( bOS::Exception::FileSystemException& fsErr)
		{
			CM_TRACE_ERROR("Impossible to write[" << sFile << "]. Err[" << fsErr.getMessage() << "]")
			return FE_TASK_TASKACTION_ERROR;
		}
	}
	
	return FE_OK;
}

int XMLActionXMLFile::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	int iErr = XMLAction::evaluateAction ();
	
	if ( iErr != FE_OK && iErr != FE_TASK_TASKACTION_NONE)
	{
		CM_TRACE_CODEPATH( "No Action performed.")
        return iErr;
	}

	//TODO:
	//Designing an action for Email.
	WorkflowRelevantData::Attribute* var = NULL;
	
	var = getAttribute( XMLActionXMLFile::XMLFILE );
	if ( var != NULL ) 
	{
		//modify by mfarina on 22/05/2005 for bug 1
		//sFile = getEvaluatedParameter(var->getValue());
		sFile = getEvaluatedParameter(var->getValue(), var->getType().c_str());
	}
	else
	{
		CM_TRACE_ERROR("Attribute[" << XMLActionXMLFile::XMLFILE << "] not declared in Activity")
		return FE_TASK_TASKACTION_ERROR;
	}

	var = getAttribute( XMLActionXMLFile::XMLATTRIBUTE );
	if ( var != NULL ) 
	{
		//modify by mfarina on 22/05/2005 for bug 1
		//sAttribute = getEvaluatedParameter(var->getValue());
		sAttribute = getEvaluatedParameter(var->getValue(), var->getType().c_str());
	}
	else
	{
		CM_TRACE_ERROR("Attribute[" << XMLActionXMLFile::XMLATTRIBUTE << "] not declared in Activity")
		return FE_TASK_TASKACTION_ERROR;
	}

    return FE_OK;
}

