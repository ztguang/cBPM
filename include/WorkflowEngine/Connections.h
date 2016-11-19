#ifndef _DATABASE_CONNECTIONS_H_
#define _DATABASE_CONNECTIONS_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"
using namespace bOS::XML;

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "Connection.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace DataBase
		{
			class ENGINE_API Connections : public XMLObjectSet
			{
				public:

					Connections();
					Connections( XMLNode* node );

					virtual ~Connections();

					void init();
					bool init(bOS::XML::XMLNode*);

					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					Connection* getPrimary();


				private:

			};

			class ENGINE_API XMLConnections
			{
			public:
				static String MAIN_NODE;

			private:


				friend class Connections;
			};
		}
	}
}

#endif //_DATABASE_CONNECTIONS_H_