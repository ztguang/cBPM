#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "DataType.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowDataTypes
		{
			class ENGINE_API DataTypes : public XMLObjectSet
			{
			public:

				DataTypes();
				DataTypes(bOS::XML::XMLNode*);
				virtual ~DataTypes();

				void init();
				bool init(bOS::XML::XMLNode*node);
				//bool init(bOS::IO::File& file);     //ztg delete
				bool init(bOS::IO::File file);

				bool parse(bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				DataType* getDataType ( const String& sKey);

			private:

			};

			class ENGINE_API XMLDataTypes
			{
			public:
				static String MAIN_NODE;
			};

			class ENGINE_API SQLDataTypes
			{
			public:
				static String TABLE_NAME;
			};
		}
	}
}

#endif //_DATA_TYPES_H_
