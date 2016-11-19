#include "ScriptFunctionExecution.h"
#include "ApplicationException.h"
using namespace WorkflowEngine;

#include "Applications.h"
#include "Application.h"
#include "ApplicationFunction.h"


#include "Tracer.h"

ScriptFunctionExecution::ScriptFunctionExecution(ApplicationFunction* _functionsignature, ApplicationFunction* _function) : 
	FunctionExecution(_function)
{
	functionsignature = _functionsignature;
}

ScriptFunctionExecution::~ScriptFunctionExecution()
{
}

const char* ScriptFunctionExecution::run()
{
	CM_CODEBLOCK(ScriptFunctionExecution::run)

	/*Common::FormalParameters& vParameters = function->getParameters();
	Common::FormalParameter* parameter = NULL;

	for ( int i=0; i<vParameters.size(); i++)
	{
		parameter = (Common::FormalParameter*)vParameters.at(i);
		CM_TRACE_DEBUG("Parameter[" << parameter->getValue() << "]")
		_Arguments.push_back(parameter->getValue() );
	}*/

	try
    {
		ApplicationFunctionResult result;
		result.setCode (0);
		result.setMessage ("OK");

		Common::FormalParameters& vParametersIn = function->getParameters();
		Common::FormalParameters& vParametersOut = result.getParameters();

		Common::FormalParameters& vParameters = functionsignature->getResult().getParameters();
		Common::FormalParameter* parameter = NULL;

		//Calcolo
		//CVCalcParser cvCalcParser;

		for ( unsigned int i=0; i<vParameters.size(); i++)
		{
			parameter = (Common::FormalParameter*)vParameters.at(i);
			CM_TRACE_DEBUG("Parameter[" << parameter->getName() << "] [" << parameter->getValue() << "]")

			string sValue = parameter->getValue();
			for ( unsigned int j=0; j<vParametersIn.size(); j++)
			{
				Common::FormalParameter* parameterIn = (Common::FormalParameter*)vParametersIn.at(j);
				string sToken="[";
				sToken+=parameterIn->getName();
				sToken+="]";

				sValue = this->replace (sValue, sToken, parameterIn->getValue());

			}

			string sProcessedValue;

			int iPos =-1;
			while ( (iPos=sValue.find(",")) > -1 )
			{
				sValue=( sValue.substr(0, iPos) + "." + sValue.substr(iPos+1));
			}

			//try
			//{
				if ( sValue.find("str",0) == 0 )
				{
					sProcessedValue =sValue.substr (3);
				}
				else if ( sValue.find("intero", 0) != -1 ) 
				{
					//sProcessedValue = StringUtils::toString ((int)cvCalcParser.Evaluate(sValue));
				}
				else
				{
					char tmp[20];
					memset( tmp, 0, 20);
					//sprintf( tmp, "%.2f", (double)cvCalcParser.Evaluate(sValue));
					sProcessedValue = tmp;
				}

				//if ( cvCalcParser.HasWarning() )
				//{
				//	CM_TRACE_WARNING(cvCalcParser.GetWarningMsg())
				//}
			//}
			//catch(CVCalcParserException)
			//{
			//}

			Common::FormalParameter parameterOut(parameter->getName(), sProcessedValue);
			parameterOut.setType (parameter->getType());
			vParametersOut.addParameter (parameterOut);
		}

		char* acReceive = StringUtils::toChar (result.getXMLString(0));

		CM_TRACE_DEBUG(acReceive )
		return acReceive;
	}
    catch (...)
    {
		CM_TRACE_ERROR( "Script Error")
		throw new DynamicLibraryException("Script Error");
    }
}

//to insert in bos::StringUtils
String ScriptFunctionExecution::replace(const String& sValue, const String& sParam, const String& sParamValue)
{
    CM_CODEBLOCK(replace)
	CM_TRACE_DEBUG("Value[" << sValue << "] Token[" << sParam << "] TokenValue[" << sParamValue << "]")

	ostrstream strReport;
	
	int iPosTagB;
	int iPosTagE=0;
	int iPosCur=0;

	while ( (iPosTagB=sValue.find(sParam, iPosCur )) != -1 )
	{
		strReport << sValue.substr( iPosCur, iPosTagB - iPosCur);
		strReport << sParamValue;

		iPosCur=iPosTagB+sParam.length ();
	}

    if ( iPosCur > sValue.length () ) 
        strReport << ends;
    else
	    strReport << sValue.substr(iPosCur) << ends;


    return strReport.str();
}
