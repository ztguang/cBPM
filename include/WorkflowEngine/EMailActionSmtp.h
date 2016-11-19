#ifndef __EMAIL_ACTION_SMTP_H__
#define __EMAIL_ACTION_SMTP_H__

#include "EMailAction.h"

#include "SmtpLibrary/Smtp.h"
using namespace mail;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Mail
			{
				namespace Action
				{
					class EMailActionSmtp : public EMailAction
					{
						public:

							EMailActionSmtp( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
					        
							virtual ~EMailActionSmtp();

							virtual int action( String& result );

						protected:
							int evaluateAction();

						private:

							static String SERVERSMTP_HOST;
							static String SERVERSMTP_PORT;
							static String FROM;
							static String FROM_MAIL;
							static String RECIPIENT_TO;
							static String RECIPIENT_CC;
							static String RECIPIENT_BCC;
							static String SUBJECT;

							Smtp smtp;

							String sServer;
							String sFrom;
							String sFromMail;
							String sSubject;
							String sTo;
							String sCC;
							String sBCC;
							unsigned short iPort;


					};
				}
			}
		}
	}
}

#endif 



