#include "CommonDefines.h"

#include "Condition.h"
using namespace WorkflowEngine::Idioma;

#include "Tracer.h"

const String Condition::DELIMITER_BEGIN						="(";
const String Condition::DELIMITER_END						=")";
const String Condition::DELIMITER_PARAM_BEGIN				="%";
const String Condition::DELIMITER_PARAM_END					="%";
const String Condition::DELIMITER_OPERATOR_BEGIN			="@";
const String Condition::DELIMITER_OPERATOR_END				="@";
const String Condition::DELIMITER_LOGICALOPERATOR_BEGIN		="#";
const String Condition::DELIMITER_LOGICALOPERATOR_END		="#";

const String Condition::OPERATOR_EQUAL_VALUE				="==";
const String Condition::OPERATOR_NOTEQUAL_VALUE				="!=";
const String Condition::OPERATOR_GREATHERTHAN_VALUE			=">";
const String Condition::OPERATOR_LESSTHAN_VALUE				="<";
const String Condition::OPERATOR_GREATHEREQUALTHAN_VALUE	=">=";
const String Condition::OPERATOR_LESSEQUALTHAN_VALUE		="<=";;

const String Condition::LOGICALOPERATOR_AND_VALUE			="AND";
const String Condition::LOGICALOPERATOR_OR_VALUE			="OR";
const String Condition::LOGICALOPERATOR_NOT_VALUE			="NOT";

/*
String Condition::getStatement() 
{
	CM_CODEBLOCK(getStatement)

	String statement=DELIMITER_BEGIN;
	statement+= DELIMITER_PARAM_BEGIN + sLeftParameter + DELIMITER_PARAM_END;
	statement+= DELIMITER_OPERATOR_BEGIN;

	switch ( iOperator)
	{
	case OPERATOR_EQUAL:
		statement+=OPERATOR_EQUAL_VALUE;
		break;
	case OPERATOR_GRATHERTHAN:
		statement+=OPERATOR_GREATHEREQUALTHAN_VALUE;
		break;
	case OPERATOR_LESSTHAN:
		statement+=OPERATOR_LESSTHAN_VALUE;
		break;
	case OPERATOR_NOTEQUAL:
		statement+=OPERATOR_NOTEQUAL_VALUE;
		break;
	case OPERATOR_GRATHEREQUALTHAN:
		statement+=OPERATOR_GREATHEREQUALTHAN_VALUE;
		break;
	case OPERATOR_LESSEQUALTHAN:
		statement+=OPERATOR_LESSEQUALTHAN_VALUE;
		break;
	}
	statement+= DELIMITER_OPERATOR_END;
	statement+= DELIMITER_END;

	return statement;
}
*/

