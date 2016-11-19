#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#define FILE_TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"
#include "ItemInterface.h"

namespace WorkflowEngine
{
	namespace Idioma
	{
		class Parameter;

		enum ParamType
		{
			PARAM_IN,
			PARAM_OUT,
			PARAM_INOUT 
		};

		class ENGINE_API Parameter : public ItemInterface
		{
    		public:
		
				Parameter(ParamType pType, String &sParamName) : ItemInterface (SUBITEM_PARAM) 
				{
					_type = pType; 
					_name = sParamName;
				}
			
				virtual ~Parameter() 
				{
				}

				ParamType getType() 
				{ 
					return _type;
				}

				String getName() 
				{ 
					return _name;
				}
			
				String getStatement();

				static const String DELIMITER_INPUT_BEGIN;
				static const String DELIMITER_INPUT_END;
				static const String DELIMITER_OUTPUT_BEGIN;
				static const String DELIMITER_OUTPUT_END;
				static const String DELIMITER_INPUTOUTPUT_BEGIN;
				static const String DELIMITER_INPUTOUTPUT_END;

    		private:
		
				ParamType _type;
			
				String _name;
		};

		typedef std::vector<Parameter *> ParamList;
		typedef ParamList::iterator ParamListIterator;

	}
}

#endif //_EVALUATOR_PARAMETER_H_

