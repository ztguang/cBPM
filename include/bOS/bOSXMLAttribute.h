#ifndef __BOS_XML_XMLATTRIBUTE_H__
#define __BOS_XML_XMLATTRIBUTE_H__

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSCollectionEntry.h"

namespace bOS
{
    namespace XML
    {
		class BOS_API XMLAttribute : public bOS::Collections::CollectionEntry 
        {
            public:

                XMLAttribute();

				XMLAttribute( const char* acName, const char* acValue);
				XMLAttribute( const char* acName, const String& sValue);
				XMLAttribute( const char* acName, long lValue);
				XMLAttribute( const char* acName, int iValue);
				XMLAttribute( const char* acName, unsigned int iValue);

                virtual ~XMLAttribute();

				//bOS::Collections::CollectionEntry
				bool equalTo(bOS::Collections::CollectionEntry*);

                const char* getName();
				unsigned int getUIntValue();
				int getIntValue();
				long getLongValue();
                const char* getValue();

                void setName( const char* acName );
                void setValue( const char* acValue );

            protected:

            private:

                String      sName;
                String      sValue;
        };
    }
};

#endif //__BOS_XML_XMLATTRIBUTE_H__


