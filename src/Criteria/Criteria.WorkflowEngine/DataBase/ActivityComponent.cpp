#include "CommonDefines.h"

#include "ActivityComponent.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::XML;

using namespace bOS::SQL;

ActivityComponent::ActivityComponent() : ProcessComponent()
{
	this->init();
}

ActivityComponent::~ActivityComponent()
{
}

void ActivityComponent::init()
{
	ProcessComponent::init();
	sId="";
}
bool ActivityComponent::parse(XMLNode* node)
{
	if ( ProcessComponent::parse (node) )
	{
		return true;
	}

	return false;
}

bool ActivityComponent::parse (XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName(), XMLActivityComponent::ID_ATTRIBUTE.c_str() ) == 0 )
		return true;

	return false;
}

void ActivityComponent::setXML(bOS::XML::XMLNode* node)
{
	ProcessComponent::setXML(node);

	node->addAttribute( new XMLAttribute(XMLActivityComponent::ID_ATTRIBUTE.c_str(), sId) );
}

/*****************************************/
ResultSetField* ActivityComponent::setRecord(ResultSetRecord& record)
{
	ResultSetField* field = ProcessComponent::setRecord ( record );

	field = new ResultSetField(SQLActivityComponent::ACTIVITY_ID_FIELD.c_str(), sId);
	record.add (field);

	return field;
}

String ActivityComponent::acGetWhere()
{
	StringBuffer sSql;

	sSql.append (ProcessComponent::acGetWhere() );

	/*if ( sId.length() > 0 )
	{
	*/
		sSql.append (" AND ");
		sSql.append (SQLActivityComponent::ACTIVITY_ID_FIELD);
		sSql.append("=");
		sSql.append( StringUtils::returnQuoteAndTwice(sId));
	//}

	return (char*)sSql.getData();
}

bool ActivityComponent::parse(ResultSetField* field)
{
	if ( ProcessComponent::parse (field) )
	{
		return true;
	}
	else if ( !strcmp(field->sName.c_str(),  SQLActivityComponent::ACTIVITY_ID_FIELD.c_str()) )
	{
		sId = field->sValue.getData();
	} 
	else
	{
		return false;
	}

	return true;
}

void ActivityComponent::setActivityId(const char* acId)
{
	sId = acId;
}

String& ActivityComponent::getActivityId()
{
	return sId;
}

