#ifndef __BOS_XML_XMLEXCEPTION_H__
#define __BOS_XML_XMLEXCEPTION_H__

//TO_BE_EXPORTED

#include "bOSException.h"

namespace bOS
{
    namespace XML
    {
        #define XML_INIT_ERROR          "Error during initialization of Xerces Subsystem : "
        #define XML_PARSE_ERROR         "Error during parsing XML : "
        #define XML_TREE_WALKING_ERROR  "Error during traversing the XML tree."
        #define XML_UNKNOWN_ERROR       "Unknow error during parsing. Please refer to an application administrator."
		#define XML_FILE_NOTFOUND		"Impossible to parse.File not exists."
		#define XML_ROOT_NOTFOUND		"Impossible to parse.Root Node is not retrievable." 
		#define XML_DOCUMENT_NOTFOUND	"Impossible to parse.Document is not retrievable." 

		class BOS_API XMLException : public bOS::Exception::BaseException 
        {
            public:

                XMLException(const String & message ) : BaseException( message ) {};

                XMLException() : BaseException( XML_UNKNOWN_ERROR ) {};

                XMLException( const String & message, const int lineNumber ) 
                    : BaseException(message, lineNumber) {};

                virtual ~XMLException() {};
        };
    }
}

#endif //__BOS_XML_XMLEXCEPTION_H__


