#ifndef _DATABASES_DATABASE_H_
#define _DATABASES_DATABASE_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLFile.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "Connections.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace DataBase
		{
			class ENGINE_API DataBase : public XMLFile
			{
			public:
				DataBase();
				virtual ~DataBase();

				void init();
				bool parse(bOS::XML::XMLAttribute*);
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				Connections& getConnections() { return vConnections;}

			private:

				Connections vConnections;
				

			};

			class ENGINE_API XMLDataBase 
			{
			public:
				static String MAIN_NODE;

			};
		}
	}
}

#endif //_DATABASES_DATABASE_H_