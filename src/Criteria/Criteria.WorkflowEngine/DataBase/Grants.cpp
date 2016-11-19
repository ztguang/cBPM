#include "CommonDefines.h"

#include "Grants.h"
#include "Grant.h"
using namespace DataManager::Panorama::Common;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

Grants::Grants() : XMLObjectSet()
{
	this->init();
}

Grants::Grants(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Grants::~Grants()
{
}

void Grants::init()
{
	this->removeAll();
}

bool Grants::init(bOS::XML::XMLNode* node)
{
	return XMLObjectSet::init (node);
}

bool Grants::init(const char* acXML)
{
	return XMLObjectSet::init (acXML);
}

bool Grants::parse(XMLAttribute* attribute)
{
	return false;
}

bool Grants::parse(XMLNode* node)
{
	if ( strcmp(node->getName(),XMLGrant::MAIN_NODE.c_str()) == 0 )
	{
		Grant* grant = new Grant(node);
		XMLObjectSet::add( (CollectionEntry*)grant);
	}
	else
		return false;

	return true;
}

XMLNode* Grants::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode(XMLGrants::MAIN_NODE.c_str(), "" );
	unsigned int uiSize=this->size();
	Grant* grant=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		grant = (Grant*)(this->at(i));
		root->addNode( grant->getXMLNode(iHow) );
	}

    return root;
}

bool Grants::check (const char* acUserKey, const char* acRoleKey, const char* acGrantType )
{
	Grant* grant=NULL;

	bool bRetYes = true;
	bool bRetNo = false;

	unsigned int uiSize = this->size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		grant = (Grant*)(this->at(i));

		if ( !strcmp(grant->getType().c_str(),acGrantType) ) 
		{
			Users& users = grant->getUsers();
			Roles& roles = grant->getRoles();

			if ( grant->isEnabled() ) 
			{
				if ( (acUserKey != NULL) && (users.checkUser(acUserKey)) )
				{
					return true;
				}
				else if ( (acRoleKey != NULL) && (roles.checkRole(acRoleKey)) )
				{
					bRetYes=true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if ( (acUserKey != NULL) && (users.checkUser(acUserKey)) )
				{
					return false;
				}
				else if ( (acRoleKey != NULL) && (roles.checkRole(acRoleKey)) )
				{
					bRetNo = true;
				}
				else
				{
					bRetNo=false;
				}
			}
		}
	}

	return bRetYes && !bRetNo;
}