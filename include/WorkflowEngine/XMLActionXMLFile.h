#ifndef __XMLCTION_XMLFILE_H__
#define __XMLCTION_XMLFILE_H__

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
					class XMLActionXMLFile : public XMLAction
					{
						public:

							XMLActionXMLFile( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, bool bReadFile);
					        
							virtual ~XMLActionXMLFile();

							virtual int action( String& result );

						protected:
							int evaluateAction();

						private:

							bool bReadFile;
							String sFile;
							String sAttribute;

							static String XMLATTRIBUTE;
							static String XMLFILE;
					};
				}
			}
		}
	}
}

#endif //__XMLCTION_XMLFILE_H__



