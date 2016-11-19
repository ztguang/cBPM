#ifndef _BOS_XML_DATA_OBJECT_SET_H_
#define _BOS_XML_DATA_OBJECT_SET_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSFile.h"

#include "bOSXMLObject.h"

#include "bOSCollection.h"

namespace bOS
{
	namespace XML
	{
		namespace Data
		{
			class BOS_API XMLObjectSet : public XMLObject, public bOS::Collections::Collection
			{
			public:
				XMLObjectSet();
				XMLObjectSet(bOS::XML::XMLNode* node);
				XMLObjectSet(const char* acNode);

				virtual ~XMLObjectSet();

				virtual void init();
				bool init(bOS::XML::XMLNode*);
				bool init(const char* acXML);

				//ztg alter
				//bool init(bOS::IO::File& file);
				//bool addFile(bOS::IO::File& file);
				bool init(bOS::IO::File file);
				bool addFile(bOS::IO::File file);

				virtual bool parse(bOS::XML::XMLAttribute*) = 0;
				virtual bool parse(bOS::XML::XMLNode*) = 0;

				virtual bOS::XML::XMLNode* getXMLNode(unsigned int iHow) = 0;

				virtual bool isValid() = 0;

			protected:

				//usefuls methods for protected access to collection from not atomic operation.
				void lock();
				void unlock();

			};
		}
	}
}

#endif //_BOS_XML_DATA_OBJECT_SET_H_
