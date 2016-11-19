#include "CommonDefines.h"

#include "WorkFlowThread.h"
using namespace WorkflowEngine::Criteria::Core;

void WorkFlowThread::run()
{
	CM_CODEBLOCK(run)

	CM_TRACE_CODEPATH( "Adding new Workflow to running workflow list.")
	wManager->add(wWF);

	try
	{
		resultValue = (int)wWF->start();
	}
	catch ( ... )
	{
		CM_TRACE_ERROR( "Workflow has terminated with error.")

		//TODO: 
		resultValue=1;
	}
		
	CM_TRACE_CODEPATH( "Workflow has terminated. Removing from list.")
	wManager->remove( wWF->getWorkflowID() );
}


void WorkFlowThread::setWorkflowId(const char* ID)
{
	wWF->setWorkflowId(ID);
}