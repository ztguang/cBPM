#ifndef _STATUS_H_
#define _STATUS_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API Status : public XMLObject, public bOS::Collections::CollectionEntry
			{
				public:

					Status();
					Status( bOS::XML::XMLNode* node );

					virtual ~Status();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid(){return true;}

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*) {return false;}

					String& getStatus() { return sStatus;}
					String& getDate(){ return sDate;}

					void setStatus(const String& Value) { sStatus = Value;}
					void setDate(const String& Value) {sDate= Value;}

				private:

					String		sStatus;
					String		sDate;
			};

			class ENGINE_API XMLStatus
			{
			public:

				static String MAIN_NODE;

			private:

				static String DATE_ATTRIBUTE;

				friend class Status;
				friend class Log;//DATE_ATTRIBUTE is used for Log too.
			};
		}
	}
}

#endif //_STATUS_H_
