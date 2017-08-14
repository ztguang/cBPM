#ifndef _DATABASE_FILESYSTEM_CONNECTION_H_
#define _DATABASE_FILESYSTEM_CONNECTION_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"
using namespace bOS::XML;

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "Connection.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace DataBase
		{
			class ENGINE_API FileSystemConnection : public Connection
			{
				public:

					FileSystemConnection();
					FileSystemConnection( XMLNode* node );

					virtual ~FileSystemConnection();

					//XMLObject
					void init();
					bool init(XMLNode*);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					String getProcessTemplatesFolder() { return this->getProcessTemplatesValue();}
					String getProcessInstancesFolder() { return this->getProcessInstancesValue();}
					String getResultTypeFile() { return this->getDataTypesValue();}
					String getServicesFile() { return this->getServicesValue();}
					String getUsersFile() { return this->getUsersValue();}
					String getRolesFile() { return this->getRolesValue();}
					String getApplicationsFile() { return this->getApplicationsValue();}
					String getEventsDefinitionFile() { return this->getEventsValue();}
					String getOccurredEventsFile() { return this->getOccurredEventsValue();}
					String getWaitingEventsFile() { return this->getWaitingEventsValue();}
					String getCheckListFolder() { return this->getCheckListValue();}
					String getFormsFolder() { return this->getFormsValue();}

			private:

			};

			class ENGINE_API XMLFileSystemConnection
			{
			public:
				static String MAIN_NODE;

			private:
				
				friend class FileSystemConnection;
			};
		}
	}
}

#endif //_DATABASE_FILESYSTEM_CONNECTION_H_
