#ifndef __KEYWORD_H__
#define __KEYWORD_H__

#define FILE_TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"
#include "ItemInterface.h"

namespace WorkflowEngine
{
	namespace Idioma
	{
		class ENGINE_API Keyword : public ItemInterface
		{
    		public:
		
				Keyword( String sText ) : ItemInterface (ITEM_KEYWORD) 
				{
					_text = sText;
				}
			
				virtual ~Keyword() 
				{
				}

				String getStatement() 
				{ 
					return DELIMITER_BEGIN + _text + DELIMITER_END;
				}

				String getText() 
				{
					return _text;
				}

				static const String DELIMITER_BEGIN;
				static const String DELIMITER_END;

    		private:
		
				String _text;
		};
	}
}

#endif 


