#include "CommonDefines.h"

#include "Workflow.h"
#include "WorkFlowThread.h"
#include "WorkflowException.h"
#include "WorkflowReport.h"
using namespace WorkflowEngine::Criteria::Core;

#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "IDataType.h"
#include "NaturalType.h"
using namespace WorkflowEngine;

#include "WorkflowProcess.h"
#include "BehaviourExecution.h"
#include "Transition.h"
#include "Activity.h"
#include "Attribute.h"
#include "DataTypes.h"
#include "DataType.h"
using namespace DataManager::Panorama;

//Task Class
#include "BaseTask.h"
using namespace WorkflowEngine::Criteria::BasicTask;

#include "ProcessTask.h"
#include "SubFlowExitTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Process;

#include "PrimitiveTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Primitive;

#include "LoopTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Iteration;

#include "ConditionTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Condition;

#include "ApplicationFunctionTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Application;

#include "XMLTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::XML;

#include "EventTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Event;

//Event
#include "StartedWorkflowEvent.h"
#include "RestartedWorkflowEvent.h"
#include "EndWorkflowEvent.h"
#include "ErrorWorkflowEvent.h"
#include "ManualWorkflowEvent.h"
using namespace WorkflowEngine::Criteria::Event::WorkflowEvent;

#include "OccurredEvent.h"
using namespace DataManager::Panorama::WorkflowEvents;

#include "EventsManager.h"
using namespace WorkflowEngine;

Workflow::Workflow() : EventMaker("Workflow")
{
    CM_CODEBLOCK(Workflow)

    this->init();
}

Workflow::Workflow( WorkflowProcesses::WorkflowProcess* pInstance ) : EventMaker("Workflow")
{
    CM_CODEBLOCK(Workflow_by_ProcessInstance_ptr)

    assert( pInstance != NULL);
	if ( pInstance == NULL)
	{
		CM_TRACE_ERROR("ProcessInstance pointer is null")
        throw EngineException(FE_PROCESS_I_ID_NOTVALID, "");
	}

    this->init();

	process = pInstance;
}

Workflow::Workflow( const char* processID ) : EventMaker("Workflow")
{
    CM_CODEBLOCK(Workflow_by_ProcessInstance_id)

	if ( strcmp(processID,"") == 0)
	{
		CM_TRACE_ERROR("ProcessInstance pointer is null")
        throw EngineException(FE_PROCESS_I_ID_NOTVALID, "");
	}

    this->init();

	//TODO: Definire un eccezione nella classe DataBase.
	/*try
	{*/
        CM_TRACE_CODEPATH( "Loading ProcessInstance ID [" << processID << "]")

		process = DataBaseHelper::instance()->getProcessInstance(processID);

		if ( this->parentProcess.compare("") )
		{
			process->setParentProcess(this->parentProcess.c_str());
		}
	//}
    /*
	catch ( DynamicModelException& dme )
	{
        CM_TRACE_ERROR("Impossible to load ProcessInstance ID [" << processID << "]. Err [" << dme.getMessage() << "]")

		switch ( dme.getErrorCode() )
		{
			case SELECT_NEVER_ONE_ROW:
                throw EngineException(FE_PROCESS_I_NOTFOUND, dme.getMessage().c_str() );

			default:
                throw EngineException(FE_DB_ERROR, dme.getMessage().c_str());
		}
	}
	*/
}

Workflow::Workflow( WorkflowProcesses::WorkflowProcess* pInstance, WorkflowProcesses::Activity* task) : EventMaker("Workflow")
{
    CM_CODEBLOCK(Workflow_C)

    assert( pInstance != NULL);
	assert(task != NULL);

    this->init();

	process = pInstance;

	this->setBeginTask ( task->getActivityName());
}

Workflow::~Workflow()
{
    CM_CODEBLOCK(~Workflow)
}

Workflow* Workflow::operator=( Workflow* w )
{
    CM_CODEBLOCK(WorkFlow oper=)

    Workflow* wf = new Workflow();
    wf->process = w->process;
    return wf;
}
void Workflow::init()
{
    CM_CODEBLOCK(init)

    status = Workflow::RUNNING;

	bError = true;
    bFather = false;
    bRestart = false;
    sBeginTask = "";
	sCode ="";
    iRequestID = 0;
    iLevel = 0;
	//eliminata per modifica DataBase1.2 loading/saving process
//	bWorkflowChild = false;
	parentProcess = "";
	bAnchor = false;

	eventParameters.clear();

	//eliminata per modifica DataBase1.2 loading/saving process
	//bWorkflowStoppedBySplitTask = false;
}

