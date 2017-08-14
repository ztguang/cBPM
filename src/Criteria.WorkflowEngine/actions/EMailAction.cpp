#include "CommonDefines.h"

#include "EMailAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Mail::Action;

EMailAction::EMailAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
: BaseAction(process, task)
{
    assert( process != NULL);
}

EMailAction::~EMailAction()
{
}

int EMailAction::evaluateAction()
{
	return BaseAction::evaluateAction();
}
