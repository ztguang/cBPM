#ifndef _MESSAGES_H_
#define _MESSAGES_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "bOSSQLTable.h"

#include "ProcessComponent.h"

#include "Message.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API Messages : public bOS::XML::Data::XMLObjectSet,
											public bOS::SQL::SQLTable,
											public ProcessComponent
			{
			public:
				Messages();
				Messages(bOS::XML::XMLNode* node );
				virtual ~Messages();

				//XMLObject
				virtual void init();
				bool init(bOS::XML::XMLNode*node);
				bool init(const char* acXML);
				bool parse(bOS::XML::XMLAttribute*);
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				//SQLTable
				const char* acGetTableName()				{return SQLMessage::TABLE_NAME.c_str();}
				void setRecord(bOS::SQL::ResultSetRecord&)	{;}
				String acGetWhere()							{return ProcessComponent::acGetWhere();}
				bool parse(bOS::SQL::ResultSetField*)		{return true;}
				bool parse(bOS::SQL::ResultSetRecord*);
				void addSQLCommands(bOS::SQL::SQLCommands& vCommands, int operation);

				bool haveAutoIncrementField() { return true;}
				void setAutoIncrementField(long ) {;}

				void addMessages(Messages& vMessages);
				bool addMessage(Message& message);

			private:

			};

			class ENGINE_API XMLMessages
			{
			public:
				static String MAIN_NODE;
			};

			class ENGINE_API SQLMessages
			{
			public:
				static String TABLE_NAME;

			private:
				friend class Messages;
			};
		}
	}
}

#endif //_MESSAGES_H_