//Any Workflow::starting()
int Workflow::starting()
{
    CM_CODEBLOCK(starting)

	/*
		- throws Restarted/Started Event
		- searchs the beginning task. (error task if workflow is restarting.)
	*/

	/*
		throwing Started/Restarted Workflow Event.
	*/
    if ( bRestart )
    {
        CM_TRACE_CODEPATH("WorkFlow is coming to restart.")
		//this->throwEvent( RestartedWorkflowEvent(this) );     //ztg delete
		//this->throwEvent( (RestartedWorkflowEvent*)(this) );

    }
    else
    {
        CM_TRACE_CODEPATH("WorkFlow is starting now.")
		//this->throwEvent( StartedWorkflowEvent(this) );     //ztg delete
		//this->throwEvent( (StartedWorkflowEvent*)(this) );
     }

	//TODO: The Error Task searching is only for workflow restarting.
	/*
		searching for taskEror
	*/
    /*
		Retrieve the first task to execute and set Handled field inside
		error table to true.
	*/
	WorkflowProcesses::Activities& vTasks= process->getActivities();
	//ProcessError* error = process->getError();
	//String sTaskInError = error->getTask();
	//WorkflowProcesses::Activity* taskErr = vTasks.get(sTaskInError);
	WorkflowProcesses::Activity* taskErr=NULL;

	int iErrorCode = FE_OK;
    WorkflowProcesses::Activity* taskFirst = NULL;

	if ( taskErr != NULL )
	{
        CM_TRACE_DEBUG("Unmanaged Error found. Task Err[" << taskErr->getActivityName() << "]" )

		/*
			bError is used only for sub-workflow.
			Workflow restarting policie allows to restart a sub-workflow from
			begin task. Thus, if a sub-workflow error task is setted for restarting
			from a specific task the bError flag allows to avoids it.
		*/

		//TODO:
		/*
			The workflow restart from beginning task if's necessary to delete
			sub-workflows error from table. In fact, if error occurred while
			workflow restarting the sub-workflows errors are incosistent.
			Another way is to store bError flag.
		*/
        /*
		if ( bError )
		{
            CM_TRACE_CODEPATH( "Error to manage.")

			switch ( taskErr->getErrorAction() )
			{
			case ProcessError::RESTART_TASK:
                {
					CM_TRACE_CODEPATH( "Restart Workflow from the Error Task.")

                    //Task to restart is TaskErr.
				    taskFirst = taskErr;

                    //Setting it to true.
					//The sub-workflows are enabled to manage their errors.
				    bError = true;
                }
				break;
            case ProcessError::RESTART_PROCESS:
                {
					CM_TRACE_CODEPATH( "Restart from the beginning")

				    taskFirst = NULL;

					//Setting it to false.
					//The sub-workflows are not enabled to manage their errors.
				    bError = false;
                }
				break;
            case ProcessError::RESTART_ALL_CHAIN:
                {
					CM_TRACE_CODEPATH( "Restart All Chain")

				    //TODO: i don't know
					taskFirst = NULL;
					bError = false;
                }
				break;
			default:
                {
					CM_TRACE_ERROR( "Unknow error action.")

				    //TODO: Manage error
                }
				break;
			}
		}
		else	//( bError )
		{
            CM_TRACE_DEBUG( "Error is ignored.")
		}
		*/
	}


    /*
		If there are not unmanaged error workflow restart execution from
		beginning task or task select from user.
	*/
	WorkflowProcesses::Activity* taskStopped=NULL;

	if ( taskFirst == NULL )
	{
		if ( sBeginTask.length() == 0 )
		{
			taskFirst = vTasks.getStartActivity();
		}
		else
		{
			taskFirst = vTasks.get(sBeginTask);

			/*
			taskStopped = vTasks.getStoppedTask();
			assert(taskStopped != NULL);
			if ( taskStopped != NULL )
			{
				taskStopped->setCompleted();
			}
			else
			{
				//TODO: throws Error

			}
			*/
		}
	}

	/*
		taskfirst equal to NULL.It's an error.
	*/
	if ( taskFirst == NULL )
	{
		CM_TRACE_ERROR("Starting Task not found.")
		iErrorCode = FE_PROCESS_I_TASK_BEGIN_NOTFOUND;
	}
	else
	{
		process->setRunning();

        CM_TRACE_CODEPATH( "Adding Runtime Attributes.")

		/*
			Adding process ID and level to Process.
			If attribute with same name exist they'll be overwrite.
		*/
		addAttribute2Process(WorkflowProcesses::XMLReport::PROCESS_ID_VARIABLE.c_str(), process->getProcessId());
		addAttribute2Process(WorkflowProcesses::XMLReport::WORKFLOW_LEVEL_VARIABLE.c_str(), iLevel);

		//Starting
		CM_TRACE_DEBUG( "Starting Workflow from task[" << taskFirst->getActivityName() << "]")

		iErrorCode = explore( taskFirst);

		//salvare gli attributi di processo solo una volta.
		try
		{
			DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes = process->getAttributes();
			vAttributes.setProcessId ( process->getProcessId() );
			DataBaseHelper::instance()->updateAttributes(process->getAttributes());
		}
		catch ( DBException dbErr)
		{
			CM_TRACE_ERROR("Impossible to update process attributes.[" << dbErr.getMessage() << "]")
		}
		catch ( ... )
		{
			CM_TRACE_ERROR("Impossible to update process attributes.[Unknow Error]")
		}

	} //( taskFirst == NULL )


	if ( iErrorCode == FE_OK )
	{
        if ( isStoppedByTask() )
        {
            CM_TRACE_CODEPATH( "Setting Process in Running Status.")
			process->setRunning();

			if ( bFather )
			{
				//throwEvent ( ManualWorkflowEvent ( this ) );     //ztg delete
				//throwEvent ( (ManualWorkflowEvent*)(this) );
			}
        }
        else
        {
			/*
			il completed del processo viene assegnato esclusivamente quando si incontra il task End or Exit.
			if ( this->bWorkflowChild )
			{
				CM_TRACE_CODEPATH( "workflow child completed.")
			}
			else if ( this->bWorkflowStoppedBySplitTask )
			{
				CM_TRACE_CODEPATH( "workflow completed.FlowControl passed to workflow child")
			}
			else
			{
				CM_TRACE_CODEPATH( "Setting Process in Completed Status.")
				process->setCompleted();
			*/
				if ( bFather )
				{
					//throwEvent ( EndWorkflowEvent ( this ) );     //ztg delete
					//throwEvent ( (EndWorkflowEvent*)(this) );

				}
			/*}
			*/
        }
	}
	else
	{
        CM_TRACE_CODEPATH( "Setting Process in Error Status.")
		process->setError();

		if ( bFather )
		{
			//throwEvent ( ErrorWorkflowEvent ( this ) );
					//throwEvent ( EndWorkflowEvent ( this ) );     //ztg delete
					//throwEvent ( (EndWorkflowEvent*)(this) );

		}
	}

	/*
	*/
	//TODO:
	/*
	//eliminata per modifica DataBase1.2 loading/saving process
	if ( !bWorkflowChild && !bWorkflowStoppedBySplitTask )
	{
	*/

		DataBaseHelper::instance()->updateProcess(process);

		//salvo gli attributi prima di cancellare il processo in quanto potrebbero essere passati ad
		//un processo chiamante.
		if ( iLevel > 0 )
		{
			vAttributes.add(process->getAttributes());
		}
		DataBaseHelper::instance()->releaseProcess(process);
	//}
	//return (void*)iErrorCode;
	return iErrorCode;
}

