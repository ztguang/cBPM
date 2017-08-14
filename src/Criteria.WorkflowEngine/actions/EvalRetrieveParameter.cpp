#include "CommonDefines.h"

#include "BaseAction.h"
#include "EvalRetrieveParameter.h"
using namespace WorkflowEngine::Criteria::BasicTask::Action;

String EvalRetrieveParameter::getValue(String sAttributeName)
{
	WorkflowRelevantData::Attribute* attr = NULL;

	attr = action->getAttribute(sAttributeName);

	if ( attr != NULL ) 
	{
		return attr->getValue();
	}
	

	return "";
}



