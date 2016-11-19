#ifndef _TRANSITION_H_
#define _TRANSITION_H_

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
			class ENGINE_API Transition : public bOS::Collections::CollectionEntry, public XMLObject
			{
				public:

					Transition();
					Transition(bOS::XML::XMLNode* node );

					virtual ~Transition();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*) {return false;}

					bool isNoReExecuteWay();

					String& getFromActivity() { return sFromActivity;}
					String& getToActivity() { return sToActivity;}
					String& getResult() { return sResult;}
					String& getOperator() { return sOperator;}
					bool getReExec() { return bReExec;}

					void setFromActivity(const String& Value ) { sFromActivity = Value;}
					void setToActivity(const String& Value ) { sToActivity = Value;}
					void setResult(const String& Value ) { sResult = Value;}
					void setOperator(const String& Value ) {sOperator=Value;}
					void setReExec(bool bValue) {bReExec=bValue;}

				private:

					String	sId;
					String	sFromActivity;
					String	sToActivity;
					String  sResult;
					String	sOperator;
					bool	bReExec;
			};

			class ENGINE_API XMLTransition
			{
			public:
				static String MAIN_NODE;

				static String ID_ATTRIBUTE;
				static String FROM_ATTRIBUTE;
				static String TO_ATTRIBUTE;

				static String RESULT_NODE;
				static String REEXEC_NODE;
				static String OPERATOR_NODE;

				static String NOTEQUAL_OPERATOR;
				static String EQUAL_OPERATOR;
				static String LESS_THAN_OPERATOR;
				static String MORE_THAN_OPERATOR;
				static String LESS_EQUAL_THAN_OPERATOR;
				static String MORE_EQUAL_THAN_OPERATOR;
				static String ALWAYS_OPERATOR;

				static String YES_REEXEC;
				static String NO_REEXEC;
			};
		}
	}
}

#endif //_PROCESS_TRANSITION_H_
