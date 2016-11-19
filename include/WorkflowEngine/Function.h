#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#define FILE_TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"
#include "ItemInterface.h"

#include "Parameter.h"

namespace WorkflowEngine
{
	namespace Idioma
	{
		class ENGINE_API Function : public ItemInterface
		{
    		public:
		
				enum FunctionItemType
				{
					FUNCTION_NO,
					FUNCTION_NAME,
					FUNCTION_RESULT,
					FUNCTION_PARAMIN,
					FUNCTION_PARAMOUT,
					FUNCTION_PARAMINOUT
				};

				Function() : ItemInterface (ITEM_FUNCTION) 
				{
				}
			
				virtual ~Function();

    			String getStatement();

				void addFunctionName( String sFunctionName )
				{ 
					_functionName = sFunctionName;
				}
			
				void addResult( String &sResult )
				{
					_result = sResult;
				}
			
				Parameter* addParameter( ParamType eType, String sName );

				String getFunctionName() 
				{ 
					return _functionName;
				}
			
				String getResult() 
				{ 
					return _result;
				}

				static const String DELIMITER_BEGIN;
				static const String DELIMITER_END;

				static const String DELIMITER_RESULT_BEGIN;
				static const String DELIMITER_RESULT_END;

				static const String DELIMITER_FUNCTION_BEGIN;
				static const String DELIMITER_FUNCTION_END;

    			void make( String &sStatement );

				Parameter* getFirstParam( ParamListIterator& iParam );
				Parameter* getNextParam( ParamListIterator& iParam );

			private:
			
				String _functionName;
				String _result;
			
				ParamList paramList;

		};
	}
}
#endif


