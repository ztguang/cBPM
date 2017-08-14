#include "CommonDefines.h"

#include "ProcessActionAttach.h"
using namespace WorkflowEngine::Criteria::BasicTask::Process::Action;

#include "Workflow.h"
#include "WorkflowException.h"
#include "WorkFlowThread.h"
using namespace WorkflowEngine::Criteria::Core;

#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

ProcessActionAttach::ProcessActionAttach( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, int iLevel, bool _Attach )
    : ProcessAction(process, task, iLevel)
{
	sTaskParentProcess = task->getActivityName();

	bAttach = _Attach;
}

ProcessActionAttach::~ProcessActionAttach()
{
}

int ProcessActionAttach::action(String& sResult)
{
	CM_CODEBLOCK(ProcessActionAttach::action)

    int errCode = evaluateAction();
	if ( errCode != FE_OK)
    {
        return errCode;
    }

	String _ProcessID;
	
	Workflow* workflow=NULL;
	vector<WorkFlowThread*> threadList;
	vector<String>	idList;
	int iWorkFlowRet=0;

	for ( int i=0; (i<iOccurency) && (errCode == FE_OK); i++)
	{
		try
		{
			//_ProcessID = createProcessInstance(connection, sProcessName);
			CM_TRACE_DEBUG("Creating Process from Workflow[" << sProcessName << "]")
			WorkflowProcesses::WorkflowProcess process2Create;
			_ProcessID = DataBaseHelper::instance()->createProcess(sProcessName.c_str(), process2Create, true );
			CM_TRACE_DEBUG("ProcessInstance[" << _ProcessID << "] created.")
			
		}
		catch ( EngineException& feErr)
		{
			//TODO:
			CM_TRACE_ERROR( "Error creating ProcessInstance[" << feErr.getMessage() << "]")
			errCode = FE_TASK_TASKACTION_PROCESS_ERROR;
		}
		
		if ( bSequence )
		{
			workflow = new Workflow(_ProcessID.c_str());

			this->MigrateAttribute (workflow, _privateAttributes, _publicAttributes);

			//Add by mfarina on 05/12/2006
			WorkflowProcesses::WorkflowProcess* process = workflow->getProcess();
			try
			{
				DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes = process->getAttributes();
				vAttributes.setProcessId ( _ProcessID.c_str() );
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

			//TODO: Passare solo quelli gestiti dal processo figlio.
			/*
			for ( unsigned int i=0; i<_privateAttributes.size(); i++)
			{
				WorkflowRelevantData::Attribute* attribute = (WorkflowRelevantData::Attribute*)_privateAttributes.at(i);

				//TODO: insert here only attribute to transfer subflow.
				if ( strcmp( attribute->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_NOTMIGRATE.c_str()) != 0)
				{
					workflow->addAttribute2Process(*attribute);
				}
			}

			//TODO: Passare solo quelli gestiti dal processo figlio.
			for ( unsigned int i=0; i<_publicAttributes.size(); i++)
			{
				WorkflowRelevantData::Attribute* attribute = (WorkflowRelevantData::Attribute*)_publicAttributes.at(i);

				//TODO: insert here only attribute to transfer subflow.
				if ( strcmp( attribute->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_NOTMIGRATE.c_str()) != 0)
				{
					workflow->addAttribute2Process(*attribute);
				}
			}
			*/

			try
			{
				if ( bAttach ) 
				{
					workflow->setParentProcess(this->iPID.c_str());
					workflow->setTaskParentProcess(this->sTaskParentProcess.c_str());
					workflow->setLevel (++iWorkflowLevel);
					CM_TRACE_DEBUG( "Execute Workflow in sequential way.")


					iWorkFlowRet = (int)workflow->start();

					if ( iWorkFlowRet != FE_OK )
					{
						CM_TRACE_CODEPATH( "Error executing Workflow. ContinueSubprocessExec flag setted.")
						errCode = FE_TASK_TASKACTION_PROCESS_ERROR;
					}

					if ( workflow->isStoppedByTask() )
					{
						errCode = FE_TASK_SUBFLOW_STOPPED_BY_TASK;
					}
					//add by mfarina on 09/04/2005.
					//subflow is in attach way and is only one.
					else if (iOccurency = 1) 
					{
						/**/
						CM_TRACE_DEBUG("Exporting Attributes from process child to process father variables context.")
						int iSize = workflow->getAttributes().size();
						for ( int i=0;i<iSize;i++)
						{
							WorkflowRelevantData::Attribute* var = (WorkflowRelevantData::Attribute*)workflow->getAttributes().at(i);

							CM_TRACE_CODEPATH("Attribute[" << var->getName() << "]")
							
							if ( (strcmp( var->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_OUTPUT.c_str()) == 0) ||
								(strcmp( var->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_INPUTOUTPUT.c_str() ) == 0)) 
							{
								CM_TRACE_DEBUG("Exporting Variable Name[" << var->getName() << "] Value[" << var->getValue() << "]")
								_varsContext.add(*var);
							}
						}
					}
	
					delete workflow;
				}
				else
				{
					WorkFlowThread* pThread = WorkflowManager::instance()->executeJob( workflow, true );
				}
			}
			catch (WorkflowException& wfErr)
			{
				CM_TRACE_ERROR("Impossible to execute Job. [" << wfErr.getMessage() << "]")
				errCode = FE_TASK_TASKACTION_PROCESS_ERROR;
			}
		}
		else
		{
			idList.push_back(_ProcessID);
		}
	}
		
	//only if parallel
	for (unsigned int j=0; (j<idList.size() && (errCode == FE_OK) ); j++)
	{
		_ProcessID = idList.at(j);
		workflow = new Workflow(_ProcessID.c_str());

		this->MigrateAttribute (workflow, _privateAttributes, _publicAttributes);

		//TODO: Passare solo quelli gestiti dal processo figlio.
		/*
		for ( unsigned int i=0; i<_privateAttributes.size(); i++)
		{
			WorkflowRelevantData::Attribute* attribute = (WorkflowRelevantData::Attribute*)_privateAttributes.at(i);

			//TODO: insert here only attribute to transfer subflow.
			if ( strcmp( attribute->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_NOTMIGRATE.c_str()) != 0)
			{
				workflow->addAttribute2Process(*attribute);
			}
		}

		//TODO: Passare solo quelli gestiti dal processo figlio.
		for ( unsigned int i=0; i<_publicAttributes.size(); i++)
		{
			WorkflowRelevantData::Attribute* attribute = (WorkflowRelevantData::Attribute*)_publicAttributes.at(i);

			//TODO: insert here only attribute to transfer subflow.
			if ( strcmp( attribute->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_NOTMIGRATE.c_str()) != 0)
			{
				workflow->addAttribute2Process(*attribute);
			}
		}
		*/
		/**/
		

		try 
		{
			if ( bAttach ) 
			{
				workflow->setParentProcess(this->iPID.c_str());
				workflow->setTaskParentProcess(this->sTaskParentProcess.c_str());
				workflow->setLevel (++iWorkflowLevel);
				workflow->setExit2Manage();

				WorkFlowThread* pThread = WorkflowManager::instance()->executeJob( workflow, false );
				threadList.push_back(pThread);
			}
			else
			{
				WorkFlowThread* pThread = WorkflowManager::instance()->executeJob( workflow, true );
			}
		}
		catch (WorkflowException& wfErr)
		{
			CM_TRACE_ERROR("Impossible to execute Job. [" << wfErr.getMessage() << "]")
			errCode = FE_TASK_TASKACTION_PROCESS_ERROR;

		}
	}

		
	if ( threadList.size() > 0 )
	{
		std::vector<WorkFlowThread*>::iterator iThread = threadList.begin();
		for (; iThread < threadList.end(); iThread++)
		{
			try
			{
				if ( (*iThread)->isRunning() )
				{
					(*iThread)->join();
				}

				iWorkFlowRet = (*iThread)->getResult();
			}
			catch ( ... )
			{
				//TODO:
				iWorkFlowRet = 1000;
			}

			if ( iWorkFlowRet != FE_OK )
			{
				errCode = FE_TASK_TASKACTION_PROCESS_ERROR;
			}
		}

		threadList.clear();
	}

	
    sResult = StringUtils::toString(iWorkFlowRet);
	

	return errCode;
}

void ProcessActionAttach::MigrateAttribute (WorkflowEngine::Criteria::Core::Workflow* workflow, WorkflowRelevantData::Attributes& taskAttributes, WorkflowRelevantData::Attributes& processAttribute)
{
	CM_CODEBLOCK(ProcessActionAttach::MigrateAttribute)

	for ( unsigned int i=0; i<taskAttributes.size(); i++)
	{
		WorkflowRelevantData::Attribute* attribute = (WorkflowRelevantData::Attribute*)taskAttributes.at(i);

		//TODO: insert here only attribute to transfer subflow.
		if ( strcmp( attribute->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_NOTMIGRATE.c_str()) != 0)
		{
			CM_TRACE_DEBUG("Migrating from Task Attribute[" << attribute->getName() << "] Value [" << attribute->getValue() << "]")
			workflow->addAttribute2Process(*attribute);
		}
	}

	for ( unsigned int i=0; i<taskAttributes.size(); i++)
	{
		WorkflowRelevantData::Attribute* attributeTest = (WorkflowRelevantData::Attribute*)taskAttributes.at(i);

		CM_TRACE_DEBUG("Task Attribute[" << attributeTest->getName() << "] Value [" << attributeTest->getValue() << "] Direction[" << attributeTest->getDirection() << "]")
	}

	//TODO: Passare solo quelli gestiti dal processo figlio.
	for ( unsigned int i=0; i<processAttribute.size(); i++)
	{
		WorkflowRelevantData::Attribute* attribute = (WorkflowRelevantData::Attribute*)processAttribute.at(i);

		//TODO: insert here only attribute to transfer subflow.
		if ( strcmp( attribute->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_NOTMIGRATE.c_str()) != 0)
		{
			WorkflowRelevantData::Attribute* attrFromTask = taskAttributes.get(attribute->getName().c_str() );

			if ( ( attrFromTask == NULL) || ( strcmp( attrFromTask->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_NOTMIGRATE.c_str()) != 0) )
			{
				CM_TRACE_DEBUG("Migrating from Process Attribute[" << attribute->getName() << "] Value [" << attribute->getValue() << "]")
				workflow->addAttribute2Process(*attribute);

				if ( attrFromTask == NULL ) 
				{
					CM_TRACE_DEBUG("Not found inside Task Attributes")
				}
				else
				{
					CM_TRACE_DEBUG("Attribute found inside Task Attributes. Attribute[" << attrFromTask->getName() << " Value[" << attrFromTask->getValue() << "] Direction [" << attrFromTask->getDirection() << "]")
				}
			}
		}
	}
}