//Any Workflow::stopping()
int Workflow::stopping()
{
	//return (void*)NULL;
	return 0;
}

//Any Workflow::suspending()
int Workflow::suspending()
{
	//return (void*)NULL;
	return 0;
}

void Workflow::setNoErrorManaging()
{
    bError = false;
}

void Workflow::setFather()
{
    bFather = true;
}

void Workflow::setRestart()
{
    bRestart = true;
}

void Workflow::setBeginTask( String _status )
{
    sBeginTask = _status;
}

void Workflow::setBeginTask( String _status, string _code )
{
    sBeginTask = _status;
	sCode = _code;
}

void Workflow::setBeginTask(string _status, Common::FormalParameters& parameters)
{
	sBeginTask = _status;

	eventParameters.clear();
	eventParameters.addParameter(parameters);
}

void Workflow::setLevel( int level )
{
    iLevel= level;
}

int Workflow::getLevel(  )
{
    return iLevel;
}

WorkflowProcesses::WorkflowProcess* Workflow::getProcess()
{
    //ztg add
    //if (process=="") process=NULL;

    return process;
}

bool Workflow::isStoppedByTask()
{
    if ( status == STOPPED_BY_MANUALTASK )
	{
        return true;
	}
    else
	{
        return false;
	}
}

int Workflow::explore(WorkflowProcesses::Activity* task)
{
    CM_CODEBLOCK(Workflow::explore)

	assert(task != NULL);

	BaseTask* taskAction = NULL;

	int iErrorCode = FE_OK;
	int iErrorCodeType = FE_OK;

	bool bNotEnd=true;
	bool bNotStopped=true;

	switch ( task->getType() )
	{
	case WorkflowProcesses::Activity::START:
		{
			taskAction = new BaseTask(process, task);
		}
		break;

	case WorkflowProcesses::Activity::SUBFLOW:
		{
			taskAction = new ProcessTask(process, task, iLevel);
		}
		break;

	case WorkflowProcesses::Activity::API:
		{
			taskAction = new PrimitiveTask(process, task);
		}
		break;

	case WorkflowProcesses::Activity::ITERATION:
		{
			taskAction = new LoopTask(process, task);
		}
		break;

	case WorkflowProcesses::Activity::CONDITION:
		{
			taskAction = new ConditionTask(process, task);
		}
		break;

	case WorkflowProcesses::Activity::APPLICATION:
		{
			taskAction = new ApplicationFunctionTask(process,task);
		}
		break;

	case WorkflowProcesses::Activity::XML:
		{
			taskAction  = new XMLTask(process, task);
		}
		break;

	case WorkflowProcesses::Activity::THROWER:
		{
			taskAction = new ConditionTask(process, task);
		}
		break;

	case WorkflowProcesses::Activity::CATCHER:
		{
			taskAction = new BaseTask(process, task);
		}
		break;
	case WorkflowProcesses::Activity::END:
	case WorkflowProcesses::Activity::EXIT:
		{
			taskAction = new SubFlowExitTask(process,task,iLevel);
		}
		break;
	case WorkflowProcesses::Activity::EVENT:
		{
			taskAction = new EventTask(process, task, eventParameters);
		}
		break;

	default:
		{
			taskAction = new BaseTask(process, task);

			CM_TRACE_WARNING("task error. Task type not exists.")
			iErrorCodeType =FE_TASK_TYPE_ERROR;
		}
		break;
	}

	String sOldTask = task->getStatus();

	CM_TRACE_CODEPATH("Assigning task[" << task->getActivityName() << "]")
	iErrorCode = taskAction->assign();
	if ( iErrorCode != FE_OK)
	{
		CM_TRACE_WARNING("Impossible to assign task[" << task->getActivityName() << "]")
		return iErrorCode;
	}

	if ( iErrorCodeType == FE_TASK_TYPE_NOTMANAGED || iErrorCodeType == FE_TASK_TYPE_ERROR )
	{
		CM_TRACE_WARNING("Impossible to perform action. ErrorCodeType occurred.")
		return iErrorCodeType;
	}

	//bAnchor indica che il workflow ?stato instanziato dal task exit di un sottoprocesso.
	if ( bAnchor)
	{
		CM_TRACE_CODEPATH( "Task not executed because is an anchor.")
		bAnchor = false;

		iErrorCode = FE_OK;
	}
	//Se sCode ?valorizzato indica che il workflow ?stato istanziato dall'esterno grazie
	//alla WAPI che completa una task manuale e ne assegna il risultato.
	else if ( sCode != "" )
	{
		CM_TRACE_CODEPATH("Task not executed beacuse is a manual task invoked by WAPI.ResultCode[" << sCode << "]")

		//setting result.
		WorkflowDataTypes::DataType datatype;
		datatype.setKey (task->getBehaviour().getDataType());

		try
		{
			DataBaseHelper::instance()->getDataType(datatype);
		}
		catch ( DBException& dbErr )
		{
			CM_TRACE_ERROR("Impossible to retrieve DataType[" << datatype.getKey() << "]. Err[" << dbErr.getMessage() << "]")
			iErrorCode = FE_RESULTCODE_NOTFOUND;
		}

		WorkflowDataTypes::DataTypeValue* code = datatype.getDataTypeValues().getValue(sCode);
		if ( code == NULL )
		{
			CM_TRACE_WARNING("Code[" << sCode << "] not found inside DataTypes. Impossible to perform workflow exploration")
			iErrorCode = FE_RESULTCODE_NOTFOUND;
			bNotStopped = false;
		}
		else
		{
			CM_TRACE_DEBUG("Assign Result Value[" << code->getValue() << "]")
			task->setResult(code->getValue());
		}

		sCode = "";
	}
	else if ( eventParameters.size() > 0)
	{
		iErrorCode = taskAction->execute();
		eventParameters.clear();
	}
	//ztg alter
	//else if ( (sOldTask == WorkflowProcesses::XMLActivity::CREATED_STATUS) || task->isToRexecute() )
    else if ( ((sOldTask == WorkflowProcesses::XMLActivity::CREATED_STATUS) || task->isToRexecute() ) && (bRestart == false) )
	{
		iErrorCode = taskAction->execute();

		String sScriptType = task->getBehaviour().getScriptType();
		switch ( iErrorCode )
		{
		case FE_OK:
			//super pezza

			if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::SUBFLOW_SPECIAL_TYPE.c_str()) == 0 )
			{
				bNotStopped = false;
				if ( process->getParentProcess() > 0 )
				{
					process->setExit2Manage();
				}
			}
			else
			{
				if ( !(task->isAutomatic()) )
				{
					task->setManual();

					//TODO: introdurre l'activity manual
					taskAction->autoAssignTo();

					setStoppedByTask();
					bNotStopped = false;

					if ( process->getParentProcess() > 0 )
					{
						process->setExit2Manage();
					}
				}
			}
			break;

		case FE_TASK_SUBFLOW_STOPPED_BY_TASK:
			setStoppedByTask();
			bNotStopped = false;

			iErrorCode = FE_OK;

			if ( process->getParentProcess() > 0 )
			{
				process->setExit2Manage();
			}
			break;

		case FE_TASK_STOPPED_BY_WAINTING_EVENT:
			setStoppedByTask();
			bNotStopped = false;

			iErrorCode = FE_OK;

			//add by mfarina 02/10/2004 for resolving Giancarmine malf.
			if ( process->getParentProcess() > 0 )
			{
				process->setExit2Manage();
			}

			task->setWaitingForEvent();
			break;
		}
	}
	else
	{
		iErrorCode = FE_OK;
		CM_TRACE_DEBUG("Task not Executed because it's already executed and no re-exec type. Name[" << task->getActivityName() << "]" )
	}


	if ( bNotStopped )
	{
		iErrorCode = taskAction->complete(iErrorCode );
	}

	try
	{
		DataBaseHelper::instance()->updateActivity(task, false);
	}
	catch ( DBException dbErr)
	{
		CM_TRACE_ERROR("Impossible to update task.[" << dbErr.getMessage() << "]")
	}
	catch ( ... )
	{
		CM_TRACE_ERROR("Impossible to update task.[Unknow Error]")
	}

	try
	{
		DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes = task->getAttributes();
		vAttributes.setActivityId ( task->getActivityId().c_str() );
		vAttributes.setProcessId ( task->getProcessId() );
		DataBaseHelper::instance()->updateAttributes(task->getAttributes());
	}
	catch ( DBException dbErr)
	{
		CM_TRACE_ERROR("Impossible to update task attributes.[" << dbErr.getMessage() << "]")
	}
	catch ( ... )
	{
		CM_TRACE_ERROR("Impossible to update task attributes.[Unknow Error]")
	}
	bRestart = false;               //ztg add
	//TODO: rendere configurabile
	/*
	try
	{
		DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes = process->getAttributes();
		vAttributes.setProcessId ( task->getProcessId() );
		DataBaseHelper::instance()->updateAttributes(process->getAttributes());
	}
	catch ( DBException dbErr)
	{
		CM_TRACE_ERROR("Impossible to update process attributes.[" << dbErr.getMessage() << "]")
	}
	catch ( ... )
	{
		CM_TRACE_ERROR("Impossible to update process attributes.[Unknow Error]")
	}
	*/

	/*
	try
	{

		WorkflowReport wfReport(process, task);

		WorkflowProcesses::BehaviourExecution* behaviourExecution = task->getBehaviour().getBehaviourExecution();

		Report& report = behaviourExecution->getReport();
		wfReport.compileReport(report);

		report.setProcessId ( process->getProcessId() );
		DataBaseHelper::instance()->insertReport(report);

		Reports& reports = process->getReports();
		reports.addReport (report);
	}
	catch ( DBException& dbErr)
	{
		CM_TRACE_ERROR("Error saving Report[" << dbErr.getMessage() << "]")
	}
	*/

	if ( iErrorCode != FE_OK )
	{
		/*
		ProcessError error;
		error.setTask( task->getName() );
		error.setErrCode( iErrorCode );
		error.setErrString(String( "Errore!") );
		error.setHandled( 0 );
		*/
	}
	else
	{
		/*
			Questo flag indica se l'esecuzione del workflow ?terminata.

			workflow termina:
				Eseguito un task END
				Eseguito un task CATCH(di tipo Sync) in sub-workflow.
				Eseguito un task CATCH(di tipo Only_One) in sub-workflow ed il task ?stato gi?eseguito.
		*/
		if ( task->isEndType() || task->isExitType() )
		{
			CM_TRACE_CODEPATH( "End Task Type executed.")
			iErrorCode = FE_OK;
			bNotEnd = false;
			process->setCompleted();
		}
		//else if ( task->isCatcherType() && (this->bWorkflowChild ) )
		else if ( task->isCatcherType()  )
		{
			int iCatchType = task->getCatchType();
			int iNrExecuted;

			switch ( iCatchType)
			{
			case WorkflowProcesses::Activity::NEVER: //sync
				{
					Mutex::Lock locker(mtxNrExecuted);
					iNrExecuted = task->getNrExecuted();

					CM_TRACE_CODEPATH( "NREXECUTED.Catch Task Type executed.Sync.Process[" << task->getProcessId() << "] Task[" << task->getActivityId() << "]  Nr[" << task->getNrExecuted() << "]")

					iNrExecuted--;
					task->setNrExecuted(iNrExecuted);

					//TODO: Recursive saving....
					DataBaseHelper::instance()->updateActivity(task, false);

					if ( iNrExecuted > 0 )
					{
						bNotEnd=false;
					}
					else
					{
						//eliminata per modifica DataBase1.2 loading/saving process
						bWorkflowChild = false;
						CM_TRACE_DEBUG("Sync")
						//this->wfFather->smphWorkflowChildren.post();

					}
				}

				//

				break;

			case WorkflowProcesses::Activity::EVER:	//no sync
				break;

			case WorkflowProcesses::Activity::ONLY_ONE:
				//task gi?eseguito quindi il primo workflow ?gia passato da questo branch.
				if ( task->isAlreadyExecuted() )
				{
					bNotEnd = false;
				}
				else
				{
					//this->wfFather->smphWorkflowChildren.post();
				}
				break;
			}
		}


		//rem by mfarina on 10/11/2006 for saving process attributes only when process is terminated.
		/*
		if (bNotEnd || bNotStopped)
		{
			try
			{
				DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes = process->getAttributes();
				vAttributes.setProcessId ( task->getProcessId() );
				DataBaseHelper::instance()->updateAttributes(process->getAttributes());
			}
			catch ( DBException dbErr)
			{
				CM_TRACE_ERROR("Impossible to update process attributes.[" << dbErr.getMessage() << "]")
			}
			catch ( ... )
			{
				CM_TRACE_ERROR("Impossible to update process attributes.[Unknow Error]")
			}

		}
		*/



		if ( bNotEnd && bNotStopped )
		{
			manageMessageFlows(task);

			try
			{
				//getNetTask sets Task Re-Exec Field to value Transition Re-Exec Field
				TaskList tasks = getNextTask(task);
				unsigned int uiSize = tasks.size();

				//TODO: or condition??? it should be an and condition.
				if ( (uiSize == 1) || (task->getType() != WorkflowProcesses::Activity::THROWER) )
				{
					/*
					Saving Task in no recursive way.It's necessary to save Task here
					because getNextTask has found a next task and modifies re-exec field task too.
					When the task class will implement the fix method it'll save task record too.
					Obviously if getNextTask makes an error save db is unuseful.
					*/
					iErrorCode=explore(tasks.at(0));
				}
				else
				{
					if ( task->getReferenceActivity() == "" )
					{
						iErrorCode = FE_OK;
					}
					else
					{
						WorkflowProcesses::Activities& tasks = process->getActivities();
						WorkflowProcesses::Activity* refTask = tasks.get(task->getReferenceActivity());
						assert(refTask != NULL);


						int iCatchType = refTask->getCatchType();
						unsigned int iNrExecuted=0;

						switch ( iCatchType)
						{
						case WorkflowProcesses::Activity::NEVER: //sync

							{
								Mutex::Lock locker(mtxNrExecuted);

								iNrExecuted = refTask->getNrExecuted();

								CM_TRACE_CODEPATH("NREXECUTED.Retreive NrExecuted from refereceTask[" << refTask->getActivityName().c_str() <<"] NrExecuted[" << iNrExecuted << "]")
								iNrExecuted+=uiSize;

								if ( task->isAlreadyExecuted() )
								{
									//se il task di split ?gi?stato eseguito significa che uno dei workflow
									//generati dallo split non termina in un task di merge ma nello split
									//per cui nel caso che il reference task sia di tipo sync non ?necessario
									//conteggiare questo workflow.
									iNrExecuted--;
								}

								refTask->setNrExecuted(iNrExecuted);

								CM_TRACE_CODEPATH("NREXECUTED updated[" << iNrExecuted << "]")
								//TODO: Recursive saving....
								DataBaseHelper::instance()->updateActivity(refTask,false);
							}

							break;

						case WorkflowProcesses::Activity::EVER:	//no sync
							break;

						case WorkflowProcesses::Activity::ONLY_ONE:
							//TODO
							break;
						}
					}

					vector<WorkFlowThread*> threadList;
					//workflow->setLevel (iSubLevel);
					for ( unsigned int i=0; i<uiSize; i++)
					{
						DataBaseHelper::instance()->addUsersToProcess(this->process);
						Workflow* wf = new Workflow(this->process, tasks.at(i));

						if ( this->getLevel() > 0 )
						{
							wf->setParentProcess( this->getParentProcess());
							wf->setTaskParentProcess(this->getTaskParentProcess());
							wf->setLevel (this->getLevel());
						}
						//wf->setWorkflowChild(this);
						wf->setWorkflowChild();
						//TODO
						//iWorkFlowRet = (int)workflow->start();
						//wf->addEventListeners( this->getEventListeners() );

						WorkFlowThread* pThread = NULL;
						try
						{
							pThread = WorkflowManager::instance()->executeJob( wf, true );
						}
						catch ( WorkflowException&)
						{
							//TODO
						}
						threadList.push_back(pThread);
					}

					//eliminata per modifica DataBase1.2 loading/saving process
//					bWorkflowStoppedBySplitTask = true;
					iErrorCode = FE_OK;
					//Il seguente codice implementa la sync con il vecchio modo.

					/*std::vector<WorkFlowThread*>::iterator iThread = threadList.begin();
					for (; iThread < threadList.end(); iThread++)
					{
						(*iThread)->join();

						int iWorkFlowRet = (*iThread)->getResult();

						if ( iWorkFlowRet != FE_OK )
						{
							iErrorCode = FE_TASK_TASKACTION_PROCESS_ERROR;
						}
					}

					//this->smphWorkflowChildren.wait();

					threadList.clear();*/

				}
			}

			catch ( EngineException& fee )
			{
				CM_TRACE_ERROR( "Impossible to find the next task. [" << fee.getMessage() << "]")
				iErrorCode = fee.getErrorCode();
			}
		}
	}

    //TODO:
	/*
		Fix methods is used for try-catch enhancement.
		After task execution the workflow searchs next task and explore workflow from it.
		If a execution task failed the fix methods is only way for catching error.

		At the moment no one task implements fix method.
		If the workflow explorer is too expensive you can delete TaskAction object before
		new explore method invocation and return FE_OK without invoking fix method.
	*/
 	if ( taskAction != NULL )
	{
		int iFixErrorCode = taskAction->fix();

		if ( iErrorCode == FE_OK)
		{
			iErrorCode = iFixErrorCode;
		}

		try
		{
			CM_TRACE_CODEPATH( "Deleting TaskAction Object.")
			delete taskAction;
		}
		catch (EngineException& feErr)
		{
			CM_TRACE_ERROR( "A TaskAction destructor has error.[" << feErr.getMessage() << "]")
			iErrorCode = feErr.getErrorCode();
		}
	}


	return iErrorCode;
}


