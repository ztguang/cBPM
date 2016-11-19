#include "CommonDefines.h"

#include "XMLActionXSLT.h"
using namespace WorkflowEngine::Criteria::BasicTask::XML::Action;

#include "bOS.h"
#include "bOSXSLTManager.h"

#include "bOSFileSystem.h"
using namespace bOS::IO;

String XMLActionXSLT::WF_OBJECT		= "WF_OBJECT";
String XMLActionXSLT::XMLFILE_IN	= "XMLFILE_IN";
String XMLActionXSLT::XMLFILE_OUT	= "XMLFILE_OUT";
String XMLActionXSLT::XSLFILE_IN	= "XSLFILE_IN";
String XMLActionXSLT::XMLSTRING_IN	= "XMLSTRING_IN";
String XMLActionXSLT::XMLSTRING_OUT	= "XMLSTRING_OUT";
String XMLActionXSLT::XSLSTRING_IN	= "XSLSTRING_IN";


XMLActionXSLT::XMLActionXSLT( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
    : XMLAction(process, task) 
{
	iInFlag = XSLTParamType(NONE);
	iOutFlag = XSLTParamType(NONE);
	iXslFlag = XSLTParamType(NONE);
}

XMLActionXSLT::~XMLActionXSLT() 
{
}

int XMLActionXSLT::action( String& result )
{
	CM_CODEBLOCK(action)

    int feErr = this->evaluateAction();
    
	if ( feErr != FE_OK)
	{
		CM_TRACE_CODEPATH( "No Action performed.")
        return feErr;
	}

	bool bRet=true;

	bOS::XML::XSLT::XSLTManager xsltManager;

	if ( iInFlag == XSLTParamType(FILE) && 
		 iOutFlag == XSLTParamType(FILE) && 
		 iXslFlag == XSLTParamType(FILE) )
	{
		xsltManager.byFile (sIn.c_str() , sXsl.c_str(), sOut.c_str());

	}
	else
	{
		String sXmlIn;
		if ( iInFlag == XSLTParamType(FILE) )
		{
			sXmlIn = FileSystem::getStringFile (sIn);
		}
		String sXslIn;
		if ( iXslFlag == XSLTParamType(FILE) )
		{
			sXslIn = FileSystem::getStringFile (sIn);
		}

		String sXmlOut = xsltManager.byString (sXmlIn.c_str(), sXslIn.c_str());

		if ( iOutFlag == XSLTParamType(FILE) )
		{
			ofstream fOut(sOut.c_str());
			fOut << sXmlOut;
		}
		else
		{
			varOut->setValue (sXmlOut);
			_varsContext.add(*varOut);
		}
	}
	
	return FE_OK;
}

int XMLActionXSLT::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	int iErr = XMLAction::evaluateAction ();
	
	if ( iErr != FE_OK)
	{
		CM_TRACE_CODEPATH( "No Action performed.")
        return iErr;
	}

	//TODO:
	//Designing an action for Email.
	WorkflowRelevantData::Attribute* var = NULL;
	
	var = getAttribute( XMLActionXSLT::WF_OBJECT );
	if ( var != NULL ) 
	{
		iInFlag = XSLTParamType(WF_OBJ);
		//TODO
		//sIn = _process->getXMLText();
	}
	var = getAttribute( XMLActionXSLT::XMLFILE_IN );
	if ( var != NULL ) 
	{
		iInFlag = XSLTParamType(FILE);
		//modify by mfarina on 22/05/2005 for bug 1
		//sIn = getEvaluatedParameter(var->getValue());
		sIn = getEvaluatedParameter(var->getValue(), var->getType().c_str());
	}
	var = getAttribute( XMLActionXSLT::XMLFILE_OUT );
	if ( var != NULL ) 
	{
		iOutFlag = XSLTParamType(FILE);
		//modify by mfarina on 22/05/2005 for bug 1
		//sOut = getEvaluatedParameter(var->getValue());
		sOut = getEvaluatedParameter(var->getValue(), var->getType().c_str());
	}
	var = getAttribute( XMLActionXSLT::XSLFILE_IN );
	if ( var != NULL ) 
	{
		iXslFlag = XSLTParamType(FILE);
		//modify by mfarina on 22/05/2005 for bug 1
		//sXsl = getEvaluatedParameter(var->getValue());
		sXsl = getEvaluatedParameter(var->getValue(), var->getType().c_str());

	}
	var = getAttribute( XMLActionXSLT::XMLSTRING_IN );
	if ( var != NULL ) 
	{
		iInFlag = XSLTParamType(STRING);
		//modify by mfarina on 22/05/2005 for bug 1
		//sIn = getEvaluatedParameter(var->getValue());
		sIn = getEvaluatedParameter(var->getValue(), var->getType().c_str());
	}
	var = getAttribute( XMLActionXSLT::XMLSTRING_OUT );
	if ( var != NULL ) 
	{
		iOutFlag = XSLTParamType(STRING);
		
		String sValue =var->getValue();
		
		sOut = sValue.substr(1, sValue.length() - 2);

		varOut = getAttribute(sOut);
		
	}
	var = getAttribute( XMLActionXSLT::XSLSTRING_IN );
	if ( var != NULL ) 
	{
		iXslFlag = XSLTParamType(STRING);
		//modify by mfarina on 22/05/2005 for bug 1
		//sXsl = getEvaluatedParameter(var->getValue());
		sXsl = getEvaluatedParameter(var->getValue(), var->getType().c_str());
	}

	if ( iXslFlag == XSLTParamType(NONE) )
	{
		sXsl = _ActionText;
	}

    return FE_OK;
}

