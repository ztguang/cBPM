#include "CommonDefines.h"

#include "Evaluator.h"

#include "Expression.h"
#include "FreeText.h"
#include "Function.h"
#include "Keyword.h"
#include "Condition.h"

#include "ScriptException.h"
using namespace WorkflowEngine::Idioma;

#include "Tracer.h"

Evaluator::Evaluator() 
{ 
	CM_CODEBLOCK(Evaluator)
}

Evaluator::Evaluator( String &sStatement )
{ 
	CM_CODEBLOCK(Evaluator)
	make(sStatement);
}

Evaluator::~Evaluator() 
{ 
	CM_CODEBLOCK(~Evaluator)
	
    for ( unsigned int i=0; i<itemList.size(); i ++ )
	{
		delete itemList.at(i);
	}

	itemList.clear();
}


void Evaluator::make( String &sStatement )
{ 
	CM_CODEBLOCK(make)

	ItemType eItem=ITEM_NO;
	ItemType eItemFound;
	unsigned int uiDelimiterSize;
	unsigned int uiPosInit;
	String sStat;
    String sItem;
	bool bBegin=true;
	int iRec=0;

    //
	for ( unsigned int i=0; i<sStatement.size();)
	{
		eItemFound=ITEM_NO;

		sStat = sStatement.substr(i);

		if ( (uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Keyword::DELIMITER_BEGIN))  > 0 )
			eItemFound= ITEM_KEYWORD;

		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Keyword::DELIMITER_END)) > 0 ) 
			eItemFound= ITEM_KEYWORD; 

		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,Function::DELIMITER_BEGIN))  > 0 )
			eItemFound= ITEM_FUNCTION;

		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Function::DELIMITER_END)) > 0 ) 
			eItemFound= ITEM_FUNCTION;

		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,FreeText::DELIMITER_BEGIN))  > 0 )
			eItemFound= ITEM_FREETEXT;

		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,FreeText::DELIMITER_END)) > 0 ) 
			eItemFound= ITEM_FREETEXT;
		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,Expression::DELIMITER_BEGIN))  > 0 )
			eItemFound= ITEM_EXPRESSION;

		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat,Expression::DELIMITER_END)) > 0 ) 
			eItemFound= ITEM_EXPRESSION;

		else if ((uiDelimiterSize= ItemInterface::CheckDelimiter(sStat,Condition::DELIMITER_BEGIN))  > 0 )
		{
			if ( eItem==ITEM_CONDITION) 
			{
				iRec++;
				i++;
				continue;
			}
			else
				eItemFound= ITEM_CONDITION;
		}
		else if ((uiDelimiterSize=ItemInterface::CheckDelimiter(sStat, Condition::DELIMITER_END)) > 0 ) 
		{
			if ( iRec == 0 )
				eItemFound= ITEM_CONDITION;
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


		if ( bBegin ) 
		{
            bBegin=false;
			eItem = eItemFound;
			i+=uiDelimiterSize;
			uiPosInit = i;
		}
		else
		{
			if ( eItem == eItemFound ) 
			{
				bBegin = true;
				String sStat = sStatement.substr(uiPosInit, i-uiPosInit);

				i+=uiDelimiterSize;

				Function *pFunc=NULL;
				Expression* expression=NULL;
				Condition* condition =NULL;

				switch ( eItemFound ) 
				{
					case ITEM_FREETEXT:
						addFreeText(sStat);
						break;
					case ITEM_KEYWORD:
						addKeyword(sStat);	
						break;
					case ITEM_FUNCTION:
						pFunc= addFunction();
						pFunc->make(sStat);
						break;
					case ITEM_EXPRESSION:
						expression = addExpression();
						expression->setRetrieveParameter(retrieveParameter);
						expression->make(sStat);
						break;
					case ITEM_CONDITION:
						condition = addCondition();
						condition->setRetrieveParameter(retrieveParameter);
						condition->make(sStat);
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

FreeText* Evaluator::addFreeText(String &sText)
{
	CM_CODEBLOCK(addFreeText)

	FreeText* ft = new FreeText(sText);

	itemList.push_back(ft);

	return ft;
}

Keyword* Evaluator::addKeyword( String &sText )
{
	CM_CODEBLOCK(addKeyword)

	Keyword* kw = new Keyword(sText);

	itemList.push_back(kw);

	return kw;
}

Function* Evaluator::addFunction()
{
	CM_CODEBLOCK(addFunction)

	Function* func = new Function();

	itemList.push_back(func);

	return func;
}

Expression* Evaluator::addExpression()
{
	CM_CODEBLOCK(addExpression)

	Expression* expression = new Expression();

	itemList.push_back(expression);

	return expression;
}

Condition* Evaluator::addCondition()
{
	CM_CODEBLOCK(addCondition)

	Condition* condition = new Condition();

	itemList.push_back(condition);

	return condition;
}


String Evaluator::getStatement() 
{ 
	CM_CODEBLOCK(getStatement)

	String sStatement;

	for ( unsigned int i=0; i<itemList.size(); i ++ )
	{
		sStatement+=(itemList.at(i))->getStatement();
	}

	return sStatement;
}


ItemInterface* Evaluator::getNextItem( ItemListIterator& iItem )
{
    if ( iItem !=  itemList.end() )
    {
        iItem++;

        if ( iItem !=  itemList.end() )
            return (*iItem);
        else
            return (ItemInterface *)NULL;
    }
    
    return (ItemInterface *)NULL;

}

ItemInterface* Evaluator::getFirstItem( ItemListIterator& iItem )
{
	if ( itemList.size() > 0 )
	{
		iItem = itemList.begin();
		return (*iItem);
	}

	return (ItemInterface *)NULL;
}