TaskList Workflow::getNextTask( WorkflowProcesses::Activity* task)
{
    CM_CODEBLOCK(Workflow::getNextTask)

	TaskList tasks;

	CM_TRACE_CODEPATH( "Searching next task for Task[" << task->getActivityName() << "] Result [" << task->getResult() << "]")

	WorkflowProcesses::Transitions& trans = process->getTransitions();

	if ( trans.size() == 0)
	{
		CM_TRACE_FATAL("No transitions found inside process.Xml process not-well formed.")
		throw EngineException(FE_TRANSITION_NOTFOUND);
	}

	WorkflowProcesses::Transition* transition;
	WorkflowProcesses::Activity* taskRet = NULL;

	int iFound=0;

	for ( unsigned int i = 0; i<trans.size(); i++ )
	{
		transition = (Transition*)trans.at(i);

		if ( transition->getFromActivity() == task->getActivityName() )
		{
			if ( checkResult(transition, task) )
			{
				CM_TRACE_CODEPATH( "Transition Found. ResultValue[" << transition->getResult() << "]")

				if ( transition->isNoReExecuteWay() )
				{
					CM_TRACE_CODEPATH( "Setting Task not to re-execute.")
                    task->setNotToRexecute();
				}

				CM_TRACE_CODEPATH("Task selected over transition [" << transition->getToActivity() << "]")
				WorkflowProcesses::Activity* taskM = process->getActivities().get(transition->getToActivity() );
                if ( taskM == NULL )
                {
					CM_TRACE_ERROR("Next Task [" << transition->getToActivity() << "] not found!. Activites Nr["<<process->getActivities().size() << "]")
                    throw EngineException(FE_TASK_NOTFOUND);
                }
                else
                {
                    CM_TRACE_CODEPATH( "Next Task found. Name[" << taskM->getActivityName() << "]")
					tasks.push_back (taskM);
					iFound++;
                }
			}
		}
	}

	if ( iFound == 0)
	{
		CM_TRACE_FATAL("No Transitions founds")
		throw EngineException(FE_TRANSITION_NOTFOUND);
	}

	return tasks;
}

