#ifndef __XMLCTIONXSLT_H__
#define __XMLCTIONXSLT_H__

#include "XMLAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace XML
			{
				namespace Action
				{
				class XMLActionXSLT : public XMLAction
				{
					public:

						XMLActionXSLT( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
				        
						virtual ~XMLActionXSLT();

						virtual int action( String& result );

					protected:
						int evaluateAction();

					private:

						static String WF_OBJECT;
						static String XMLFILE_IN;
						static String XMLFILE_OUT;
						static String XSLFILE_IN;

						static String XMLSTRING_IN;
						static String XMLSTRING_OUT;
						static String XSLSTRING_IN;

						enum XSLTParamType
						{
							NONE,
							WF_OBJ,
							FILE, 
							STRING
						};

						XSLTParamType iInFlag;
						XSLTParamType iOutFlag;
						XSLTParamType iXslFlag;

						String sIn;
						String sOut;
						String sXsl;

						WorkflowRelevantData::Attribute* varOut;
				};
				}
			}
		}
	}
}

#endif 



