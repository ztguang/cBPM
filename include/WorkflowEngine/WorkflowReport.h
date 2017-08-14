#ifndef __WORKFLOW_REPORT_H__
#define __WORKFLOW_REPORT_H__

#include "WorkflowProcess.h"
#include "Activity.h"
#include "Report.h"
using namespace DataManager::Panorama;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			class WorkflowReport
			{
				public:
					WorkflowReport(WorkflowProcesses::WorkflowProcess*,WorkflowProcesses::Activity*);
					virtual ~WorkflowReport();

					void compileReport(WorkflowProcesses::Report&);

				private:
					WorkflowProcesses::Activity* task;
					WorkflowProcesses::WorkflowProcess* process;

					
			};
		}
	}
}

#endif 


