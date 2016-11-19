#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringBuffer.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"
using namespace bOS::XML;

using namespace bOS::Collections;

#define SPECIAL_CODE_NUM 1
/*char vSpecialCharacter[SPECIAL_CODE_NUM] = {'<','>','&'};
String vSpecialCode[SPECIAL_CODE_NUM] = {"&lt;","&gt;", "&amp;"};
*/
char vSpecialCharacter[SPECIAL_CODE_NUM] = {'&'};
String vSpecialCode[SPECIAL_CODE_NUM] = {"&amp;"};

XMLNode::XMLNode()
{
    sName = "";
    sValue = "";
    nodeParent = (XMLNode*)NULL;
}

XMLNode::XMLNode( const char* acName, const char* acValue)
{
    sName = acName;
    sValue = acValue;
    nodeParent = (XMLNode*)NULL;
}

XMLNode::XMLNode( const char* acName, const String& _Value)
{
    sName = acName;
    sValue = _Value;
    nodeParent = (XMLNode*)NULL;
}

XMLNode::XMLNode( const char* acName, unsigned int uiValue)
{
    sName = acName;
	sValue = StringUtils::toString (uiValue);
    nodeParent = (XMLNode*)NULL;
}

XMLNode::XMLNode( const char* acName, int iValue)
{
    sName = acName;
	sValue = StringUtils::toString (iValue);
    nodeParent = (XMLNode*)NULL;
}

XMLNode::~XMLNode()
{

}

String XMLNode::getValueTranscoded(const char* acValue)
{
	StringBuffer sbValue;
	bool bRet =true;
	const char* acIndex = acValue;
	while ( (*acIndex) != 0 )
	{
		bRet = true;

		for ( unsigned int j=0; j<SPECIAL_CODE_NUM && bRet; j++) 
		{
			if ( (*acIndex) == vSpecialCharacter[j]) 
			{
				sbValue.append(vSpecialCode[j]);
				bRet=false;
			}
		}

		if ( bRet )
			sbValue.append ((*acIndex));

		acIndex++;
	}

	return sbValue.getData();
}


String XMLNode::getXMLText( bool bIndent, unsigned int uilevel )
{
    String sSeparator = NEWLINE;
    String sIndentator = "";

    if ( bIndent )
	{
		sIndentator=String(uilevel, '\t');
	}
	else
	{
        sSeparator = "";
	}

	StringBuffer sb;

    sb.append( sIndentator );
    sb.append( "<" );
	sb.append( sName.c_str() );

	//Attributes
	unsigned int uiSize = vAttributes.size();
	XMLAttribute* attribute = NULL;
	for ( unsigned int ui=0; ui<uiSize; ui++)
    {
		attribute = (XMLAttribute*)vAttributes[ui];

		sb.append( " " );
		sb.append( attribute->getName() );
		sb.append( "=\"" );

		sb.append(XMLNode::getValueTranscoded( attribute->getValue() ));

		sb.append( "\"" );
    }
	sb.append( ">" );

	
	if ( sValue.length() > 0 ) 
	{
		/*if ( strcmp(sName.c_str(), "Script") ) 
		{
			sb.append("<![CDATA[");
			sb.append (sValue );
			sb.append ("]]>");
		}
		else
		{*/
			sb.append( XMLNode::getValueTranscoded(sValue.c_str()) );
			//sb.append (sValue );
		//}
	}

	uiSize = vNodes.size();
	if ( uiSize > 0 )
	{
		sb.append( sSeparator.c_str() );
		
		//sb.append( sSeparator.c_str() );

		XMLNode* node = NULL;
		
		for ( unsigned int ui=0; ui<uiSize; ui++)
		{
			node = (XMLNode*)vNodes[ui];
			sb.append( node->getXMLText(bIndent, uilevel + 1));
		}
	
		sb.append( sIndentator.c_str() );
	}

	sb.append( "</" );
	sb.append( sName.c_str() );
	sb.append( ">" );
	sb.append( sSeparator.c_str() );

	return sb.getData();
}


String XMLNode::getInnerXML()
{
	StringBuffer sb;

	unsigned int uiSize = vNodes.size();
	XMLNode* node = NULL;
    for ( unsigned int ui=0; ui<uiSize; ui++)
    {
		node = (XMLNode*)vNodes[ui];
		sb.append( node->getXMLText());
    }

	return sb.getData();
}

XMLNode* XMLNode::getParentNode()
{
    return nodeParent;
}

void XMLNode::setParent( XMLNode* node )
{
	assert(node != NULL);
    nodeParent = node;
}

const char* XMLNode::getName()
{
    return sName.c_str();
}

const char* XMLNode::getValue()
{
    return sValue.c_str();
}

unsigned int XMLNode::getUIntValue()
{
	return bOS::CoreString::StringUtils::toInteger(sValue);
}

int XMLNode::getIntValue()
{
	return bOS::CoreString::StringUtils::toInteger(sValue);
}

long XMLNode::getLongValue()
{
	return bOS::CoreString::StringUtils::toLong (sValue);
}

void XMLNode::setName( const char* acName )
{
    sName = acName;
}

void XMLNode::setValue( const char* acValue )
{
    this->sValue = acValue;
}

void XMLNode::addAttribute( XMLAttribute* attribute )
{
    vAttributes.add(attribute);
}

bool XMLNode::removeAttribute(XMLAttribute* attribute)
{
	return vAttributes.remove(attribute);
}

XMLAttribute* XMLNode::getAttribute(const char* acName)
{
	XMLAttribute attribute;
	attribute.setName(acName);

	return (XMLAttribute*)vAttributes.get(&attribute);
}

Collection& XMLNode::getAttributes()
{
    return vAttributes;
}

void XMLNode::addNode( XMLNode* node )
{
	vNodes.add(node);
	node->setParent ( this );
}

bool XMLNode::removeNode( XMLNode* node )
{
	return vNodes.remove(node);
}

Collection& XMLNode::getNodes()
{
	return vNodes;
}

XMLNode* XMLNode::getNode( const char* acName )
{
	XMLNode* node=NULL;
	unsigned int uiSize = vNodes.size();
	for ( unsigned int ui=0; ui<uiSize; ui++)
	{
		node = (XMLNode*)vNodes.at(ui);

		if ( !strcmp(acName, node->getName()) )
		{
			return node;
		}
	}

	return NULL;
}

bool XMLNode::equalTo (CollectionEntry* entry)
{
	return false;
}

