#include "CommonDefines.h"

#include "BaseTask.h"
using namespace WorkflowEngine::Criteria::BasicTask;

#include "BaseAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Action;

#include "DBException.h"
#include "DataBaseHelper.h"
using namespace DataManager::DataBase;

#include "Report.h"
#include "Reports.h"
using namespace DataManager::Panorama::WorkflowProcesses;

BaseTask::BaseTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task )
{
	CM_CODEBLOCK(BaseTask)

	assert(process != NULL);
	assert(task != NULL);

	_process = process; 
    _task = task;

	_task->setProcessId( _process->getProcessId());

    _action = NULL;
}

BaseTask::~BaseTask()
{
	CM_CODEBLOCK(~BaseTask)

    if ( _action != NULL )
	{
        delete _action;
	}
}

int BaseTask::execute()
{
    CM_CODEBLOCK(execute)

	_task->setRunning();

	this->writeReport(TaskStatus(EXECUTED));

 	return FE_OK;
}

int BaseTask::delegate()
{
    return FE_OK;
}

int BaseTask::assign()
{
    CM_CODEBLOCK(assign)

	_task->setOwner ("CRITERIA");

	_task->setQueued();

	this->writeReport(TaskStatus(ASSIGNED));

	return FE_OK;
}

void BaseTask::autoAssignTo()
{
	CM_CODEBLOCK(autoAssignTo)

	WorkflowRelevantData::Attribute* attribute = this->getAttribute(XMLActivity::MARKER_ASSIGN_TO.c_str());

	if ( attribute != NULL )
	{
		//modify by mfarina on 22/05/2005 for bug 1
		String sValue = this->getEvaluatedParameter ( attribute->getValue() , attribute->getType() );
		//String sValue = this->getEvaluatedParameter ( attribute->getValue()  );
		

		_task->setOwner(sValue);
		_task->setRunning();
	}
}

int BaseTask::release()
{
    CM_CODEBLOCK(release)

	_task->setCreated();

	return FE_OK;
}

int BaseTask::complete(int feErr)
{
    CM_CODEBLOCK(complete)

	appendVarContext();

	switch (feErr ) 
	{
	case FE_OK:
		_task->setCompleted();
		break;
	case FE_TASK_SUBFLOW_STOPPED_BY_TASK:
		//_task->setRunning();
		break;
	default:
		_task->setError ();
		break;
	}

	this->writeReport(TaskStatus(COMPLETED));

    return feErr;
}

int BaseTask::fix()
{
    if ( _action != NULL )
	{
        return _action->fix();
	}

    return FE_OK;
}

void BaseTask::appendVarContext()
{
	CM_CODEBLOCK(appendVarContext)

	WorkflowRelevantData::Attributes& vProcessVars = _process->getAttributes();
	WorkflowRelevantData::Attributes& vTaskVars = _task->getAttributes();

	if ( _action != NULL )	//action is not BeginTask or EndTask.
	{
		WorkflowRelevantData::Attributes& vContextVars = _action->getVarsContext();
		unsigned int uiSize = vContextVars.size();

		for ( unsigned int i =0; i<uiSize; i++)
		{
			WorkflowRelevantData::Attribute* variable = (WorkflowRelevantData::Attribute*)vContextVars.at(i);
			
			//CM_TRACE_DEBUG("Adding Variable[" << variable->getName() << "] Value[" << variable->getValue() << "] to process")
			//vProcessVars.add(*variable);

			WorkflowRelevantData::Attribute* varTask = vTaskVars.get(variable->getName().c_str());
			if ( varTask != NULL) 
			{
				CM_TRACE_DEBUG("Setting Variable[" << variable->getName() << "] Value[" << variable->getValue() << "] to task")
				varTask->setValue (variable->getValue());	
			}
			else
			{
				WorkflowRelevantData::Attribute* varProcess= vProcessVars.get(variable->getName().c_str());
				if ( varProcess != NULL) 
				{
					CM_TRACE_DEBUG("Setting Variable[" << variable->getName() << "] Value[" << variable->getValue() << "] to task")
					varProcess->setValue (variable->getValue());	
				}
				else if ( strcmp(variable->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_TASK.c_str() ) == 0) 
				{
					varTask=vTaskVars.add(variable->getName().c_str(), WorkflowRelevantData::XMLAttribute::NUMBER_TYPE.c_str());
					//TODO: Sostituire con metodi sulla classe XMLAttribute
					varTask->setDirection ( WorkflowRelevantData::XMLAttribute::DIRECTION_CONSTANT);
					varTask->setValue (variable->getValue());
				}
				else
				{
					varTask = vProcessVars.add (variable->getName().c_str(), WorkflowRelevantData::XMLAttribute::NUMBER_TYPE.c_str());
					varTask->setDirection ( WorkflowRelevantData::XMLAttribute::DIRECTION_INPUTOUTPUT);
					varTask->setValue (variable->getValue());
				}
			}
		}
	}
	
	unsigned int uiSize = vTaskVars.size();
	for ( unsigned int i =0; i<uiSize; i++)
	{
		WorkflowRelevantData::Attribute* variable = (WorkflowRelevantData::Attribute*)vTaskVars.at(i);

		if ( ( strcmp(variable->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_OUTPUT.c_str() ) == 0) || 
			 ( strcmp(variable->getDirection().c_str(), WorkflowRelevantData::XMLAttribute::DIRECTION_INPUTOUTPUT.c_str()) == 0) )
		{
			vProcessVars.add(*variable);
		}
	}
	
	vProcessVars.add(_varContext);
}

