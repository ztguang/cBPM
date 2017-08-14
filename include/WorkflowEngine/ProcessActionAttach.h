#ifndef __PROCESS_ACTION_ATTACH_H__
#define __PROCESS_ACTION_ATTACH_H__

#include "ProcessAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			class Workflow;
		}

		namespace BasicTask
		{
			namespace Process
			{
				namespace Action
				{
					class ProcessActionAttach : public ProcessAction
					{
						public:
						
							ProcessActionAttach( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, int iLevel, bool bAttach );

							virtual ~ProcessActionAttach();

							virtual int action( String& result );

						protected:
							int createProcessInstance(String& sProcessName);

							String sTaskParentProcess;

							bool bAttach;

						private:
							
							void MigrateAttribute (WorkflowEngine::Criteria::Core::Workflow* workflow, WorkflowRelevantData::Attributes& taskAttributes, WorkflowRelevantData::Attributes& processAttribute);
					};
				}
			}
		}
	}
}

#endif 

