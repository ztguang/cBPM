#include "CommonDefines.h"

#include "XMLAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::XML::Action;

XMLAction::XMLAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
: BaseAction(process, task)
{
    assert( process != NULL);
}

XMLAction::~XMLAction()
{
}

int XMLAction::evaluateAction()
{
	return BaseAction::evaluateAction();
}
