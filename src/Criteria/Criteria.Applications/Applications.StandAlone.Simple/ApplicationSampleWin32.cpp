#include "bOS/bOS.h"
#include "bOS/bOSStringUtils.h"
using namespace bOS::CoreString;

#include "ApplicationSampleWin32.h"

#include "Scenario/ApplicationFunction.h"
#include "Scenario/ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

ApplicationSampleWin32::ApplicationSampleWin32()
{
}

ApplicationSampleWin32::~ApplicationSampleWin32()
{
}

char* ApplicationSampleWin32::one(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);
		
		/*
		if ( !strcmp(parameter->getName().c_str(), "XML_FILE") )
		{
			sXmlFile = parameter->getValue();
		}
		else if ( !strcmp(parameter->getName().c_str(), "XSL_FILE") )
		{
			sXslFile = parameter->getValue();
		}
		else if ( !strcmp(parameter->getName().c_str(), "PDF_FILE") )
		{
			sPdfFile = parameter->getValue();
		}
		*/
	}

	long lCode = 0;
	String sMessage;

	//exec

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);

	return StringUtils::toChar(result.getXMLString(0));
}

char* ApplicationSampleWin32::two(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);
		
		/*
		if ( !strcmp(parameter->getName().c_str(), "XML_FILE") )
		{
			sXmlFile = parameter->getValue();
		}
		else if ( !strcmp(parameter->getName().c_str(), "XSL_FILE") )
		{
			sXslFile = parameter->getValue();
		}
		else if ( !strcmp(parameter->getName().c_str(), "PDF_FILE") )
		{
			sPdfFile = parameter->getValue();
		}
		*/
	}

	long lCode = 0;
	String sMessage;

	//exec

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);

	return StringUtils::toChar(result.getXMLString(0));
}