#include "CommonDefines.h"

#include "XMLTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::XML;

//Action
#include "XMLAction.h"
#include "XMLActionXSLT.h"
#include "XMLActionXMLFile.h"
using namespace WorkflowEngine::Criteria::BasicTask::XML::Action;

XMLTask::XMLTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) : BaseTask(process, task)
{
}

XMLTask::~XMLTask()
{
}

int XMLTask::execute()
{
	CM_CODEBLOCK(execute)

	int feRet = BaseTask::execute();

	if ( feRet != FE_OK ) 
	{
		CM_TRACE_DEBUG("Error Executing Task. [" << feRet << "]")
		return feRet;
	}

	XMLAction* xmlAction = NULL;

	String sScriptType = _task->getBehaviour().getScriptType();
	if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::XML_XSLT_TYPE.c_str()) == 0 ) 
	{
			CM_TRACE_CODEPATH( "Executing Attach Primitive.")
            xmlAction = new XMLActionXSLT( _process, _task );
    }
	else if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::XML_FILE_READ_TYPE.c_str()) == 0 ) 
	{
			CM_TRACE_CODEPATH( "Executing Attach Primitive.")
            xmlAction = new XMLActionXMLFile( _process, _task, true );
    }
	else if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::XML_FILE_WRITE_TYPE.c_str()) == 0 ) 
	{
			CM_TRACE_CODEPATH( "Executing Attach Primitive.")
            xmlAction = new XMLActionXMLFile( _process, _task, false );
    }
	else
	{
            return FE_TASK_ACTIONTYPE_ERROR;
    }

    String sResult = "";
	feRet = xmlAction->action(sResult);

	CM_TRACE_CODEPATH( "Action is terminated with result.[" << sResult << "] ReturCode[" << feRet << "]")

	switch ( feRet )
	{
	case FE_OK:
	case FE_TASK_TASKACTION_NONE:
		_task->setResult(sResult);
		feRet = FE_OK;
		break;
	default:
		break;

	}
    _action = xmlAction;

	return feRet;
}

