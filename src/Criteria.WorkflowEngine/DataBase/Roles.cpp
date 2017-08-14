#include "CommonDefines.h"

#include "Roles.h"
using namespace DataManager::Panorama::WorkflowParticipantsData;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

Roles::Roles() : XMLObjectSet()
{
	this->init();
}

Roles::Roles(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Roles::~Roles()
{
}

void Roles::init()
{
	XMLObjectSet::init();
}

bool Roles::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

//bool Roles::init(bOS::IO::File& file)     //ztg delete
bool Roles::init(bOS::IO::File file)
{
	return XMLObjectSet::init(file);
}

bool Roles::init(const char* acXML)
{
	return XMLObjectSet::init(acXML);
}

bool Roles::parse(XMLAttribute* attribute)
{
	return false;
}

bool Roles::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLRole::MAIN_NODE.c_str()) )
    {
		Role* role = new Role(node);
		this->add((CollectionEntry*)role);
    }
	else
		return false;

	return true;
}

XMLNode* Roles::getXMLNode(unsigned int iHow)
{
	//TODO:Collection::Lock locker(*this);

	XMLNode* root = new XMLNode( XMLRoles::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->nots_size();
	Role* role=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		role = (Role*)(this->nots_at(i));
		root->addNode( role->getXMLNode(iHow) );
	}

    return root;
}


bool Roles::getRolesByUser(const char* acUser, Roles* roles)
{
	//TODO:Collection::Lock locker(*this);

	Role* role2ex = NULL;
	unsigned int uiSize = this->nots_size();
	bool bRet = false;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		role2ex= (Role*)this->nots_at(i);

		Users& users = role2ex->getUsers();

		if ( users.checkUser (acUser) )
		{
			bRet = roles->addRole(role2ex->getXMLString (0).c_str());
			if ( !bRet )
				return false;
		}
	}

	return bRet;
}

bool Roles::getRole(Role* role)
{
	assert(role != NULL );

	CollectionEntry* entry = (CollectionEntry*)role;
	CollectionEntry* entry2Ret = Collection::get(entry);

	if ( entry2Ret == NULL )
		return false;

	//TODO: User Copy-Constructor to develop.
	Role* role2Ret = (Role*)entry2Ret;

	XMLNode* node = role2Ret->getXMLNode(0);
	bool bRet = role->init (node);
	delete node;

	return bRet;
}

bool Roles::addRole(const char* acRole)
{
	Role* role2Add = new Role(acRole);
	return this->add((CollectionEntry*)role2Add);
}

bool Roles::updateRole(const char* acRoleKey)
{
	Role* role2Update = new Role(acRoleKey);
	return this->update((CollectionEntry*)role2Update);
}

bool Roles::deleteRole(const char* acRoleKey)
{
	Role role;
	role.setKey(acRoleKey);

	return  this->remove((CollectionEntry*)(&role));
}

bool Roles::checkRole(const char* acRoleKey)
{
	Role role;
	role.setKey(acRoleKey);

	return this->getRole(&role);
}

bool Roles::checkRoles(Roles* roles)
{
	Role* role = NULL;
	unsigned int uiSize = roles->nots_size();
	bool bRet = false;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		role= (Role*)roles->nots_at(i);

		if ( this->checkRole(role->getKey().c_str()) )
			return true;
	}

	return false;
}
