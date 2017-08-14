#include "SMTPHelper.h"

#include "bOS/bOSXMLHelper.h"
#include "bOS/bOSXMLNode.h"
#include "bOS/bOSXMLAttribute.h"

#include "bOS/bOSSystem.h"

//DB
#include "Scenario/DataBaseHelper.h"
#include "Scenario/DBException.h"
using namespace DataManager::DataBase;

#include "Scenario/Roles.h"
#include "Scenario/Role.h"
#include "Scenario/Users.h"
#include "Scenario/User.h"
using namespace DataManager::Panorama::WorkflowParticipantsData;

#include "Scenario/FormalParameters.h"
#include "Scenario/FormalParameter.h"
using namespace DataManager::Panorama::Common;

#include "Scenario/ApplicationFunction.h"
#include "Scenario/ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "Scenario/ApplicationTemplate.h"

#include "bOS/Tracer.h"

const String TO_PARAMETER		= "To";
const String CC_PARAMETER		= "Cc";
const String BCC_PARAMETER		= "Bcc";
const String USER_TO_PARAMETER	= "UserTo";
const String USER_CC_PARAMETER	= "UserCc";
const String USER_BCC_PARAMETER	= "UserBcc";
const String ROLE_TO_PARAMETER	= "RoleTo";
const String ROLE_CC_PARAMETER	= "RoleCc";
const String ROLE_BCC_PARAMETER	= "RoleBcc";
const String SUBJECT_PARAMETER	= "Subject";
const String BODY_PARAMETER		= "Body";
const String IDSUBJECT_PARAMETER= "IdSubject";
const String IDBODY_PARAMETER	= "IdBody";
const String ATTACH_PARAMETER	= "Attach";

SMTPHelper* SMTPHelper::_instance = NULL;

String sMailServer;
String sSenderAlias;
String sSenderMail;

SMTPHelper* SMTPHelper::instance()
{
	if ( _instance == NULL )
	{
		_instance = new SMTPHelper();
	}

	return _instance;
}

void SMTPHelper::deinstance()
{
	if (_instance != NULL )
		delete _instance;
}

SMTPHelper::SMTPHelper()
{
	//ReadXML
	string sFile = bOS::CoreSystem::System::getEnvironmentVariable ("${WF_HOME}");
	sFile+="\\database\\SMTPHelper.xml";

	bOS::XML::XMLNode* node = bOS::XML::XMLHelper::parseFromFile (sFile.c_str());

	bOS::XML::XMLAttribute* attribute = node->getAttribute ("MailServer");
	sMailServer = attribute->getValue();

	bOS::XML::XMLNode* nodeSender = node->getNode ("Sender");

	attribute = nodeSender->getAttribute ("User");
	sSenderMail = attribute->getValue();

	attribute = nodeSender->getAttribute ("Alias");
	sSenderAlias = attribute->getValue();

	delete node;
}

SMTPHelper::~SMTPHelper()
{
}