void Condition::make( String &sStatement )
{ 
	CM_CODEBLOCK(make)

	bool bOperatorFound=false;
	bool bLogicalOperatorFound=false;
	bool bExecute = false;

	ConditionItemType eItem = CONDITION_NO;
	ConditionItemType eItemFound;

	unsigned int uiDelimiterSize;
	unsigned int uiPosInit;

	String sStat;
	int iRec=0;
	
	bool bBegin=true;
	for ( unsigned int i=0; i<sStatement.size();)
	{
		eItemFound=CONDITION_NO;

		sStat = sStatement.substr(i);

		if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,DELIMITER_PARAM_BEGIN))  > 0 )
			eItemFound= CONDITION_PARAM;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat, DELIMITER_PARAM_END)) > 0 ) 
			eItemFound= CONDITION_PARAM;
		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,DELIMITER_OPERATOR_BEGIN))  > 0 )
			eItemFound= CONDITION_OPERATOR;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,DELIMITER_OPERATOR_END)) > 0 ) 
			eItemFound= CONDITION_OPERATOR;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,DELIMITER_LOGICALOPERATOR_BEGIN)) > 0 ) 
			eItemFound= CONDITION_LOGICALOPERATOR;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,DELIMITER_LOGICALOPERATOR_END)) > 0 ) 
			eItemFound= CONDITION_LOGICALOPERATOR;
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Condition::DELIMITER_BEGIN)) > 0 ) 
		{
			if ( eItem==CONDITION_CONDITION) 
			{
				iRec++;
				i++;
				continue;
			}
			else
				eItemFound= CONDITION_CONDITION;
		}	
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Condition::DELIMITER_END)) > 0 ) 
		{
			if ( iRec == 0 )
				eItemFound= CONDITION_CONDITION;
			else
			{
				iRec--;
				i++;
				continue;
			}
		}
		else
		{
			i++;
			continue;
		}

		if ( eItemFound == CONDITION_NO )
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
						case CONDITION_PARAM:
							if ( bOperatorFound || bLogicalOperatorFound) 
							{
								sRightParameter=assignParameter(sStat);
								bExecute = true;
							}
							else
							{
								sLeftParameter=assignParameter(sStat);
							}
							break;

						case CONDITION_OPERATOR:
			
							if ( sStat == OPERATOR_EQUAL_VALUE) 
								iOperator=OPERATOR_EQUAL;
							else if ( sStat == OPERATOR_GREATHERTHAN_VALUE)
								iOperator=OPERATOR_GRATHERTHAN;
							else if ( sStat == OPERATOR_LESSTHAN_VALUE) 
								iOperator=OPERATOR_LESSTHAN;
							else if ( sStat == OPERATOR_NOTEQUAL_VALUE) 
								iOperator=OPERATOR_NOTEQUAL;
							else if ( sStat == OPERATOR_GREATHEREQUALTHAN_VALUE) 
								iOperator=OPERATOR_GRATHEREQUALTHAN;
							else if ( sStat == OPERATOR_LESSEQUALTHAN_VALUE) 
								iOperator=OPERATOR_LESSEQUALTHAN;

							bOperatorFound = true;

							break;

						case CONDITION_LOGICALOPERATOR:
			
							if ( sStat == LOGICALOPERATOR_AND_VALUE) 
								iLogicalOperator=LOGICALOPERATOR_AND;
							else if ( sStat == LOGICALOPERATOR_OR_VALUE)
								iLogicalOperator=LOGICALOPERATOR_OR;
							else if ( sStat == LOGICALOPERATOR_NOT_VALUE) 
								iLogicalOperator=LOGICALOPERATOR_NOT;

							bLogicalOperatorFound = true;

							break;

						case CONDITION_CONDITION:
							Condition condition;
							
							condition.setRetrieveParameter ( retrieveParameter);
							condition.make(sStat);
							

							if ( bOperatorFound || bLogicalOperatorFound) 
							{
								sRightParameter = ( condition.getResult() ? "1" : "0"); 
								bExecute = true;
							}
							else
								sLeftParameter = ( condition.getResult() ? "1" : "0"); 
							
							break;
					}

					if ( bExecute )
					{
						bExecute = false;
						if ( bOperatorFound ) 
						{
							if ( isOnlyDigit(sLeftParameter ) && isOnlyDigit(sRightParameter )) 
							{
								int iLeft=atoi(sLeftParameter.c_str());
								int iRight=atoi(sRightParameter.c_str());

								switch ( iOperator)
								{
								case OPERATOR_EQUAL:
									bResult = ( iLeft == iRight);
									break;
								case OPERATOR_GRATHERTHAN:
									bResult = ( iLeft > iRight);
									break;
								case OPERATOR_LESSTHAN:
									bResult = ( iLeft < iRight);
									break;
								case OPERATOR_NOTEQUAL:
									bResult = ( iLeft != iRight);
									break;
								case OPERATOR_GRATHEREQUALTHAN:
									bResult = ( iLeft >= iRight);
									break;
								case OPERATOR_LESSEQUALTHAN:
									bResult = ( iLeft <= iRight);
									break;
								}
							}
							else
							{
								if ( sLeftParameter.find("\"") == -1 ) 
								{
									sLeftParameter="\"" + sLeftParameter + "\"";
								}
								if ( sRightParameter.find("\"") == -1 ) 
								{
									sRightParameter="\"" + sRightParameter + "\"";
								}
								switch ( iOperator)
								{
								case OPERATOR_EQUAL:
									bResult = ( sLeftParameter == sRightParameter);
									break;
								case OPERATOR_GRATHERTHAN:
									bResult = ( sLeftParameter > sRightParameter);
									break;
								case OPERATOR_LESSTHAN:
									bResult = ( sLeftParameter < sRightParameter);
									break;
								case OPERATOR_NOTEQUAL:
									bResult = ( sLeftParameter != sRightParameter);
									break;
								case OPERATOR_GRATHEREQUALTHAN:
									bResult = ( sLeftParameter >= sRightParameter);
									break;
								case OPERATOR_LESSEQUALTHAN:
									bResult = ( sLeftParameter <= sRightParameter);
									break;
								}
							}
						}
						else
						{
							switch ( iLogicalOperator)
							{
							case LOGICALOPERATOR_AND:
								bResult = ( atoi(sLeftParameter.c_str()) && atoi(sRightParameter.c_str()));
								break;
							case LOGICALOPERATOR_OR:
								bResult = ( atoi(sLeftParameter.c_str()) || atoi(sRightParameter.c_str()));
								break;
							case LOGICALOPERATOR_NOT:
								bResult = !atoi(sLeftParameter.c_str());
								break;
							}
						}
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

String Condition::assignParameter(String sParam)
{
	if ( isLiteralValue(sParam) )
	{
		return sParam;
	}
	else
		return retrieveParameter->getValue(sParam);
}
