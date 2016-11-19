#include "CommonDefines.h"

#include "Activities.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::SQL;

Activities::Activities() : XMLObjectSet(), SQLTable(false), ProcessComponent()
{
	this->init();
}

Activities::Activities(bOS::XML::XMLNode* node ) : XMLObjectSet(), SQLTable(false), ProcessComponent()
{
	XMLObjectSet::init(node);
}

Activities::~Activities()
{
}

void Activities::init()
{
	XMLObjectSet::init();
}
bool Activities::init(bOS::XML::XMLNode* node)
{
	return XMLObjectSet::init (node); 
}

bool Activities::init (const char* acXML)
{
	return XMLObjectSet::init (acXML);
}

bool Activities::parse(bOS::XML::XMLNode* node )
{
	if ( strcmp(node->getName(), XMLActivity::MAIN_NODE.c_str() ) == 0)
	{
		Activity* activity = new Activity(node);
		XMLObjectSet::add((CollectionEntry*)activity);
	}
	else
		return false;

	return true;
}

bOS::XML::XMLNode* Activities::getXMLNode(unsigned int iHow)
{
	bOS::XML::XMLNode* root= new bOS::XML::XMLNode( XMLActivities::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	Activity* activity=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		activity = (Activity*)(this->at(i));
		root->addNode( activity->getXMLNode(iHow) );
	}
    
    return root;
}

bool Activities::remove(String& _Name)
{
	Activity activity;
	activity.setName (_Name.c_str());
	CollectionEntry* entry = (CollectionEntry*)&activity;

	return bOS::Collections::Collection::remove (entry);
}

Activity* Activities::get(String& _Name)
{
	Activity activity;
	activity.setName (_Name.c_str());
	CollectionEntry* entry = (CollectionEntry*)&activity;

	Activity* activity2Ret = (Activity*)bOS::Collections::Collection::get(entry);

	return activity2Ret;
}

Activity* Activities::getActivity(Activity::ActivityType activityType)
{
	unsigned int uiSize= this->size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Activity* activity = (Activity*)this->at(i);
		if ( activity->getType() == activityType )
		{
			return activity;
		}
	}

	return NULL;
}

Activity* Activities::getStartActivity()
{
	return this->getActivity (Activity::START);
}

ActivitiesList Activities::getActivities(String sStatus, String sOwner)
{
	//TODO: Collection::Lock loker(*this);
	ActivitiesList activitiesList;

	unsigned int uiSize= this->nots_size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Activity* activity = (Activity*)this->nots_at(i);
		if ( ( (sStatus == "")|| ( activity->getStatus() == sStatus ) ) && 
		     ( (sOwner == "") || ( activity->getOwner() == sOwner ) ) )
		{
			activitiesList.push_back(activity->getActivityName());
		}
	}

    return activitiesList;
}

void Activities::addActivities(Activities& vActivities)
{
	int iSize = vActivities.size();
	for ( int i=0; i<iSize;i++)
	{
		Activity* activity = (Activity*)vActivities.at(i);

		bOS::XML::XMLNode* node = activity->getXMLNode(0);
		Activity* newActivity = new Activity(node);
		delete node;

		this->add((CollectionEntry*)newActivity);
	}
}

void Activities::addActivity(Activity& activity)
{
	//TODO: Activity copy-constructor to develop.
	bOS::XML::XMLNode* node = activity.getXMLNode(0);
	Activity* newActivity = new Activity(node);
	delete node;
	this->add((CollectionEntry*)newActivity);
}


void Activities::setProcessId(const char* _ProcessId)
{
	ProcessComponent::setProcessId (_ProcessId);
	unsigned int iSize = this->size();
	for ( unsigned int i=0; i<iSize;i++)
	{
		Activity* activity = (Activity*)(this->at(i));
		activity->setProcessId(_ProcessId);
	}
}

bool Activities::parse(bOS::SQL::ResultSetRecord* record)
{
	CM_CODEBLOCK(Activities::parseRecord)

	bool bRet = true;
	Activity* activity = new Activity();

	if ( activity->parse( record) )
	{
		XMLObjectSet::add( (CollectionEntry*) activity);

	}
	else
	{
		delete activity;
		bRet=false;
	}

	return bRet;
}

void Activities::addSQLCommands(SQLCommands& vCommands, int operation)
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
			Activity* activity = (Activity*)(this->at(i));

			activity->addSQLCommands(vCommands, operation);
		}
	}
}