char* SMTPHelper::SendWithFormat(bool bMailFormat, char* acFunction)
{
	long lCode = 0;
	String sMessage="Parametro";

	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	String sTo;
	String sCc;
	String sBcc;
	String sUserTo;
	String sUserCc;
	String sUserBcc;
	String sRoleTo;
	String sRoleCc;
	String sRoleBcc;
	String sBody;
	String sSubject;
	String sAttach;

	int iSize = parameters.size();
	
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), TO_PARAMETER.c_str() ) )
		{
			sTo = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), CC_PARAMETER.c_str() ) )
		{
			sCc = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), BCC_PARAMETER.c_str() ) )
		{
			sBcc = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), USER_TO_PARAMETER.c_str() ) )
		{
			sUserTo = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), USER_CC_PARAMETER.c_str() ) )
		{
			sUserCc = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), USER_BCC_PARAMETER.c_str() ) )
		{
			sUserBcc = parameter->getValue().c_str();
		}

		else if ( !strcmp(parameter->getName().c_str(), ROLE_TO_PARAMETER.c_str() ) )
		{
			sRoleTo = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), ROLE_CC_PARAMETER.c_str() ) )
		{
			sRoleCc = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), ROLE_BCC_PARAMETER.c_str() ) )
		{
			sRoleBcc = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), SUBJECT_PARAMETER.c_str() ) )
		{
			sSubject = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), BODY_PARAMETER.c_str() ) )
		{
			sBody = parameter->getValue().c_str();
		}
		else if ( !strcmp(parameter->getName().c_str(), ATTACH_PARAMETER.c_str() ) )
		{
			sAttach = parameter->getValue().c_str();
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.";
		}
	}
	

	ApplicationFunctionResult result;

	//action
	if ( ( ( sTo.length() > 0) || (sUserTo.length() > 0 ) || ( sRoleTo.length() > 0) ) && (sSubject.length() > 0 ) )
	{
		CSMTPConnection smtp;
		//Connect to the server
		if ( smtp.Connect(sMailServer.c_str()) )
		{
			CSMTPMessage message;
			message.SetHTMLFormat(bMailFormat);
			CSMTPAddress From(sSenderAlias.c_str(), sSenderMail.c_str()); //Change these values to your settings
			message.m_From = From;

			if ( sTo.length() > 0 )
			{
				string sMailTo = sTo;
				int iPos = 0;

				while ( (iPos = sMailTo.find_first_of (';', 0)) > -1)
				{
					string sOnlyOne = sMailTo.substr (0, iPos);
					sMailTo = sMailTo.substr (iPos+1);

					SMTPHelper::instance()->AddMail ( sOnlyOne.c_str(), message, CSMTPMessage::TO);
				}

				SMTPHelper::instance()->AddMail ( sMailTo.c_str(), message, CSMTPMessage::TO);
			
			}

			if ( sCc.length() > 0 )
			{
				SMTPHelper::instance()->AddMail ( sCc.c_str(), message, CSMTPMessage::CC);
			}

			if ( sBcc.length() > 0 )
			{
				SMTPHelper::instance()->AddMail ( sBcc.c_str(), message, CSMTPMessage::BCC);
			}

			if ( sUserTo.length() > 0 )
			{
				SMTPHelper::instance()->AddUserMail ( sUserTo.c_str(), message, CSMTPMessage::TO);
			}

			if ( sUserCc.length() > 0 )
			{
				SMTPHelper::instance()->AddUserMail ( sUserCc.c_str(), message, CSMTPMessage::CC);
			}

			if ( sUserBcc.length() > 0 )
			{
				SMTPHelper::instance()->AddUserMail ( sUserBcc.c_str(), message, CSMTPMessage::BCC);
			}

			if ( sRoleTo.length() > 0 )
			{
				SMTPHelper::instance()->AddRoleMail ( sRoleTo.c_str(), message, CSMTPMessage::TO);
			}

			if ( sRoleCc.length() > 0 )
			{
				SMTPHelper::instance()->AddRoleMail ( sRoleCc.c_str(), message, CSMTPMessage::CC);
			}

			if ( sRoleBcc.length() > 0 )
			{
				SMTPHelper::instance()->AddRoleMail ( sRoleBcc.c_str(), message, CSMTPMessage::BCC);
			}

			message.m_sSubject = sSubject;
			message.AddBody(sBody);

			/*
			//Testing Reply To support
			m.m_ReplyTo = CSMTPAddress(_T("Another PJ"), _T("admin@mfarina.it"));
			*/

			if ( sAttach.length() > 0 )
			{
				CSMTPAttachment* attachment = new CSMTPAttachment();
				attachment->Attach(sAttach);
				message.AddAttachment(attachment);
			}

			//Sent the message
			if (!smtp.SendMessage(message))
			{
				lCode = 1000;
				sMessage= smtp.GetLastCommandResponse();
			}

			//Disconnect from the server
			smtp.Disconnect();

		}
		else
		{
			lCode = 1000;
			sMessage= smtp.GetLastCommandResponse();
		}
	}
	else
	{
		lCode =1000;
		sMessage = "E' necessario passare sia il destinetario che l'oggetto";
	}
	
	result.setCode (lCode);
	result.setMessage (sMessage);

	return StringUtils::toChar (result.getXMLString(1));
}


