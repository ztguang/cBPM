#include "bOS/Tracer.h"

#include "Scenario/ApplicationTemplate.h"
#include "ApplicationSampleWin32.h"

int main()
{
	CM_SETTING_TO("ApplicationTemplate", CodeTracer::CODEBLOCK_LEVEL)

	ApplicationTemplate* application = new ApplicationTemplate();

	//register methods
	application->addCallBack("one", ApplicationSampleWin32::one);
	application->addCallBack("two", ApplicationSampleWin32::two);
	
	application->startup ("Criteria.Applications.StandAlone.Simple");
}