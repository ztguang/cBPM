#ifndef _DATATYPE_VALUE_H_
#define _DATATYPE_VALUE_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "bOSCollectionEntry.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowDataTypes
		{
			class ENGINE_API DataTypeValue : public XMLObject, public bOS::Collections::CollectionEntry
			{
				public:

					DataTypeValue();
					DataTypeValue(bOS::XML::XMLNode* node );
					DataTypeValue(const char* acXML);

					virtual ~DataTypeValue();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*);

					String&	getKey() { return sKey;}
					String& getValue() { return sValue;}

					void setKey(const String& Value) { sKey=Value;}
					void setValue(const String& Value) { sValue=Value;}
			    
				private:

					String	sKey;
					String  sValue;
			};

			class ENGINE_API XMLDataTypeValue
			{
			public:
				static String MAIN_NODE;

			private:
				static String KEY_ATTRIBUTE;

				friend class DataTypeValue;
			};
		}
	}
}

#endif //_DATATYPE_VALUE_H_