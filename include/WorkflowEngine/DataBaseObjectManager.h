#ifndef _DATABASE_OBJECTMANAGER_H_
#define _DATABASE_OBJECTMANAGER_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
using namespace bOS::XML;

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace DataBase
		{
			class ENGINE_API DataBaseObjectManager : public XMLObjectSet
			{
				public:

					DataBaseObjectManager();
					DataBaseObjectManager( XMLNode* node );

					virtual ~DataBaseObjectManager();

					//XMLObjectSet
					void init();
					bool init(bOS::XML::XMLNode*);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

				private:

			};

			class ENGINE_API XMLDataBaseObjectManager
			{
			public:
				static String MAIN_NODE;

			private:

				friend class ObjectManager;
			};
		}
	}
}

#endif //_DATABASE_OBJECTMANAGER_H_