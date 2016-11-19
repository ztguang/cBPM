#ifndef _WORKFLOW_PROCESS_INSTANCE_REPOSITORY_H_
#define _WORKFLOW_PROCESS_INSTANCE_REPOSITORY_H_

#include "bOS.h"
#include "bOSXMLDirectory.h"

namespace DataManager
{
	namespace DataBase
	{
		namespace FileSystem
		{
			class WorkflowProcessInstanceRepository : public bOS::XML::Data::XMLDirectory
			{
			public:
				WorkflowProcessInstanceRepository();
				~WorkflowProcessInstanceRepository();

			private:

			};
		}
	}
}

#endif //_WORKFLOW_PROCESS_INSTANCE_REPOSITORY_H_