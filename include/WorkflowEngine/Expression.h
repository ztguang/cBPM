#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#define FILE_TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"
#include "ItemInterface.h"
#include "RetrieveParameter.h"

#include "Parameter.h"

namespace WorkflowEngine
{
	namespace Idioma
	{
		class ENGINE_API Expression : public ItemInterface
		{
    		public:
		
				enum ExpressionItemType
				{
					EXPRESSION_NO,
					EXPRESSION_RESULT,
					EXPRESSION_CONDITION,
					EXPRESSION_PARAM
				};

				Expression() : ItemInterface (ITEM_EXPRESSION) 
				{
				}
			
				virtual ~Expression() {;}

				String getStatement() { return "";}

				static const String DELIMITER_BEGIN;
				static const String DELIMITER_END;

				static const String DELIMITER_RESULT_BEGIN;
				static const String DELIMITER_RESULT_END;

				static const String DELIMITER_PARAM_BEGIN;
				static const String DELIMITER_PARAM_END;

    			void make( String &sStatement );

				void setRetrieveParameter(RetrieveParameter* retrieve) { retrieveParameter=retrieve;}
				String getResult() { return sResult;}

				String getResultAttribute() { return sResultAttribute;}

			private:

				String assignParameter(String sValue);
				RetrieveParameter* retrieveParameter;

				bool bConditionResult;
				String sResult;
				String sResultAttribute;
		};
	}
}
#endif


