#include "CommonDefines.h"

#include "ConditionAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Condition::Action;

ConditionAction::ConditionAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) : BaseAction(process, task) 
{
	CM_CODEBLOCK(ConditionAction)
}

ConditionAction::~ConditionAction()
{
	CM_CODEBLOCK(~ConditionAction)
}

int ConditionAction::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	return BaseAction::evaluateAction();
}
