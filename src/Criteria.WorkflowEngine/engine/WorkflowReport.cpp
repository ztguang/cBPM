#include "CommonDefines.h"

#include "WorkflowReport.h"
using namespace WorkflowEngine::Criteria::Core;

#include "bOS.h"
#include "bOSDateTime.h"
using namespace bOS::Utils;

WorkflowReport::WorkflowReport(WorkflowProcesses::WorkflowProcess* _process, WorkflowProcesses::Activity* _task) 
{
	CM_CODEBLOCK(WorkflowReport)

	assert(_process != NULL);
	assert(_task != NULL);
    
    task = _task;
	process = _process;
}

WorkflowReport::~WorkflowReport()
{
	CM_CODEBLOCK(~WorkFlowReport)
}

//TODO: Questo metodo dovrebbe essere unificato con quello di BaseAction
void WorkflowReport::compileReport(WorkflowProcesses::Report& report)
{
    CM_CODEBLOCK(compileReport)

	String sTemplate = report.getValue();

    CM_TRACE_CODEPATH( "Report Template: [" << sTemplate.c_str() << "]")

	StringBuffer sReport;
	
	int iPosTagB;
	int iPosTagE=0;
	unsigned int iPosCur=0;

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
			    sReport.append(process->getProcessId());

			else if ( strcmp(sTagName.c_str(), WorkflowProcesses::XMLReport::WORKFLOW_NAME_VARIABLE.c_str() ) == 0 )
			    sReport.append(process->getName());

			else if ( strcmp ( sTagName.c_str(), WorkflowProcesses::XMLReport::ACTIVITY_NAME_VARIABLE.c_str() ) == 0 )
			    sReport.append(task->getActivityName());

            //TODO: to define
            //else if ( sTagName == REPORT_TAG_TASK_ATTRIBUTES )
			//    strReport << "Instruction"; 

            else //Tag Not Defined. Search for Attribute
            {
                CM_TRACE_CODEPATH( "Tag :[" << sTagName.c_str() << "] not defined.")

				WorkflowRelevantData::Attributes& vVars = task->getAttributes();
                WorkflowRelevantData::Attribute* var = vVars.get (sTagName.c_str());
                if ( var != NULL )
                {
                    CM_TRACE_CODEPATH( "Adding Attrbiute[" << var->getValue() << "]")
                    sReport.append(var->getValue());
                }
                else
                {
					vVars = process->getAttributes();
					var = vVars.get(sTagName.c_str());
                    if ( var != NULL )
                    {
                        CM_TRACE_CODEBLOCK( "Adding Attrbiute[" << var->getValue() << "]")   
                        sReport.append(var->getValue());
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
	    sReport.append(sTemplate.substr(iPosCur));

	report.setDateTime( DateTime::getCurrentDateTime().toString() );
	report.setValue(sReport.getData());
}
