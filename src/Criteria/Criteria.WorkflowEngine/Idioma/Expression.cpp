#include "CommonDefines.h"

#include "Expression.h"
#include "Condition.h"
using namespace WorkflowEngine::Idioma;

#include "Tracer.h"

//Function Delimiter
const String Expression::DELIMITER_BEGIN			="*";
const String Expression::DELIMITER_END				="*";
const String Expression::DELIMITER_RESULT_BEGIN		="?";
const String Expression::DELIMITER_RESULT_END		="?";
const String Expression::DELIMITER_PARAM_BEGIN		="%";
const String Expression::DELIMITER_PARAM_END		="%";

void Expression::make( String &sStatement )
{ 
	CM_CODEBLOCK(make)

	bool bParam=false;
	ExpressionItemType eItem = EXPRESSION_NO;
	ExpressionItemType eItemFound;
	unsigned int uiDelimiterSize;
	unsigned int uiPosInit;
	String sStat;
	int iRec=0;
	
	bool bBegin=true;
	for ( unsigned int i=0; i<sStatement.size();)
	{
		eItemFound=EXPRESSION_NO;

		sStat = sStatement.substr(i);

		if ( (uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,DELIMITER_RESULT_BEGIN))  > 0 )
			eItemFound= EXPRESSION_RESULT;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,DELIMITER_RESULT_END)) > 0 ) 
			eItemFound= EXPRESSION_RESULT;
		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,Condition::DELIMITER_BEGIN))  > 0 )
		{
			if ( eItem==EXPRESSION_CONDITION) 
			{
				iRec++;
				i++;
				continue;
			}
			else
				eItemFound= EXPRESSION_CONDITION;
		}
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat, Condition::DELIMITER_END)) > 0 ) 
		{
			if ( iRec == 0 )
				eItemFound= EXPRESSION_CONDITION;
			else
			{
				iRec--;
				i++;
				continue;
			}

		}
		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,Parameter::DELIMITER_INPUT_BEGIN))  > 0 )
			eItemFound= EXPRESSION_PARAM;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Parameter::DELIMITER_INPUT_END)) > 0 ) 
			eItemFound= EXPRESSION_PARAM;
		else
		{
			i++;
			continue;
		}

		if ( eItemFound == EXPRESSION_NO )
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
					case EXPRESSION_RESULT:
						sResultAttribute = sStat;
						break;

					

					case EXPRESSION_PARAM:
						
						if ( bConditionResult ) 
						{
							if ( !bParam )
								sResult = assignParameter(sStat);
						}
						else
						{
							if ( bParam ) 
								sResult = assignParameter(sStat);
						}
						bParam=true;

						break;

					case EXPRESSION_CONDITION:
						Condition condition;
						condition.setRetrieveParameter ( retrieveParameter);
						condition.make(sStat);
						bConditionResult = condition.getResult();

						break;
					}
				}
				else
				{
					i++;
					continue;
				}
			}
		}
	}
}


String Expression::assignParameter(String sParam)
{
	if ( isLiteralValue(sParam) )
	{
		return sParam;
	}
	else
		return retrieveParameter->getValue(sParam);
}


