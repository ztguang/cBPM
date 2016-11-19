#include "CommonDefines.h"

#include "Attributes.h"
using namespace DataManager::Panorama::WorkflowRelevantData;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::SQL;

using namespace DataManager::Panorama::WorkflowProcesses;

Attributes::Attributes() : XMLObjectSet(), SQLTable(false), ActivityComponent()
{
	this->init();
}

Attributes::Attributes(bOS::XML::XMLNode* node ) : XMLObjectSet(), SQLTable(false), ActivityComponent()
{
	XMLObjectSet::init(node);
}

Attributes::~Attributes()
{
}

void Attributes::init()
{
	XMLObjectSet::init();
}
bool Attributes::init(bOS::XML::XMLNode* node)
{
	return XMLObjectSet::init (node);
}

bool Attributes::init(const char* acXML)
{
	return XMLObjectSet::init(acXML);
}

Attribute* Attributes::get(const char* acName)
{
	Attribute attribute;
	attribute.setName ( acName);

	CollectionEntry* entry = (CollectionEntry*)&attribute;

	Attribute* attrib2Ret = (Attribute*)XMLObjectSet::get(entry);

	return attrib2Ret;
}

Attribute* Attributes::add(Attribute& attrib)
{
	Attribute* attribute=NULL;
	if ( attrib.getName().length() > 0 ) 
	{
		attribute = get(attrib.getName().c_str());

		if ( attribute == NULL ) 
		{
			attribute = new Attribute();
			attribute->setName( attrib.getName() );
			attribute->setValue (attrib.getValue() );
			attribute->setType( attrib.getType() );
			attribute->setDirection(attrib.getDirection());

			XMLObjectSet::add ((CollectionEntry*) attribute);
		}
		else
		{
			//TODO: Mutex???
			attribute->setValue( attrib.getValue() );
		}
	}

	return attribute;
}

Attribute* Attributes::add(const char* acName, const char* acType)
{
	Attribute* attribute = new Attribute();
	attribute->setName (acName);
	attribute->setType (acType);

	XMLObjectSet::add ((CollectionEntry*) attribute);

	return attribute;
}

void Attributes::add(Attributes& vAttribs)
{
	unsigned int uiSize = vAttribs.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Attribute* attribute = (Attribute*)vAttribs.at(i);
		add(*attribute);
	}
}

void Attributes::assign(Attributes& vAttribs)
{
	unsigned int uiSize = vAttribs.size();
	Attribute* attribute = NULL;
	Attribute* attrib = NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		attrib = (Attribute*)vAttribs.at(i);
		attribute = new Attribute();
		attribute->setName( attrib->getName() );
		attribute->setValue (attrib->getValue() );
		attribute->setType( attrib->getType() );
		attribute->setDirection(attrib->getDirection());

		XMLObjectSet::append((CollectionEntry*) attribute);
	}
}

void Attributes::updateAttributes(Attributes& vAttribs)
{
	unsigned int uiSize = vAttribs.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Attribute* attribute = (Attribute*)vAttribs.at(i);

		Attribute* attr2Update = this->get( attribute->getName().c_str() );

		if (attr2Update != NULL) 
		{
			attr2Update->setValue ( attribute->getValue() ) ;
		}
	}
}

bool Attributes::remove(const char* acName)
{
	Attribute attribute;
	attribute.setName ( acName);

	CollectionEntry* entry = (CollectionEntry*)&attribute;
	return XMLObjectSet::remove(entry);
}

bool Attributes::parse(bOS::XML::XMLNode* node )
{
	if ( strcmp(node->getName(), XMLAttribute::MAIN_NODE.c_str() ) == 0)
	{
		Attribute* attribute = new Attribute(node);
		XMLObjectSet::add((CollectionEntry*)attribute);
	}
	else
		return false;

	return true;
}

bOS::XML::XMLNode* Attributes::getXMLNode(unsigned int iHow)
{
	bOS::XML::XMLNode* root= new bOS::XML::XMLNode( XMLAttributes::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	Attribute* attribute=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		attribute = (Attribute*)(this->at(i));
		root->addNode( attribute->getXMLNode(iHow) );
	}
    
    return root;
}

void Attributes::setProcessId(const char* _ProcessId)
{
	unsigned int iSize = this->size();
	for ( unsigned int i=0; i<iSize;i++)
	{
		Attribute* attribute= (Attribute*)(this->at(i));
		attribute->setProcessId(_ProcessId);
	}

	ActivityComponent::setProcessId ( _ProcessId);
}

void Attributes::setActivityId(const char* acId)
{
	unsigned int iSize = this->size();
	for ( unsigned int i=0; i<iSize;i++)
	{
		Attribute* attribute= (Attribute*)(this->at(i));
		attribute->setActivityId(acId);
	}

	ActivityComponent::setActivityId ( acId);
}

bool Attributes::parse(bOS::SQL::ResultSetRecord* record)
{
	Attribute* attribute = new Attribute();
	attribute->parse(record);

	XMLObjectSet::add ((CollectionEntry*) attribute);

	return true;
}

void Attributes::addSQLCommands(SQLCommands& vCommands, int operation)
{
	if ( operation == SQLCommand::SELECT )
	{
		SQLTable::addSQLCommands (vCommands, operation);
	}
	else
	{
		unsigned int iSize = this->size();
		for ( unsigned int i=0; i<iSize;i++)
		{
			Attribute* attribute = (Attribute*)(this->at(i));
			attribute->addSQLCommands(vCommands, operation);
		}
	}
}