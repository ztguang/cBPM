#ifndef __ITEMINTERFACE_H__
#define __ITEMINTERFACE_H__

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

namespace WorkflowEngine
{
	namespace Idioma
	{
		enum ItemType 
		{
			ITEM_NO, 
			ITEM_FREETEXT,
			ITEM_KEYWORD,
			ITEM_FUNCTION,
			ITEM_EXPRESSION,
			ITEM_CONDITION,
			SUBITEM_PARAM
		};

		class ENGINE_API ItemInterface 
		{
		public:
			ItemInterface(ItemType itemType) 
			{ 
				_itemType = itemType;
			}
		
			virtual ~ItemInterface()
			{
			}

			ItemType getType() 
			{ 
				return _itemType;
			}

			virtual String getStatement() = 0;

			static unsigned int CheckDelimiter( String sStatement, const String &sDelimiter );

			bool isLiteralValue(String sValue);
			bool isOnlyDigit(String sValue);

		private:
			
			ItemType _itemType;
		};

		typedef std::vector<ItemInterface*> ItemList;
		typedef ItemList::iterator ItemListIterator;

	}
}

#endif


