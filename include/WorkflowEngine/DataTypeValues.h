#ifndef _DATATYPE_VALUES_H_
#define _DATATYPE_VALUES_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "DataTypeValue.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowDataTypes
		{
			class ENGINE_API DataTypeValues : public XMLObjectSet
			{
			public:

				DataTypeValues();
				DataTypeValues(bOS::XML::XMLNode*);
				virtual ~DataTypeValues();
				
				void init();
				bool init(const char* acXML);
				bool init(bOS::XML::XMLNode*node);
				bool parse(bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				DataTypeValue* getValue(String sKey);

			private:

			};

			class ENGINE_API XMLDataTypeValues
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_USERS_DATAMODEL_H_
