#ifndef _EVA_RETRIEVE_PARAMETER_H_
#define _EVA_RETRIEVE_PARAMETER_H_

#include "RetrieveParameter.h"
using namespace WorkflowEngine;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
		namespace Action
		{
			class BaseAction;

			class EvalRetrieveParameter : public Idioma::RetrieveParameter
			{
			public:
				EvalRetrieveParameter() {action=NULL;}
				virtual ~EvalRetrieveParameter() {;}

				void setAction(BaseAction* _action) {action=_action;}

				String getValue(String sValue);

			private:
				BaseAction* action;
			};
		}
	
		}
	}
}


#endif //
