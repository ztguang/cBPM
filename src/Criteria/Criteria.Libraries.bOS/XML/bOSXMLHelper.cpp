#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

#include "bOSFileSystem.h"

#include "bOSFileSystemException.h"

#include "bOSXMLHelper.h"
#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"
#include "bOSXMLException.h"

//XERCES Includes
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

void bOS::XML::XMLHelper::initialize()
{
    try
    {
		xercesc_3_1::XMLPlatformUtils::Initialize();
    }
	catch (const xercesc_3_1::XMLException& xmlErr)
    {
		//bOS::XML::XMLStringTranscoded transcoded(xmlErr.getMessage());
		throw bOS::XML::XMLException( xercesc_3_1::XMLString::transcode(xmlErr.getMessage()) );
    }
}

void bOS::XML::XMLHelper::terminate()
{
    try
    {
        xercesc_3_1::XMLPlatformUtils::Terminate();
    }
	catch (const xercesc_3_1::XMLException& xmlErr)
    {

        throw bOS::XML::XMLException( xercesc_3_1::XMLString::transcode(xmlErr.getMessage()) );
    }
}

bOS::XML::XMLNode* bOS::XML::XMLHelper::parseFromFile(const char* acFile )
{
	assert(acFile != NULL);

	/*
	ifstream strmFile(acFile, ios::in );
	if ( strmFile.fail() )
	{
		throw bOS::XML::XMLException(XML_FILE_NOTFOUND);
	}

    String sRow;
    StringBuffer sFile;

    while( !strmFile.eof() )
    {
        getline(strmFile, sRow);
        sFile.append (sRow);
    }
	strmFile.close();
	*/

	StringBuffer sFileBody;
	try
	{
		bOS::IO::FileSystem::getStringFile (acFile, sFileBody);
	}
	catch ( bOS::Exception::FileSystemException& fsErr)
	{
		throw bOS::XML::XMLException(fsErr.getMessage() );
	}

    return bOS::XML::XMLHelper::parseFromString(sFileBody.getData());
}

bOS::XML::XMLNode* bOS::XML::XMLHelper::parseFromString(const char* acXML)
{
	assert(acXML != NULL );
	return bOS::XML::XMLHelper::parse(acXML);
}

void bOS::XML::XMLHelper::saveToFile( const char* acFile, bOS::XML::XMLNode* root )
{
	try
	{
		bOS::IO::FileSystem::saveStringFile(acFile, root->getXMLText(true));
	}
	catch ( bOS::Exception::FileSystemException& fsErr)
	{
		throw bOS::XML::XMLException(fsErr.getMessage() );
	}
}

bOS::XML::XMLNode* bOS::XML::XMLHelper::parse(const char* acXML)
{
    xercesc_3_1::XercesDOMParser parser;
    parser.setValidationScheme( xercesc_3_1::XercesDOMParser::Val_Auto );
    parser.setDoNamespaces( false );

	unsigned int uiLen = strlen(acXML);

	XMLCh id = 0;
	xercesc_3_1::MemBufInputSource in((const Byte* const) acXML, uiLen, &id);

    try
    {
        parser.parse( in );
    }
	catch (const xercesc_3_1::XMLException& xmlErr)
    {

        throw bOS::XML::XMLException( xercesc_3_1::XMLString::transcode(xmlErr.getMessage()) );
    }
    catch (const xercesc_3_1::DOMException& domErr)
    {

       throw bOS::XML::XMLException( xercesc_3_1::XMLString::transcode(domErr.msg ) );
    }
    catch (...)
    {
        throw bOS::XML::XMLException( XML_UNKNOWN_ERROR );
    }

    xercesc_3_1::DOMDocument* rootDocument = parser.getDocument();
	if ( rootDocument == NULL )
	{
		throw bOS::XML::XMLException( XML_DOCUMENT_NOTFOUND );
	}

	xercesc_3_1::DOMNode* domNode = (xercesc_3_1::DOMNode*)rootDocument->getDocumentElement();
	if ( domNode == NULL )
	{
		throw bOS::XML::XMLException( XML_ROOT_NOTFOUND );
	}

    bOS::XML::XMLNode* root = bOS::XML::XMLHelper::parse( domNode );

    return root;
}

bOS::XML::XMLNode* bOS::XML::XMLHelper::parse(xercesc_3_1::DOMNode* domNode )
{
	assert(domNode != NULL);

	bOS::XML::XMLNode* node = new bOS::XML::XMLNode();
    try
    {
		{
			node->setName(xercesc_3_1::XMLString::transcode(domNode->getNodeName()));
		}

	    if (domNode->hasChildNodes())
        {
            xercesc_3_1::DOMNode* rootNode=domNode->getFirstChild();
            short siType = rootNode->getNodeType();
            switch ( siType )
            {
            case xercesc_3_1::DOMNode::TEXT_NODE:
            case xercesc_3_1::DOMNode::CDATA_SECTION_NODE:
				{
					node->setValue( xercesc_3_1::XMLString::transcode(rootNode->getNodeValue()) );
				}
                break;
            }
        }
        if ( domNode->getNodeType() == xercesc_3_1::DOMNode::ELEMENT_NODE )
        {
            xercesc_3_1::DOMNamedNodeMap* vAttributes = domNode->getAttributes();
			xercesc_3_1::DOMNode* domAttribute=NULL;
            for (unsigned int ui = 0; ui < vAttributes->getLength(); ui++)
            {
                domAttribute = vAttributes->item(ui);

				bOS::XML::XMLAttribute* attribute = new bOS::XML::XMLAttribute();

				{
					attribute->setName(xercesc_3_1::XMLString::transcode(domAttribute->getNodeName()));
				}
				{
					attribute->setValue(xercesc_3_1::XMLString::transcode(domAttribute->getNodeValue()));
				}

                node->addAttribute(attribute);
            }
        }

        if ( domNode->hasChildNodes() )
        {
			xercesc_3_1::DOMNodeList* vNodes = domNode->getChildNodes();
            xercesc_3_1::DOMNode* nodeChild;
            for (unsigned int ui = 0; ui < vNodes->getLength(); ui++)
            {
                nodeChild = vNodes->item(ui);
                if (nodeChild->getNodeType() == xercesc_3_1::DOMNode::ELEMENT_NODE)
                {
                    bOS::XML::XMLNode* newNode = bOS::XML::XMLHelper::parse( nodeChild );
                    node->addNode( newNode );
                }
            }
        }
    }

    catch (const xercesc_3_1::DOMException& domErr)
    {
        throw bOS::XML::XMLException( xercesc_3_1::XMLString::transcode(domErr.msg ));
    }

    return node;
}

