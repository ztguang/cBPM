#ifndef _DLL_SMTP_HELPER_APPLICATION_H_
#define _DLL_SMTP_HELPER_APPLICATION_H_

#ifdef DLL_SMTP_HELPER_EXPORTS
	#define DLL_SMTP_HELPER_API __declspec(dllexport)
#else
	#define DLL_SMTP_HELPER_API __declspec(dllimport)
#endif

extern "C" DLL_SMTP_HELPER_API void InstanceApplication(char*);
extern "C" DLL_SMTP_HELPER_API void DeleteApplication(char*);
extern "C" DLL_SMTP_HELPER_API char* ExecuteApplicationApi(char* );

#include "bOS/bOS.h"
#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "Scenario/CallBackFunction.h"

#include "smtp.h"

class SMTPHelper
{
public:
	
	static SMTPHelper* instance();
	static void deinstance();

	static char* (CALLBACK Send)(char*);
	static char* (CALLBACK SendHTML)(char*);
	
	
	char* SendWithFormat(bool bMailFormat,  char*);

	bool AddMail(const char* acMail, CSMTPMessage& message, CSMTPMessage::RECIPIENT_TYPE RecipientType);
	bool AddUserMail(const char* acUser, CSMTPMessage& message, CSMTPMessage::RECIPIENT_TYPE RecipientType);
	bool AddRoleMail(const char* acRole, CSMTPMessage& message, CSMTPMessage::RECIPIENT_TYPE RecipientType);

private:

	static SMTPHelper* _instance;

	SMTPHelper();
	~SMTPHelper();

};

#endif //_DLL_SMTP_HELPER_APPLICATION_H_