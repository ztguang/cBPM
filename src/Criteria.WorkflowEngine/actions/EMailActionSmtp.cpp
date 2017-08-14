#include "CommonDefines.h"

#include "EMailActionSmtp.h"
using namespace WorkflowEngine::Criteria::BasicTask::Mail::Action;

String EMailActionSmtp::SERVERSMTP_HOST = "SMTP_HOST";
String EMailActionSmtp::SERVERSMTP_PORT	= "SMTP_PORT";
String EMailActionSmtp::FROM			= "FROM";
String EMailActionSmtp::FROM_MAIL		= "FROM_MAIL";
String EMailActionSmtp::RECIPIENT_TO	= "TO";
String EMailActionSmtp::RECIPIENT_CC	= "CC";
String EMailActionSmtp::RECIPIENT_BCC	= "BCC";
String EMailActionSmtp::SUBJECT			= "SUBJECT";

EMailActionSmtp::EMailActionSmtp( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
    : EMailAction(process, task) 
{
}

EMailActionSmtp::~EMailActionSmtp() 
{
}

int EMailActionSmtp::action( String& result )
{
	CM_CODEBLOCK(action)

    int feErr = this->evaluateAction();
    
	if ( feErr != FE_OK)
	{
		CM_TRACE_CODEPATH( "No Action performed.")
        return feErr;
	}

	bool bRet=true;

	if ( iPort == 0 )
	{
		bRet=smtp.ConnectServer(sServer.c_str());
	}
	else
	{
		bRet=smtp.ConnectServer(sServer.c_str(), iPort);
	}
	if ( !bRet )
	{
		return FE_TASK_MAIL_ERROR;
	}

	smtp.SetSenderName(sFrom.c_str());
	smtp.SetSenderEmail(sFromMail.c_str());
	smtp.SetSubject(sSubject.c_str());
	smtp.AddRecipient(sTo.c_str());

	if ( sCC!= "")
	{
		smtp.AddCCRecipient (sCC.c_str());
	}
	
	
	if ( sBCC != ""  ) 
	{
		smtp.AddBCCRecipient (sBCC.c_str());
	}
	

	smtp.SetMessageBody(_ActionText.c_str());

	if (smtp.GetConnectStatus())
	{        
		if ( !(smtp.Send()) )
		{
			return FE_TASK_MAIL_ERROR;
		}
		
	}
	smtp.Disconnect();

	return FE_OK;
}

int EMailActionSmtp::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	int iErr = EMailAction::evaluateAction ();
	
	if ( iErr != FE_OK)
	{
		CM_TRACE_CODEPATH( "No Action performed.")
        return iErr;
	}

	//TODO:
	//Designing an action for Email.
	WorkflowRelevantData::Attribute* var = getAttribute( EMailActionSmtp::SERVERSMTP_HOST );
	if ( var == NULL ) 
	{
		return FE_TASK_TASKACTION_INVALID;
	}
	
	sServer=var->getValue();


	var = getAttribute( EMailActionSmtp::SERVERSMTP_PORT );
	if ( var != NULL )
	{
		iPort = atoi(var->getValue().c_str());
	}
	else
		iPort=0;

	var = getAttribute( EMailActionSmtp::FROM );
	if ( var == NULL ) 
	{
		return FE_TASK_TASKACTION_INVALID;
	}
	sFrom=var->getValue();

	var = getAttribute( EMailActionSmtp::FROM_MAIL );
	if ( var == NULL ) 
	{
		return FE_TASK_TASKACTION_INVALID;
	}
	sFromMail=var->getValue();

	var = getAttribute( EMailActionSmtp::RECIPIENT_TO );
	if ( var == NULL ) 
	{
		return FE_TASK_TASKACTION_INVALID;
	}
	sTo=var->getValue();

	var = getAttribute( EMailActionSmtp::SUBJECT );
	if ( var == NULL ) 
	{
		return FE_TASK_TASKACTION_INVALID;
	}
	sSubject=var->getValue();

	var = getAttribute( EMailActionSmtp::RECIPIENT_CC );
	if ( var != NULL ) 
	{
		sCC=var->getValue();
	}
	
	
	var = getAttribute( EMailActionSmtp::RECIPIENT_BCC );
	if ( var != NULL ) 
	{
		sBCC=var->getValue();
	}
	

    return FE_OK;
}

