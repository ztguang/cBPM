#include "CommonDefines.h"

#include "PrimitiveAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Primitive::Action;

const String PrimitiveAction::DEFAULT_RESULT_ATTRIBUTE	= "Primitive";

PrimitiveAction::PrimitiveAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
: BaseAction(process, task)
{
	_Process = new Process();
    assert( _Process != NULL);
}

PrimitiveAction::~PrimitiveAction()
{
    if ( _Process != NULL )
        delete _Process;

    _Arguments.clear();

}
int PrimitiveAction::evaluateAction()
{
	return BaseAction::evaluateAction();
}
