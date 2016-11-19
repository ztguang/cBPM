#ifndef _XML_DATA_XMLOBJECT_H_
#define _XML_DATA_XMLOBJECT_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSFile.h"

#include "bOSXMLNode.h"

namespace bOS
{
	namespace XML
	{
		namespace Data
		{
			class BOS_API XMLObject 
			{
			public:
				XMLObject();
				XMLObject(bOS::XML::XMLNode* node);
				XMLObject(const char* acNode);

				virtual ~XMLObject();

				virtual void init();
				bool init(bOS::XML::XMLNode*);
				bool init(const char* acXML);
				bool init(bOS::IO::File& file);
				
				//iHow is useful for creating different type of XML.
				String getXMLString(unsigned int iHow);

				virtual bool parse(bOS::XML::XMLAttribute*) = 0;
				virtual bool parse(bOS::XML::XMLNode*) = 0;
				virtual bOS::XML::XMLNode* getXMLNode(unsigned int iHow) = 0;
				virtual bool isValid() = 0;

			protected:
				
			};
		}
	}
}

#endif //_XML_DATA_XMLOBJECT_H_