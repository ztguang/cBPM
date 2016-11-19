#include "CommonDefines.h"

#include "BeginTask.h"
using namespace WorkflowEngine::Criteria::BasicTask;

BeginTask::BeginTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) : BaseTask(process, task) 
{
}

BeginTask::~BeginTask()
{
}

int BeginTask::execute()
{
	int feRet = BaseTask::execute();

	if ( feRet != FE_OK )
	{
		return feRet;
	}

    _task->setResult(String(""));

	return feRet;
}


