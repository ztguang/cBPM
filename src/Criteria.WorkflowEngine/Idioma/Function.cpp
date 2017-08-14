#include "CommonDefines.h"

#include "Function.h"
using namespace WorkflowEngine::Idioma;

#include "Tracer.h"

//Function Delimiter
const String Function::DELIMITER_BEGIN				="^";
const String Function::DELIMITER_END				="^";
const String Function::DELIMITER_RESULT_BEGIN		="?";
const String Function::DELIMITER_RESULT_END		="?";
const String Function::DELIMITER_FUNCTION_BEGIN	="@";
const String Function::DELIMITER_FUNCTION_END		="@";

Function::~Function() 
{ 
	CM_CODEBLOCK(~Function)
	
    for ( unsigned int i=0; i<paramList.size(); i ++ )
		delete paramList.at(i);

	paramList.clear();
}

String Function::getStatement() 
{
	CM_CODEBLOCK(getStatement)

	String statement="";

    if ( _result.compare("") != 0 ) 
	    statement  += DELIMITER_RESULT_BEGIN + _result + DELIMITER_RESULT_END;

	statement += DELIMITER_FUNCTION_BEGIN + _functionName + DELIMITER_FUNCTION_END;

	for (unsigned int i=0; i<paramList.size(); i++)
		statement+=(paramList.at(i))->getStatement();

	return DELIMITER_BEGIN + statement + DELIMITER_END;
}

Parameter* Function::addParameter( ParamType eType, String sName )
{
	CM_CODEBLOCK(addParameter)

	Parameter *param = new Parameter(eType, sName);
	paramList.push_back(param);
	return param;
}

void Function::make( String &sStatement )
{ 
	CM_CODEBLOCK(make)

	FunctionItemType eItem = FUNCTION_NO;
	FunctionItemType eItemFound;
	unsigned int uiDelimiterSize;
	unsigned int uiPosInit;
	String sStat;
	
	bool bBegin=true;
	for ( unsigned int i=0; i<sStatement.size();)
	{
		eItemFound=FUNCTION_NO;

		sStat = sStatement.substr(i);

		if ( (uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,DELIMITER_FUNCTION_BEGIN))  > 0 )
			eItemFound= FUNCTION_NAME;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,DELIMITER_FUNCTION_END)) > 0 ) 
			eItemFound= FUNCTION_NAME;
		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,DELIMITER_RESULT_BEGIN))  > 0 )
			eItemFound= FUNCTION_RESULT;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat, DELIMITER_RESULT_END)) > 0 ) 
			eItemFound= FUNCTION_RESULT;
		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,Parameter::DELIMITER_INPUT_BEGIN))  > 0 )
			eItemFound= FUNCTION_PARAMIN;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Parameter::DELIMITER_INPUT_END)) > 0 ) 
			eItemFound= FUNCTION_PARAMIN;
		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,Parameter::DELIMITER_OUTPUT_BEGIN))  > 0 )
			eItemFound= FUNCTION_PARAMOUT;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Parameter::DELIMITER_OUTPUT_END)) > 0 ) 
			eItemFound= FUNCTION_PARAMOUT;
		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,Parameter::DELIMITER_INPUTOUTPUT_BEGIN))  > 0 )
			eItemFound= FUNCTION_PARAMINOUT;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Parameter::DELIMITER_INPUTOUTPUT_END)) > 0 ) 
			eItemFound= FUNCTION_PARAMINOUT;
		else
		{
			i++;
			continue;
		}

		if ( eItemFound == FUNCTION_NO )
		{
			//exception
		}
        else
		{
			if ( bBegin ) 
			{
				eItem = eItemFound;
				bBegin=false;
				i+=uiDelimiterSize;
				uiPosInit = i;
			}
			else
			{
				if ( eItem == eItemFound ) 
				{
					bBegin = true;
					String sStat = sStatement.substr(uiPosInit, i-uiPosInit);
					i += uiDelimiterSize;
					switch ( eItemFound ) 
					{
						case FUNCTION_NAME:
							addFunctionName(sStat);
							break;
						case FUNCTION_RESULT:
							addResult(sStat);	
							break;
						case FUNCTION_PARAMIN:
							addParameter(PARAM_IN,sStat);
							break;
						case FUNCTION_PARAMOUT:
							addParameter(PARAM_OUT,sStat);
							break;
						case FUNCTION_PARAMINOUT:
							addParameter(PARAM_INOUT,sStat);
							break;
					}

				}
				else
				{
					//exception
				}
			}
		}
	}
}


Parameter* Function::getFirstParam( ParamListIterator& iParam )
{
	if ( paramList.size() > 0 )
	{
		iParam = paramList.begin();
		return (*iParam);
	}

	return (Parameter *)NULL;
}

Parameter* Function::getNextParam( ParamListIterator& iParam )
{
	if ( iParam !=  paramList.end() )
    {
        iParam++;

        if ( iParam !=  paramList.end() )
            return (*iParam);
        else
            return (Parameter *)NULL;
    }

	return (Parameter *)NULL;
}


