#ifndef __BASE_TASK_H__
#define __BASE_TASK_H__

#include "WorkflowProcess.h"
#include "Activity.h"
#include "Attributes.h"
#include "Behaviour.h"
#include "Script.h"
using namespace DataManager::Panorama;

#include "BaseAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Action;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			/**
			* La classe base della struttura ereditaria che implementa le funzionalit? 
			* atomiche dell'engine:
			*
			* PRIMITIVE TYPE : consente l'interazione con il sistema operativo
			* ADAPTERPRIMITIVE TYPE : consente la comunicazione socket con applicazioni esterne
			* PROCESS TYPE e SUBFLOW EXIT : funzionalit?per gestire un processo dipendente da un processo padre 
			* CONDITION TYPE e ITERATION TYPE : intoducono le funzionalit?per la gestione di pattern di workflow
			* SPECIAL TYPE e SPECIAL TYPE CATCHER : intoducono le funzionalit?per la gestione di pattern di workflow multi branch
			* XML TYPE : trasformazione XSLT
			* EMAIL TYPE : Supporto messaggistica
			*
			* Il metodo execute che implementa la classe derivata ne caratterizza il comportamento 
			* attraverso l'utlizzo degli oggetti action:
			*
			* @code
			*
			*    int nActionID = _task->getAction().getType();
			*	switch ( nActionID ) 
			*	{
			*   case Action::ACTION_TYPE:
			*        {
			*			CM_TRACE_CODEPATH( "Executing Action type.")
			*            Action = new ActionType( _process, _task );
			*        }
			*		break;
			*	default:
			*        {
			*			CM_TRACE_CODEPATH( "ActionType Error.")
			*		    return FE_TASK_ACTIONTYPE_ERROR;
			*       }
			*        break;
			*	}
			*
			* @endcode
			*/
			class BaseTask
			{
				public:
					BaseTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task );
				
					virtual ~BaseTask();

    				virtual int execute();

					virtual int delegate();

					virtual int assign();

					virtual int release();

					virtual int complete(int feErr);

					virtual int fix();

					void autoAssignTo();

				protected:

					enum TaskStatus
					{
						EXECUTED,
						DELEGATED,
						ASSIGNED,
						RELEASED,
						COMPLETED
					} ;

					WorkflowProcesses::Activity* _task;
					WorkflowProcesses::WorkflowProcess* _process;
					BaseAction* _action;

					void appendVarContext();
					WorkflowRelevantData::Attributes _varContext;

					void writeReport(TaskStatus);
					void compileReport(WorkflowProcesses::Report&);

					WorkflowRelevantData::Attribute* getAttribute( const String& name);
					String getEvaluatedParameter(const String& sParamValue, const String& sType);
			};
		}
	}
}

#endif //__BASE_TASK_H__