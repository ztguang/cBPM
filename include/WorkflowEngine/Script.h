#ifndef _SCRIPT_H_
#define _SCRIPT_H_

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
			class ENGINE_API Script : public XMLObject
			{
				public:
					
					Script();
					Script( bOS::XML::XMLNode* node );

					virtual ~Script();

					//XMLObject
					void init();
					bool init(bOS::XML::XMLNode*node);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid(){return true;}

					String& getType() { return sType;}
					void setType(const String& sValue) { sType=sValue;}
					
					String& getCommand() { return sCommand;}
					void setCommand(const String& sValue) { sCommand = sValue;}

					String& getDataType() { return sDataType;}
					void setDataType(const String& sValue) { sDataType = sValue;}

				private:

					String sType;
					String sCommand;
					String sDataType;
			};

			class ENGINE_API XMLScript
			{
			public:
				static String MAIN_NODE;

				static String TYPE_ATTRIBUTE;
				static String DATATYPE_ATTRIBUTE;

				static String NONE_TYPE;
				static String SUBFLOW_SYNCH_TYPE;
				static String SUBFLOW_SPECIAL_TYPE;
				static String SUBFLOW_ASYNC_TYPE;
				static String API_SYNCH_TYPE;
				static String API_ASYNC_TYPE;

				static String EMAIL_SMTP_TYPE;
				static String APPLICATION_API_TYPE;
				static String XML_XSLT_TYPE;
				static String XML_FILE_WRITE_TYPE;
				static String XML_FILE_READ_TYPE;
				static String EVENT_MAKER_TYPE;
				static String EVENT_CONSUMER_TYPE;
				static String EVAL_EXPRESSION_TYPE;
				static String LOOP_COUNTER_TYPE;
				static String LOOP_EXPRESSION_TYPE;
			};
		}
	}
}

#endif //_SCRIPT_H_