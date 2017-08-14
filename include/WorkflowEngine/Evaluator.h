#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

#define FILE_TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"
#include "ItemInterface.h"
#include "RetrieveParameter.h"

namespace WorkflowEngine
{
	namespace Idioma
	{
		class FreeText;
		class Keyword;
		class Function;
		class Expression;
		class Condition;

		class ENGINE_API Evaluator
		{	
    		public:
		
				Evaluator();

				Evaluator( String &sStatement );
			
				virtual ~Evaluator();

				void make( String &sStatement );
			
				FreeText* addFreeText( String &sText );
			
				Keyword* addKeyword( String &sKeyword );
			
				Function* addFunction();

				Expression* addExpression();

				Condition* addCondition();

				String getStatement();

				ItemInterface* getFirstItem( ItemListIterator& iItem );
				ItemInterface* getNextItem( ItemListIterator& iItem );
				void setRetrieveParameter(RetrieveParameter* retrieve) { retrieveParameter=retrieve;}

			private:
			
				ItemList itemList;
			
				String _statement;
				RetrieveParameter* retrieveParameter;
		};
	}
}

#endif


