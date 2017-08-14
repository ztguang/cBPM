#include "WAPI/WAPI.h"
#include "WAPI/WAPIUser.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
using namespace DataManager::DataBase;

void AllWAPIUser()
{
	CM_CODEBLOCK(AllWAPIUser)
	
	Response* response = new Response();

	response->iCode = 0;
	string sUser = "<User Key=\"ddematteo\">";
	sUser+="<Name>Daniele DeMatteo</Name>";
	sUser+="<Description>Daniele DeMatteo</Description>";
	sUser+="<Password>456</Password>";
	sUser+="<DisplayName>***</DisplayName>";
	sUser+="<Email>***</Email>";
	sUser+="</User>";
	createUser((char*)sUser.c_str(),response);
	if ( response->iCode == 0 )
	{
		cout << "User created." << endl;
	}
	else
	{
		cout << "User not created.[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	sUser = "<User Key=\"ddematteo\">";
	sUser+="<Name>Daniele DeMatteo</Name>";
	sUser+="<Description>Daniele DeMatteo</Description>";
	sUser+="<Password>456</Password>";
	sUser+="<DisplayName>***</DisplayName>";
	sUser+="<Email>***</Email>";
	sUser+="</User>";
	createUser((char*)sUser.c_str(),response);
	if ( response->iCode == 0 )
	{
		cout << "User created." << endl;
	}
	else
	{
		cout << "User not created.[" << response->sMsg << "]" << endl;
	}

	sUser = "<User Key=\"mfarina\">";
	sUser+="<Name>Maurizio Farina</Name>";
	sUser+="<Description>Maurizio Farina</Description>";
	sUser+="<Password>1234</Password>";
	sUser+="<DisplayName>***</DisplayName>";
	sUser+="<Email>***</Email>";
	sUser+="</User>";
	response->iCode = 0;
	updateUser((char*)sUser.c_str(), response);
	if ( response->iCode == 0 )
	{
		cout << "User Updated." << endl;
	}
	else
	{
		cout << "User not updated.[" << response->sMsg << "]" << endl;
	}

	sUser = "<User Key=\"ddematteo\">";
	sUser+="<Name>Daniele DeMatteo Modificato</Name>";
	sUser+="<Description>Maurizio Farina</Description>";
	sUser+="<Password>1234</Password>";
	sUser+="<DisplayName>***</DisplayName>";
	sUser+="<Email>***</Email>";
	sUser+="</User>";
	response->iCode = 0;
	updateUser((char*)sUser.c_str(), response);
	if ( response->iCode == 0 )
	{
		cout << "User Updated." << endl;
	}
	else
	{
		cout << "User not updated.[" << response->sMsg << "]" << endl;
	}

	response->iCode =0;
	int iRet = authenticate("millepiani", "a", response);
	if ( response->iCode == 0 )
	{
		cout << "mfarina. Authenticate " << (iRet ? "ok" : "ko") << endl;
	}
	else
	{
		cout << "mfarina not found." << endl;
		CM_TRACE_ERROR("Authenticate Error[" << response->sMsg << "]")
	}
	response->iCode = 0;

	iRet = authenticate("ddematteo", "1234", response);
	if ( response->iCode == 0 )
	{
		cout << "mfarina2. Authenticate " << (iRet ? "ok" : "ko") << endl;
	}
	else
	{
		cout << "mfarina2 not found." << endl;
		CM_TRACE_ERROR("Authenticate Error[" << response->sMsg << "]")
	}

	response->iCode = 0;
	char* acRet = getUser("ddematteo", response);
	if ( response->iCode == 0 )
	{
		cout << "mfarina " << acRet << endl;
	}
	else
	{
		cout << "mfarina not found." << endl;
		CM_TRACE_ERROR("getUser Error[" << response->sMsg << "]")
	}

	response->iCode = 0;
	acRet = getUser("ddematteo2", response);
	if ( response->iCode == 0 )
	{
		cout << "mfarina " << acRet << endl;
	}
	else
	{
		cout << "mfarina not found." << endl;
		CM_TRACE_ERROR("getUser Error[" << response->sMsg << "]")
	}

	response->iCode = 0;
	acRet = getUsers(response);
	if ( response->iCode == 0 )
	{
		cout << "Users[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getUsers Error[" << response->sMsg << "]")
	}
	
	response->iCode = 0;
	deleteUser("ddematteo2", response);
	if ( response->iCode == 0 )
	{
		cout << "User Deleted." << endl;
	}
	else
	{
		cout << "User not deleted.[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	deleteUser("ddematteo", response);
	if ( response->iCode == 0 )
	{
		cout << "User Deleted." << endl;
	}
	else
	{
		cout << "User not deleted.[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	sUser = "<User Key=\"ddematteo\">";
	sUser+="<Name>Daniele DeMatteo</Name>";
	sUser+="<Description>Daniele DeMatteo</Description>";
	sUser+="<Password>456</Password>";
	sUser+="<DisplayName>***</DisplayName>";
	sUser+="<Email>***</Email>";
	sUser+="</User>";
	createUser((char*)sUser.c_str(),response);
	if ( response->iCode == 0 )
	{
		cout << "User created." << endl;
	}
	else
	{
		cout << "User not created.[" << response->sMsg << "]" << endl;
	}

}