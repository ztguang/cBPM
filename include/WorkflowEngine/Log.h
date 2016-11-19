#ifndef _LOG_DATAMODEL_H_
#define _LOG_DATAMODEL_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "Status.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API Log : public XMLObjectSet, public bOS::Collections::CollectionEntry
			{
				public:

					Log();
					Log(bOS::XML::XMLNode* node );

					virtual ~Log();

					//XMLObjectSet
					virtual void init();
					bool init(bOS::XML::XMLNode* node);
					bool init(const char* acXML);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*) {return false;}

					String& getUserKey() { return sUserKey;}
					String& getResult() { return sResult;}
					String& getStatus() { return status.getStatus();}
					String& getDate() { return status.getDate();}

					void setUserKey(const String& Value ) { sUserKey = Value;}
					void setResult( const String& Value) { sResult=Value;}
					void setStatus( const String& Value);
					void setDate(const String& Value) { status.setDate(Value);}

					//Verifica se il log contiene lo stato inserito.
					//Utile per verificare se l'attivity ha assunto quello stato.
					bool checkStatus(const char* acStatus, bool bNotSkipCuurentStatus);

					void add(Status&);
					void add(Status*);

			private:
					String sUserKey;
					String sResult;

					//LogCorrente
					Status status;
			};

			class ENGINE_API XMLLog
			{
			public:
				static String MAIN_NODE;

			private:

				static String OWNER_ATTRIBUTE;
				static String RESULT_ATTRIBUTE;

				friend class Log;
			};

		}
	}
}

#endif //_LOG_DATAMODEL_H_

