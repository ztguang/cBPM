#include "CommonDefines.h"

#include "Report.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "bOSXMLException.h"

using namespace bOS::XML;

Report::Report() : XMLObject(), SQLTable(true), ProcessComponent()
{
	this->init();
}

Report::Report(XMLNode* root) : XMLObject(), SQLTable(true), ProcessComponent()
{
	this->init(root);
}

Report::~Report()
{
}

void Report::init()
{
	sValue="";
	sDateTime="";
}

bool Report::init(bOS::XML::XMLNode*node)
{
	bool bRet = XMLObject::init(node);

	sValue = node->getValue();
	if ( sValue.length() == 0 )
	{
		sValue = node->getInnerXML();
	}

	return bRet;
}

bool Report::parse(XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName(),XMLReport::DATETIME_ATTRIBUTE.c_str()) == 0 )
	{
		sDateTime = attribute->getValue();
    }
	else
		return false;

	return true;
}

bool Report::parse(XMLNode* node)
{
	return false;
}

XMLNode* Report::getXMLNode(unsigned int iHow)
{
    XMLNode* root = new XMLNode( XMLReport::MAIN_NODE.c_str(), sValue);

	root->addAttribute( new XMLAttribute( XMLReport::DATETIME_ATTRIBUTE.c_str(), sDateTime ) );

    return root;
}

bool Report::isValid()
{
    return true;
}

/***************************************************************/
const char* Report::acGetTableName()
{
	return SQLReport::TABLE_NAME.c_str();
}

void Report::setRecord(bOS::SQL::ResultSetRecord& record)
{
	record.clear();

	//TODO: Sostituire con il valore string anzichè numerico.
	record.add ( new bOS::SQL::ResultSetField(SQLReport::DATETIME_FIELD.c_str(), sDateTime));
	record.add ( new bOS::SQL::ResultSetField(SQLReport::DESCRIPTION_FIELD.c_str(), sValue));

	ProcessComponent::setRecord ( record);
}

String Report::acGetWhere()
{
	return "";
}

bool Report::parse(bOS::SQL::ResultSetRecord* record)
{
	return SQLTable::parse (record);
}

bool Report::parse(bOS::SQL::ResultSetField* field)
{
	CM_CODEBLOCK(parse_field)

	bool bRet = true;

	try
	{
		if ( !strcmp(field->sName.c_str(), SQLReport::DATETIME_FIELD.c_str()) )
		{
			sDateTime = field->sValue.getData();
		}
		else if ( !strcmp(field->sName.c_str(), SQLReport::DESCRIPTION_FIELD.c_str()) )
		{
			sValue = field->sValue.getData();
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