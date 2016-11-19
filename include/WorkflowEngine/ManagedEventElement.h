#ifndef _MANAGED_EVENTELEMENT_H_
#define _MANAGED_EVENTELEMENT_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObject.h"

#include "bOSDateTime.h"
using namespace bOS::Utils;

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API ManagedEventElement : public bOS::XML::Data::XMLObject
			{
			public:

				enum ManagedStatus
				{
					Managed = 1,
					UnManaged = 2,
					Managing = 4
				};

				ManagedEventElement();
				ManagedEventElement( bOS::XML::XMLNode* node );

				virtual ~ManagedEventElement();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				void setDateTime2Now();
				void setDateTime(const String& DateTimeValue);
				DateTime& getDateTime();

				int getManagedStatus();
				void setManagedStatus(ManagedStatus);


			private:

				ManagedStatus managedStatus;
				bOS::Utils::DateTime datetime;
			};

			class ENGINE_API XMLManagedEventElement
			{
			public:
				static String MAIN_NODE;

				static String DATETIME_ATTRIBUTE;
				
				static String STATUS_ATTRIBUTE;

				static String MANAGED_STATUS;
				static String UNMANAGED_STATUS;
				static String MANAGING_STATUS;

			};
		}
	}
}

#endif //_MANAGED_EVENTELEMENT_H_