void BaseTask::writeReport(TaskStatus eStatus)
{
	CM_CODEBLOCK(BaseTask::writeReport)

	try
	{
		WorkflowProcesses::BehaviourBase* behaviour = NULL;
		
		switch ( eStatus )
		{
		case EXECUTED:
			behaviour = _task->getBehaviour().getBehaviourExecution();
			break;

		case DELEGATED:
		case RELEASED:
			break;

		case ASSIGNED:
			behaviour = _task->getBehaviour().getBehaviourStart();
			break;

		case COMPLETED:
			behaviour = _task->getBehaviour().getBehaviourFinish();
			break;
		}
		
		Report& report = behaviour->getReport();

		//add by mfarina on 09/07/2005 to avoid compile and write over DB a empty report.
		if ( strcmp(report.getValue().c_str(), "" ) )
		{
			this->compileReport(report);
			report.setProcessId ( _process->getProcessId() );
			try
			{
				DataBaseHelper::instance()->insertReport(report);
			}
			catch ( DataManager::DataBase::DBException& err)
			{
				string sErr  = err.getMessage ();
			}
			Reports& reports = _process->getReports();
			reports.addReport (report);
		}
	}
	catch ( DBException& dbErr)
	{
		CM_TRACE_ERROR("Error saving Report[" << dbErr.getMessage() << "]")
	}
}

