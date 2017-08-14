#ifndef __BASEACTION_H__
#define __BASEACTION_H__

#include "Evaluator.h"
#include "Expression.h"
#include "ItemInterface.h"
#include "ScriptException.h"
#include "Function.h"
#include "FreeText.h"
#include "Keyword.h"
using namespace WorkflowEngine;

#include "WorkflowProcess.h"
#include "Activity.h"
using namespace DataManager::Panorama;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Action
			{
				class BaseAction
				{
					public:

						BaseAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task );

						virtual ~BaseAction();

						virtual int action( String& result ) = 0;

						virtual int fix();

						WorkflowRelevantData::Attributes& getVarsContext();

						WorkflowRelevantData::Attribute* getAttribute( const String& name );

						void setNotEvaluateAction();

					protected:

						//modify by mfarina on 22/05/2005 for bug 1
						String getEvaluatedParameter(const String& sParamValue, const char* acType = NULL);

						virtual int evaluateAction();

						Idioma::Evaluator*  _script;
						String				_ActionText;

						WorkflowRelevantData::Attributes _varsContext;
   						WorkflowRelevantData::Attributes _privateAttributes;
						WorkflowRelevantData::Attributes _publicAttributes;

						static const String ACTION_NONE;

						WorkflowProcesses::Activity* task;
						WorkflowProcesses::WorkflowProcess* process;

						bool bEvaluateAction;

					private:

						//rem by mfarina on 10/11/2006
						//void setAttributes(WorkflowRelevantData::Attributes& attList, bool bPrivate = true );
				};
			}
		}
	}
}

#endif



