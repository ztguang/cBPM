#include "CommonDefines.h"

#include "ProcessAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Process::Action;

#include "EngineException.h"
#include "WorkflowException.h"
#include "WorkflowManager.h"
using namespace WorkflowEngine::Criteria::Core;

ProcessAction::ProcessAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, int iLevel )
    : BaseAction(process, task)
{
    iPID = process->getProcessId();
    iWorkflowLevel = iLevel;
	bSequence=false;
	iOccurency=1;
}

ProcessAction::~ProcessAction()
{
}

int ProcessAction::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	//retrieve ProcessName
	WorkflowRelevantData::Attribute* attribute = this->getAttribute( WorkflowProcesses::XMLActivity::MARKER_PROCESSNAME);
	if ( attribute == NULL )
	{
		CM_TRACE_ERROR("Impossible to retrieve attribute[" << WorkflowProcesses::XMLActivity::MARKER_PROCESSNAME << "]")
		return FE_TASK_TASKACTION_NONE;
	}
	//modify by mfarina on 22/05/2005 for bug 1
	//sProcessName = this->getEvaluatedParameter(attribute->getValue());
	sProcessName = this->getEvaluatedParameter(attribute->getValue() , attribute->getType().c_str());

	attribute = this->getAttribute( WorkflowProcesses::XMLActivity::MARKER_EXECUTION );
	if ( attribute != NULL )
	{
		//modify by mfarina on 22/05/2005 for bug 1
		//String sValue = this->getEvaluatedParameter(attribute->getValue()); 
		String sValue = this->getEvaluatedParameter(attribute->getValue(), attribute->getType().c_str()); 

		if ( !strcmp(sValue.c_str(), WorkflowProcesses::XMLActivity::MARKER_SEQUENCE_EXECUTION.c_str()) )
		{
			bSequence = true;
		}
	}

	attribute = this->getAttribute( WorkflowProcesses::XMLActivity::MARKER_OCCURENCY);
	if ( attribute != NULL )
	{
		//modify by mfarina on 22/05/2005 for bug 1
		//iOccurency = atoi(this->getEvaluatedParameter(attribute->getValue()).c_str()); 
		iOccurency = atoi(this->getEvaluatedParameter(attribute->getValue(), attribute->getType().c_str()).c_str()); 
	}

    return FE_OK;
}