//add by mfarina to manage messageflows.
void Workflow::manageMessageFlows( WorkflowProcesses::Activity* task)
{
    CM_CODEBLOCK(Workflow::manageMessageFlows)

	WorkflowProcesses::Messages& messages = process->getMessages();

	if ( messages.size() == 0)
	{
		return;
	}

	WorkflowProcesses::Message* message;
	for ( unsigned int i = 0; i<messages.size(); i++ )
	{
		message = (WorkflowProcesses::Message*)messages.at(i);

		if ( message->getFromActivity() == task->getActivityName() )
		{
			message->setProcessId ( task->getProcessId() );
			DataManager::DataBase::DataBaseHelper::instance()->saveMessageFlow(message);
		}
	}
}


//
bool Workflow::checkResult(Transition* transition, WorkflowProcesses::Activity* task)
{
	CM_CODEBLOCK(Workflow::checkResult)

	assert(task != NULL);

    String sOperator=transition->getOperator();

	if (  strcmp( sOperator.c_str(),  WorkflowProcesses::XMLTransition::ALWAYS_OPERATOR.c_str() ) == 0 )
    {
        return true;
    }

	WorkflowDataTypes::DataType datatype;
	datatype.setKey ( task->getBehaviour().getDataType() );

	CM_TRACE_DEBUG("DataType to search["<< task->getBehaviour().getDataType() << "]")

	try
	{
		DataBaseHelper::instance()->getDataType(datatype);
	}
	catch ( DBException& dbErr)
	{
		CM_TRACE_ERROR("Impossible to retrieve DataType[" << datatype.getKey() << "].Err[" << dbErr.getMessage() << "]")
		return false;
	}

	//add here DataTypeProxy
	Criteria::DataTypes::IDataType* type=new Criteria::DataTypes::NaturalType(&datatype);
    bool bRet = false;

	if (  strcmp( sOperator.c_str(),  WorkflowProcesses::XMLTransition::NOTEQUAL_OPERATOR.c_str() ) == 0 )
    {
        bRet = type->notEqualTo (transition->getResult(), task->getResult() );
	}
	else if (  strcmp( sOperator.c_str(),  WorkflowProcesses::XMLTransition::EQUAL_OPERATOR.c_str() ) == 0 )
    {
        bRet = type->equalTo (transition->getResult(), task->getResult() );
	}
	//add by mfarina on 20/05/2005 for compatibility
	else if (  strcmp( sOperator.c_str(),  "=" ) == 0 )
    {
        bRet = type->equalTo (transition->getResult(), task->getResult() );
	}
	else if (  strcmp( sOperator.c_str(),  WorkflowProcesses::XMLTransition::MORE_THAN_OPERATOR.c_str() ) == 0 )
    {
        bRet = type->greaterThan (transition->getResult(), task->getResult() );
	}
	else if (  strcmp( sOperator.c_str(),  WorkflowProcesses::XMLTransition::LESS_THAN_OPERATOR.c_str() ) == 0 )
    {
        bRet = type->lessThan (transition->getResult(), task->getResult() );
	}
	else if (  strcmp( sOperator.c_str(),  WorkflowProcesses::XMLTransition::MORE_EQUAL_THAN_OPERATOR.c_str() ) == 0 )
    {
        bRet = type->greaterThanEqualTo (transition->getResult(), task->getResult() );
	}
	else if (  strcmp( sOperator.c_str(),  WorkflowProcesses::XMLTransition::LESS_EQUAL_THAN_OPERATOR.c_str() ) == 0 )
    {
        bRet = type->lessThanEqualTo (transition->getResult(), task->getResult() );
    }
	else
	{
		//error to manage
	}

    delete type;

	return bRet;
}

