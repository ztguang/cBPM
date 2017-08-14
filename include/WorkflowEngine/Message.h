#ifndef _MESSAGE_H_
#define _MESSAGE_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "bOSSQLTable.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "ProcessComponent.h"

#include "CriteriaCommonDefines.h"

#include "ExtendedAttributes.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API Message : public bOS::XML::Data::XMLObject,
											public bOS::Collections::CollectionEntry,
											public bOS::SQL::SQLTable,
											public ProcessComponent

			{
				public:

					Message();
					Message(bOS::XML::XMLNode* node );

					virtual ~Message();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//SQLTable
					const char* acGetTableName();
					void setRecord(bOS::SQL::ResultSetRecord&);
					String acGetWhere();
					bool parse(bOS::SQL::ResultSetField*);
					bool parse(bOS::SQL::ResultSetRecord*);
					bool haveAutoIncrementField() { return false;}
					void setAutoIncrementField(long ) {;}

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*) {return false;}

					String& getFromActivity() { return sFromActivity;}
					String& getToActivity() { return sToActivity;}

					void setFromActivity(const String& Value ) { sFromActivity = Value;}
					void setToActivity(const String& Value ) { sToActivity = Value;}

					DataManager::Panorama::Common::ExtendedAttributes& getParameters();

				private:

					String	sId;
					String	sFromActivity;
					String	sToActivity;

					Common::ExtendedAttributes parameters;
			};

			class ENGINE_API XMLMessage
			{
			public:
				static String MAIN_NODE;

				static String ID_ATTRIBUTE;
				static String FROM_ATTRIBUTE;
				static String TO_ATTRIBUTE;
			};

			class ENGINE_API SQLMessage
			{
			public:
				static String TABLE_NAME;

				static String ID_FIELD;
				static String FROM_FIELD;
				static String TO_FIELD;
				static String ATTRIBUTES_FIELD;
			};
		}
	}
}

#endif //_PROCESS_MESSAGE_H_
