#include "CommonDefines.h"

#include "Users.h"
using namespace DataManager::Panorama::WorkflowParticipantsData;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

Users::Users() : XMLObjectSet()
{
	this->init();
}

Users::Users(XMLNode* node ) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Users::~Users(void)
{
}

void Users::init()
{
	XMLObjectSet::init();
}

bool Users::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

//bool Users::init(bOS::IO::File& file)     //ztg delete
bool Users::init(bOS::IO::File file)
{
	return XMLObjectSet::init(file);
}

bool Users::init(const char* acXML)
{
	return XMLObjectSet::init(acXML);
}

bool Users::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLUser::MAIN_NODE.c_str() ) )
    {
		User* user = new User(node);
		this->add((CollectionEntry*)user);
    }
	else
	{
		return false;
	}

	return true;
}

bool Users::parse(XMLAttribute* attribute)
{
	return true;
}

bool Users::isValid()
{
	return true;
}

XMLNode* Users::getXMLNode(unsigned int iHow)
{
	//TODO: Collection::Lock locker(*this);

    XMLNode* root= new XMLNode( XMLUsers::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->nots_size();
	User* user=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		user = (User*)(this->nots_at(i));
		root->addNode( user->getXMLNode(iHow) );
	}

    return root;
}


bool Users::getUser (User* user)
{
	assert(user != NULL );

	CollectionEntry* entry = (CollectionEntry*)user;
	CollectionEntry* entry2Ret = Collection::get(entry);

	if ( entry2Ret == NULL )
		return false;

	//TODO: User Copy-Constructor to develop.
	User* user2Ret = (User*)entry2Ret;

	XMLNode* node = user2Ret->getXMLNode(0);
	bool bRet = user->init(node);
	delete node;
	return bRet;
}

bool Users::addUser(const char* acUser)
{
	User* user2Add = new User(acUser);
	return this->add((CollectionEntry*)user2Add);
}

bool Users::updateUser(const char* acUser)
{
	User* user2Update = new User(acUser);
	return this->update((CollectionEntry*)user2Update);
}

bool Users::deleteUser(const char* acUserKey)
{
	User user;
	user.setKey(acUserKey);

	return  this->remove((CollectionEntry*)(&user));
}

bool Users::checkUser(const char* acUserKey)
{
	User user;
	user.setKey(acUserKey);

	return this->getUser(&user);
}