void Workflow::addAttribute2Process(const char* sName, int iValue)
{
	CM_CODEBLOCK(addAttribute2Process)

	//TODO: WorkflowRelevantData::Attribute NUMBER_TYPE to manage
	WorkflowRelevantData::Attribute attribute(sName, WorkflowRelevantData::XMLAttribute::NUMBER_TYPE);
	attribute.setDirection (WorkflowRelevantData::XMLAttribute::DIRECTION_CONSTANT);
	attribute.setValue(iValue);

	WorkflowRelevantData::Attributes& vAttributes = process->getAttributes();
	vAttributes.add(attribute);
}

void Workflow::addAttribute2Process(const char* sName, const char* acValue)
{
	CM_CODEBLOCK(addAttribute2Process)

	//TODO: WorkflowRelevantData::Attribute NUMBER_TYPE to manage
	WorkflowRelevantData::Attribute attribute(sName, WorkflowRelevantData::XMLAttribute::STRING_TYPE);
	attribute.setDirection (WorkflowRelevantData::XMLAttribute::DIRECTION_CONSTANT);
	attribute.setValue(acValue);

	WorkflowRelevantData::Attributes& vAttributes = process->getAttributes();
	vAttributes.add(attribute);
}

void Workflow::addAttribute2Process (WorkflowRelevantData::Attributes& vAttrs2Add)
{
	WorkflowRelevantData::Attributes& vAttributes = process->getAttributes();
	vAttributes.add(vAttrs2Add);
}

void Workflow::addAttribute2Process (WorkflowRelevantData::Attribute& attribute)
{
	WorkflowRelevantData::Attributes& vAttributes = process->getAttributes();
	vAttributes.add(attribute);
}

//TODO: Verificare dove viene usato e valutare se passare una copia.
WorkflowRelevantData::Attributes& Workflow::getAttributes()
{
	return vAttributes;
}

void Workflow::setWorkflowChild()
{
	bWorkflowChild=true;
}

void Workflow::setWorkflowChild(Workflow* wf)
{
	bWorkflowChild=true;
	wfFather = wf;
}

void Workflow::setStatus ( int st)
{
	this->status = (WorkflowStatus)st;
}

int Workflow::getStatus ()
{
	return this->status;
}
