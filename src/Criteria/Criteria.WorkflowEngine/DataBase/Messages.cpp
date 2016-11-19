#include "CommonDefines.h"

#include "Messages.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::SQL;
using namespace bOS::XML;

Messages::Messages() :  XMLObjectSet(), SQLTable(false), ProcessComponent()
{
	this->init();
}

Messages::Messages(XMLNode* node) : XMLObjectSet(), SQLTable(false), ProcessComponent()
{
	XMLObjectSet::init(node);
}

Messages::~Messages()
{
}

void Messages::init()
{
	XMLObjectSet::init();
}

bool Messages::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool Messages::init(const char* acXML)
{
	return XMLObjectSet::init(acXML);
}

bool Messages::parse(XMLAttribute* attribute)
{
	return false;
}

bool Messages::parse(XMLNode* node)
{
	if ( strcmp(node->getName(),XMLMessage::MAIN_NODE.c_str()) == 0 )
	{
		Message* message = new Message(node);
		this->add( (CollectionEntry*)message);
	}
	else
		return false;

	return true;
}

XMLNode* Messages::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode(XMLMessages::MAIN_NODE.c_str(), "" );
	unsigned int uiSize=this->size();
	Message* message=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		message = (Message*)(this->at(i));
		root->addNode( message->getXMLNode(iHow) );
	}

    return root;
}

void Messages::addMessages(Messages& vMessages)
{
	int iSize = vMessages.size();
	for ( int i=0; i<iSize; i++)
	{
		Message* message = (Message*)vMessages.at(i);

		XMLNode* node = message->getXMLNode(0);
		Message* newMessage = new Message(node);
		delete node;
		
		add(newMessage);
	}
}

bool Messages::parse(bOS::SQL::ResultSetRecord* record)
{
	bool bRet = true;
	Message* message = new Message();

	if ( message->parse( record) )
	{
		XMLObjectSet::add( (CollectionEntry*) message);

	}
	else
	{
		delete message;
		bRet=false;
	}

	return bRet;
}

void Messages::addSQLCommands(SQLCommands& vCommands, int operation)
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
			Message* message = (Message*)(this->at(i));

			message->addSQLCommands(vCommands, operation);
		}
	}
}

bool Messages::addMessage(Message& message)
{
	Message* msg2add= new Message( message.getXMLNode(0));
	bool bRet = bOS::Collections::Collection::add((CollectionEntry*)msg2add);

	if ( !bRet )
	{
		delete msg2add;
	}

	return bRet;
}