char* SMTPHelper::Send(char* acFunction)
{
	return SMTPHelper::instance()->SendWithFormat(false, acFunction);
}

char* SMTPHelper::SendHTML(char* acFunction)
{
	return SMTPHelper::instance()->SendWithFormat(true, acFunction);
}

bool SMTPHelper::AddMail(const char* acMail, CSMTPMessage& message, CSMTPMessage::RECIPIENT_TYPE RecipientType)
{
	CM_CODEBLOCK(SMTPHelper::AddUserMail)

	CM_TRACE_CODEPATH("Adding User[" << acMail << "] mail [" << acMail << "]")
	CSMTPAddress address(acMail, acMail );   //Change these values to your settings
	message.AddRecipient(address, RecipientType);
	return 1;
}

bool SMTPHelper::AddUserMail(const char* acUser, CSMTPMessage& message, CSMTPMessage::RECIPIENT_TYPE RecipientType)
{
	CM_CODEBLOCK(SMTPHelper::AddUserMail)

	User user;
	user.setKey(acUser);

	try
	{
		DataBaseHelper::instance()->getUser (user);

		CM_TRACE_CODEPATH("Adding User[" << acUser << "] mail [" << user.getEmail().c_str() << "]")

		string sMailTo = user.getEmail();
		int iPos = 0;

		while ( (iPos = sMailTo.find_first_of (';', 0)) > -1)
		{
			string sOnlyOne = sMailTo.substr (0, iPos);
			sMailTo = sMailTo.substr (iPos+1);

			CSMTPAddress address(user.getName().c_str(), sOnlyOne.c_str() );   
			message.AddRecipient(address, RecipientType);
		}

		CSMTPAddress address(user.getName().c_str(), sMailTo.c_str() );   
		message.AddRecipient(address, RecipientType);

		/*
		CSMTPAddress address(user.getName().c_str(), user.getEmail().c_str() );   //Change these values to your settings
		message.AddRecipient(address, RecipientType);
		*/
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to find user[" << acUser << "].Err[" << dbErr.getMessage() << "]");
		return 0;
	}

	return 1;
}

bool SMTPHelper::AddRoleMail(const char* acRole, CSMTPMessage& message, CSMTPMessage::RECIPIENT_TYPE RecipientType)
{
	CM_CODEBLOCK(SMTPHelper::AddRoleMail)

	Role role;
	role.setKey(acRole);

	try
	{
		DataBaseHelper::instance()->getRole (role);
		Users& vUsers = role.getUsers();
		unsigned int uiSize = vUsers.size();

		CM_TRACE_CODEPATH("Retrieved [" << uiSize << "] from Role[" << acRole << "]")

		for ( unsigned int ui=0; ui<uiSize; ui++)
		{
			User* user = (User*)vUsers.at(ui);

			SMTPHelper::instance()->AddUserMail(user->getKey().c_str(), message, RecipientType);
		}
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to find Role[" << acRole << "].Err[" << dbErr.getMessage() << "]");
		return 0;
	}

	return 1;
}


ApplicationTemplate* application = NULL;

extern "C" DLL_SMTP_HELPER_API void InstanceApplication(char* acApplicationName)
{
	if ( application == NULL)
	{	
		application = new ApplicationTemplate();
		application->init("SMTPHelper");

		/*
		*/
		application->addCallBack("Send", SMTPHelper::Send);
		application->addCallBack("SendHTML", SMTPHelper::SendHTML);
		//application->addSpecialCallBack("Message", SMTPHelper::Message);


		SMTPHelper::instance();
	}
}

extern "C" DLL_SMTP_HELPER_API void DeleteApplication(char* acApplicationName)
{
	//TODO: delete application;
	//SMTPHelper::deinstance();

}

extern "C" DLL_SMTP_HELPER_API char* ExecuteApplicationApi(char* acFunction)
{
	return application->executeApi (acFunction);
}
