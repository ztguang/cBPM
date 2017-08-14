#include "CommonDefines.h"

#include "IterationAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Iteration::Action;

const String IterationAction::LOOP_STEP_ATTRIBUTE	= "LOOP_STEP";
const String IterationAction::LOOP_START_ATTRIBUTE	= "LOOP_START";

IterationAction::IterationAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
: BaseAction(process, task) 
{
}

IterationAction::~IterationAction()
{
}

int IterationAction::evaluateAction()
{
	return BaseAction::evaluateAction();
}
