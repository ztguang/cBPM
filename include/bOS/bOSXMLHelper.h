#ifndef __BOS_XML_XMLHELPER_H__
#define __BOS_XML_XMLHELPER_H__

//TO_BE_EXPORTED

//namespace xercesc_3_0     //ztg delete
namespace xercesc_3_1
{
    class DOMDocument;
	class DOMNode;
};

namespace bOS
{
    namespace XML
    {
		class XMLNode;

        class BOS_API XMLHelper
        {
            public:

				static void initialize();
				static void terminate();

                static XMLNode* parseFromFile(const char* acFile);
                static XMLNode* parseFromString(const char* acXML);

                static void saveToFile(const char* acFile, XMLNode* root );

            private:

                static XMLNode* parse(const char* acXML);
				static XMLNode* parse(xercesc_3_1::DOMNode*);
        };
    }
};

#endif