void BaseTask::compileReport(WorkflowProcesses::Report& report)
{
    CM_CODEBLOCK(compileReport)

	String sTemplate = report.getValue();

    CM_TRACE_CODEPATH( "Report Template: [" << sTemplate.c_str() << "]")

	StringBuffer sReport;
	
	int iPosTagB;
	int iPosTagE=0;
	int iPosCur=0;

	String sTagName;
	
	while ( (iPosTagB=sTemplate.find("[", iPosCur )) != -1 )
	{
		//-1 avoids to get '#' char
		sReport.append ( sTemplate.substr( iPosCur, iPosTagB - iPosCur) );

		if ( ( iPosTagE = sTemplate.find("]", iPosTagB + 1 ) ) != -1 )
        
        {
            //-1 avoids to get ']' char
            sTagName = sTemplate.substr(iPosTagB + 1, ( iPosTagE - iPosTagB - 1) );
            
			if ( strcmp ( sTagName.c_str(), WorkflowProcesses::XMLReport::DATE_TIME_VARIABLE.c_str() ) == 0 )
				sReport.append(DateTime::getCurrentDateTime().toString());

			else if ( strcmp( sTagName.c_str(), WorkflowProcesses::XMLReport::PROCESS_ID_VARIABLE.c_str() ) == 0 )
			    sReport.append(_process->getProcessId());

			else if ( strcmp(sTagName.c_str(), WorkflowProcesses::XMLReport::WORKFLOW_NAME_VARIABLE.c_str() ) == 0 )
			    sReport.append(_process->getName());

			else if ( strcmp ( sTagName.c_str(), WorkflowProcesses::XMLReport::ACTIVITY_NAME_VARIABLE.c_str() ) == 0 )
			    sReport.append(_task->getActivityName());

            //TODO: to define
            //else if ( sTagName == REPORT_TAG_TASK_ATTRIBUTES )
			//    strReport << "Instruction"; 

            else //Tag Not Defined. Search for Attribute
            {
                CM_TRACE_CODEPATH( "Tag :[" << sTagName.c_str() << "] not defined.")

				WorkflowRelevantData::Attributes& vVars = _task->getAttributes();
                WorkflowRelevantData::Attribute* var = vVars.get (sTagName.c_str());
                if ( var != NULL )
                {
                    CM_TRACE_CODEPATH( "Adding Attrbiute[" << var->getValue() << "]")
                    sReport.append(var->getValue());
                }
                else
                {
					WorkflowRelevantData::Attributes& vVars2 = _process->getAttributes();
					WorkflowRelevantData::Attribute* var2 = vVars2.get(sTagName.c_str());
                    if ( var2 != NULL )
                    {
                        CM_TRACE_CODEBLOCK( "Adding Attrbiute[" << var2->getValue() << "]")   
                        sReport.append(var2->getValue());
                    }
                    else
                    {
                        CM_TRACE_CODEBLOCK( "Attribute not found.")
                        sReport.append(sTagName);
                    }
                }

            }

		    iPosCur = iPosTagE+1;

            if ( iPosCur == sTemplate.length () ) 
                break;
        }
        else
        {
            iPosCur=++iPosTagB;
        }
	} // while

    if ( iPosCur <= sTemplate.length () ) 
	{
	    sReport.append(sTemplate.substr(iPosCur));
	}

	report.setDateTime( DateTime::getCurrentDateTime().toString() );
	report.setValue(sReport.getData());
}
//modify by mfarina on 22/05/2005 for bug 1
String BaseTask::getEvaluatedParameter(const String& sParamValue, const String& sType)
{
    CM_CODEBLOCK(getEvaluatedParameter)

    CM_TRACE_CODEPATH( "Parameter: [" << sParamValue.c_str() << "]")

	ostrstream strReport;
	
	int iPosTagB;
	int iPosTagE=0;
	int iPosCur=0;

	String sTagName;
	
	while ( (iPosTagB=sParamValue.find("[", iPosCur )) != -1 )
	{
		//-1 avoids to get '#' char
		strReport << sParamValue.substr( iPosCur, iPosTagB - iPosCur);

		if ( ( iPosTagE = sParamValue.find("]", iPosTagB + 1 ) ) != -1 )
        {
			
            //-1 avoids to get ']' char
            sTagName = sParamValue.substr(iPosTagB + 1, ( iPosTagE - iPosTagB - 1) );
			/*
            
            if ( strcmp ( sTagName.c_str(), NaProcessReport::TAG_DATE_TIME.c_str() ) == 0 )
                strReport << pfc::utils::DateTime::getCurrentDateTime().toString();

            else if ( strcmp( sTagName.c_str(), NaProcessReport::TAG_PROCESS_INSTANCE.c_str() ) == 0 )
			    strReport << _process->getProcessID();

            else if ( strcmp(sTagName.c_str(), NaProcessReport::TAG_PROCESS_NAME.c_str() ) == 0 )
			    strReport << _process->getName();

            else if ( strcmp ( sTagName.c_str(), NaProcessReport::TAG_TASK_NAME.c_str() ) == 0 )
			    strReport << _task->getName();

            //TODO: to define
            //else if ( sTagName == REPORT_TAG_TASK_ATTRIBUTES )
			//    strReport << "Instruction"; 
			*/
            //else //Tag Not Defined. Search for Attribute
            //{
                WorkflowRelevantData::Attribute* var= getAttribute(sTagName);
                if ( var != NULL )
                {
					CM_TRACE_CODEPATH( "Adding Attribute[" << var->getValue() << "]")
                    strReport << var->getValue();
                }
                else
                {
					//modify by mfarina on 22/05/2005 for bug 1
					try
					{
						strReport << DataBaseHelper::instance()->GetValueFromDataType(sType, sTagName);
					}
					catch ( DBException& dbErr )
					{
						CM_TRACE_CODEBLOCK( "Attribute not found. Err[" << dbErr.getMessage() << "]" )
						strReport << sTagName;
					}
                }
            //}

		    iPosCur = iPosTagE+1;

            if ( iPosCur == sParamValue.length () ) 
                break;
        }
        else
        {
            iPosCur=++iPosTagB;
        }
	} // while

    if ( iPosCur > sParamValue.length () ) 
	{
        strReport << ends;
	}
    else
	{
	    strReport << sParamValue.substr(iPosCur) << ends;
	}

    return strReport.str();
}

WorkflowRelevantData::Attribute* BaseTask::getAttribute( const String& name)
{
	String s= name;
	WorkflowRelevantData::Attribute* var = _task->getAttributes().get(s.c_str());
	if ( var == NULL )
	{
		var = _process->getAttributes().get(s.c_str());
	}

	return var;
}
