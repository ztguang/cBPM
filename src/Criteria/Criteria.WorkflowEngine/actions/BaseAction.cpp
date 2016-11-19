#include "CommonDefines.h"

#include "ScriptException.h"
using namespace WorkflowEngine;

#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "BaseAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Action;

const String BaseAction::ACTION_NONE = "[NONE]";

BaseAction::BaseAction( WorkflowProcesses::WorkflowProcess* _process, WorkflowProcesses::Activity* _task )
{
	CM_CODEBLOCK(BaseAction)

	assert(_process != NULL);
	assert(_task != NULL);

	{
		CM_CODEBLOCK(BaseAction-AssignAttributes)
		/*
		setAttributes( _task->getAttributes() );              //private
		setAttributes( _process->getAttributes(), false );    //public
		*/
		_privateAttributes.assign( _task->getAttributes() );
		_publicAttributes.assign(_process->getAttributes());
	}

	_script = NULL;

    _ActionText = _task->getBehaviour().getScriptCommand();

	task = _task;
	process = _process;
}

BaseAction::~BaseAction()
{
    if ( _script != NULL )
        delete _script;
}

int BaseAction::fix()
{
    return FE_OK;
}

WorkflowRelevantData::Attribute* BaseAction::getAttribute( const String& name )
{
	String s= name;
	WorkflowRelevantData::Attribute* var = _privateAttributes.get(s.c_str());
	if ( var == NULL )
	{
		var = _publicAttributes.get(s.c_str());
	}

	return var;
}

int BaseAction::evaluateAction()
{
	if ( strcmp(_ActionText.c_str(), BaseAction::ACTION_NONE.c_str() )  == 0 )
	{
		return FE_TASK_TASKACTION_NONE;
	}

    try
    {
		_script = new Idioma::Evaluator( _ActionText );
        assert( _script != NULL );
    }
	catch ( Idioma::ScriptException& )
    {
        return FE_TASK_TASKACTION_ERROR;
    }
    return FE_OK;
}

/*
void BaseAction::setAttributes( WorkflowRelevantData::Attributes& vars, bool bPrivate )
{
	WorkflowRelevantData::Attributes* _list;

	if ( bPrivate )
		_list = &_privateAttributes;
	else
		_list = &_publicAttributes;

	_list->add(vars);
}
*/

WorkflowRelevantData::Attributes& BaseAction::getVarsContext()
{
	return _varsContext;
}

//modify by mfarina on 22/05/2005 for bug 1
String BaseAction::getEvaluatedParameter(const String& sParamValue, const char* acType)
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
				//modify by mfarina on 22/05/2005 for bug 1
                else if ( acType != NULL )
				{
					try
					{
						strReport << DataBaseHelper::instance()->GetValueFromDataType(acType, sTagName);
					}
					catch ( DBException&)
					{
						CM_TRACE_CODEBLOCK( "Attribute not found.")
						strReport << sTagName;
					}
				}
				else
                {
                    CM_TRACE_CODEBLOCK( "Attribute not found.")
                    strReport << sTagName;
                }
            //}

		    iPosCur = iPosTagE+1;

            if ( (unsigned int)iPosCur == sParamValue.length () )
                break;
        }
        else
        {
            iPosCur=++iPosTagB;
        }
	} // while

    if ( (unsigned int)iPosCur > sParamValue.length () )
        strReport << ends;
    else
	    strReport << sParamValue.substr(iPosCur) << ends;

	String sReturn = strReport.str();

	if ( sReturn.find("[", 0) != -1 )
	{
		return getEvaluatedParameter(sReturn, acType);
	}

    return sReturn;
}

void BaseAction::setNotEvaluateAction()
{
	bEvaluateAction = false;
}
