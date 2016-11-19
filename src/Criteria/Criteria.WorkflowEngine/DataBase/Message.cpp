#include "CommonDefines.h"

#include "Message.h"
using namespace DataManager::Panorama::WorkflowProcesses;


#include "bOSXMLException.h" 

using namespace bOS::XML;
#include "Tracer.h"

Message::Message() : XMLObject(), SQLTable(true), ProcessComponent()
{
	this->init();
}

Message::Message(XMLNode* root) : XMLObject(), SQLTable(true), ProcessComponent()
{
	XMLObject::init(root);
}

Message::~Message()
{
}

void Message::init()
{
	sId="";
	sFromActivity="";
	sToActivity="";
	parameters.init();
}

bool Message::parse (XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName() ,XMLMessage::ID_ATTRIBUTE.c_str() ) == 0 )
	{
		sId=attribute->getValue();
	}
	else if ( strcmp(attribute->getName() ,XMLMessage::FROM_ATTRIBUTE.c_str() ) == 0 )
	{
		sFromActivity = attribute->getValue();
	}
	else if ( strcmp(attribute->getName() ,XMLMessage::TO_ATTRIBUTE.c_str() ) == 0 )
	{
		sToActivity = attribute->getValue();
	}
	else
		return false;
	
	return true;
}

bool Message::parse(XMLNode* node )
{
	if ( !strcmp(node->getName(),Common::XMLExtendedAttributes::MAIN_NODE.c_str()) )
    {
		parameters.init(node);
    }

	else
		return false;

	return true;
}

XMLNode* Message::getXMLNode(unsigned int iHow)
{
    XMLNode* root = new XMLNode( XMLMessage::MAIN_NODE.c_str(), "" );

	root->addAttribute ( new XMLAttribute ( XMLMessage::ID_ATTRIBUTE.c_str(), sId) );
	root->addAttribute ( new XMLAttribute ( XMLMessage::FROM_ATTRIBUTE.c_str(), sFromActivity) );
	root->addAttribute ( new XMLAttribute ( XMLMessage::TO_ATTRIBUTE.c_str(), sToActivity) );
	
	root->addNode( parameters.getXMLNode(0) );

    return root;
}

bool Message::isValid()
{
    if ( sFromActivity.length()  == 0 )
        return false;
        
    if ( sFromActivity .length() ==  0 )
        return false;
        
    return true;
}


DataManager::Panorama::Common::ExtendedAttributes& Message::getParameters()
{
	return parameters;
}

/***************************************************************/
const char* Message::acGetTableName()
{
	return SQLMessage::TABLE_NAME.c_str();
}

void Message::setRecord(bOS::SQL::ResultSetRecord& record)
{
	record.clear();

	//TODO: Sostituire con il valore string anzichè numerico.
	record.add ( new bOS::SQL::ResultSetField(SQLMessage::ID_FIELD.c_str(), this->sId));
	record.add ( new bOS::SQL::ResultSetField(SQLMessage::FROM_FIELD.c_str(), this->sFromActivity));
	record.add ( new bOS::SQL::ResultSetField(SQLMessage::TO_FIELD.c_str(), this->sToActivity));
	record.add ( new bOS::SQL::ResultSetField(SQLMessage::ATTRIBUTES_FIELD.c_str(), this->getParameters().getXMLString (0)));

	ProcessComponent::setRecord ( record);
}

String Message::acGetWhere()
{
	return "";
}

bool Message::parse(bOS::SQL::ResultSetRecord* record)
{
	return SQLTable::parse (record);
}

bool Message::parse(bOS::SQL::ResultSetField* field)
{
	CM_CODEBLOCK(parse_field)

	bool bRet = true;

	try
	{
		if ( !strcmp(field->sName.c_str(), SQLMessage::ID_FIELD.c_str()) )
		{
			sId = field->sValue.getData();
		}
		else if ( !strcmp(field->sName.c_str(), SQLMessage::FROM_FIELD.c_str()) )
		{
			sFromActivity  = field->sValue.getData();
		}
		else if ( !strcmp(field->sName.c_str(), SQLMessage::TO_FIELD.c_str()) )
		{
			sToActivity = field->sValue.getData();
		}
		else if ( !strcmp(field->sName.c_str(), SQLMessage::ATTRIBUTES_FIELD.c_str()) )
		{
			this->parameters.init(field->sValue.getData());
		}
		else 
			bRet = ProcessComponent::parse(field);
	}
	catch ( bOS::XML::XMLException& xmlErr )
	{
		CM_TRACE_ERROR("Impossible to parse Field[" << field->sName << "] Value[" << field->sValue.getData() << "].Err[" << xmlErr.getMessage() << "]")
		bRet = false;
	}
	return bRet;
}