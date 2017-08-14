#include "CommonDefines.h"

#include "SubFlowExitAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Process::Action;

#include "EngineException.h"
#include "Workflow.h"
#include "WorkflowException.h"
#include "WorkFlowThread.h"
#include "WorkflowManager.h"
using namespace WorkflowEngine::Criteria::Core;

SubFlowExitAction::SubFlowExitAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, int iLevel )
    : BaseAction(process, task)
{

	iWorkflowLevel = iLevel;
	parentProcess = process->getParentProcess();
	sTaskParentProcess = process->getTaskParentProcess();
	sReturn = "0";
}

SubFlowExitAction::~SubFlowExitAction()
{
}

int SubFlowExitAction::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	int iErr = BaseAction::evaluateAction ();

	if ( iErr != FE_OK ) 
	{
		return iErr;
	}

	Idioma::ItemListIterator iItem;
	Idioma::ItemInterface *pItem = _script->getFirstItem (iItem);

	while ( pItem ) 
	{
		switch ( pItem->getType() )
		{
		case Idioma::ITEM_FREETEXT:
			sReturn = ((Idioma::FreeText*)pItem)->getText();
			sReturn = this->getEvaluatedParameter(sReturn);
			break;

		}
		pItem = _script->getNextItem (iItem);
	}

    return FE_OK;
}

int SubFlowExitAction::action(String& sResult)
{
	CM_CODEBLOCK(SubFlowExitAction::action)

    int errCode = FE_OK;
	
	if ( bEvaluateAction )
	{
		errCode = evaluateAction();
		if ( errCode != FE_OK)
		{
			return errCode;
		}
	}

	if ( parentProcess.compare("") )
	{
		if ( process->exit2Manage() ) 
		{
			process->setExitManaged();
		
			Workflow* workflow;
			workflow = new Workflow(parentProcess.c_str());

			/**/
			CM_TRACE_DEBUG("Exporting Attributes from process child to process father variables context.")
			int iSize = process->getAttributes().size();
			for ( int i=0;i<iSize;i++)
			{
				WorkflowRelevantData::Attribute* var = (WorkflowRelevantData::Attribute*)process->getAttributes().at(i);

				CM_TRACE_CODEPATH("Attribute[" << var->getName() << "]")
				
				if ( (strcmp( var->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_OUTPUT.c_str()) == 0) ||
					(strcmp( var->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_INPUTOUTPUT.c_str() ) == 0)) 
				{
					CM_TRACE_DEBUG("Exporting Variable Name[" << var->getName() << "] Value[" << var->getValue() << "]")
					workflow->addAttribute2Process(*var);
				}
			}

			if ( iWorkflowLevel == 0 )
			{
				workflow->setFather();
			}
			workflow->setRestart();

			workflow->setBeginTask(sTaskParentProcess);
			workflow->setAnchor ();

			sResult = sReturn;

			//workflow->addEventListeners( this->getEventListeners() );
			WorkflowManager::instance()->executeJob( workflow, true );
		}
		
	}

	return FE_OK;
}
