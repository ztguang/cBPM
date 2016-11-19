#ifndef __CONDITION_H__
#define __CONDITION_H__

#define FILE_TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

#include "ItemInterface.h"
#include "RetrieveParameter.h"

namespace WorkflowEngine
{
	namespace Idioma
	{
		class ENGINE_API Condition : public ItemInterface
		{
    		public:
		
				enum ConditionItemType
				{
					CONDITION_NO,
					CONDITION_PARAM,
					CONDITION_OPERATOR,
					CONDITION_LOGICALOPERATOR,
					CONDITION_CONDITION
				};

				enum OperatorItemType
				{
					OPERATOR_EQUAL, 
					OPERATOR_GRATHERTHAN,
					OPERATOR_LESSTHAN,
					OPERATOR_NOTEQUAL,
					OPERATOR_GRATHEREQUALTHAN,
					OPERATOR_LESSEQUALTHAN
				};

				enum LogicalOperatorType
				{
					LOGICALOPERATOR_AND,
					LOGICALOPERATOR_OR,
					LOGICALOPERATOR_NOT
				};

				Condition() : ItemInterface (ITEM_CONDITION) 
				{
				}
			
				virtual ~Condition() {;}

				String getStatement() {return "";}

				static const String DELIMITER_BEGIN;
				static const String DELIMITER_END;

				static const String DELIMITER_PARAM_BEGIN;
				static const String DELIMITER_PARAM_END;

				static const String DELIMITER_OPERATOR_BEGIN;
				static const String DELIMITER_OPERATOR_END;

				static const String DELIMITER_LOGICALOPERATOR_BEGIN;
				static const String DELIMITER_LOGICALOPERATOR_END;
				
				static const String OPERATOR_EQUAL_VALUE;
				static const String OPERATOR_NOTEQUAL_VALUE;
				static const String OPERATOR_GREATHERTHAN_VALUE;
				static const String OPERATOR_LESSTHAN_VALUE;
				static const String OPERATOR_GREATHEREQUALTHAN_VALUE;
				static const String OPERATOR_LESSEQUALTHAN_VALUE;

				static const String LOGICALOPERATOR_AND_VALUE;
				static const String LOGICALOPERATOR_OR_VALUE;
				static const String LOGICALOPERATOR_NOT_VALUE;

    			void make( String &sStatement );


				void setRetrieveParameter(RetrieveParameter* retrieve) { retrieveParameter=retrieve;}

				bool getResult() { return bResult;}

			private:
				String sLeftParameter;
				String sRightParameter;
				int iLogicalOperator;
				int iOperator;
				bool bResult;

				String assignParameter(String sValue);

				RetrieveParameter* retrieveParameter;

		};
	}
}
#endif


