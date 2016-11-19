#include "WAPI/WAPI.h"
#include "WAPI/WAPIRole.h"
#include "WAPI/WAPIUser.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
using namespace DataManager::DataBase;

void AllWAPIRole()
{
	CM_CODEBLOCK(AllWAPIRole)

	Response* response = new Response();
	char* acRet = getRoles(response);
	if ( response->iCode == 0 )
	{
		cout << "Roles[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving Roles.[" << response->sMsg << "]" << endl;
	}

	

	string sRole = "<Role Key=\"ScenarioUser\">";
	sRole+="<Name>SuperUser</Name>";
	sRole+="<Description>myWorkflow SuperUser</Description>";
	sRole+="<Users>";
	sRole+="<User Key=\"ddematteo\"></User>";
	sRole+="<User Key=\"mfarina\"></User>";
	sRole+="</Users>";
	sRole+="</Role>";
	
	response->iCode = 0;
	createRole((char*)sRole.c_str(), response);
	if ( response->iCode == 0 )
	{
		cout << "Role[SuperUser] created." << endl;
	}
	else
	{
		cout << "Error inserting SuperUser[" << response->sMsg << "]" << endl;
	}

	sRole = "<Role Key=\"ScenarioUser\">";
	sRole+="<Name>SuperUser</Name>";
	sRole+="<Description>myWorkflow SuperUser</Description>";
	sRole+="<Users>";
	sRole+="<User Key=\"ddematteo\"></User>";
	sRole+="<User Key=\"mfarina\"></User>";
	sRole+="</Users>";
	sRole+="</Role>";
	
	response->iCode = 0;
	createRole((char*)sRole.c_str(), response);
	if ( response->iCode == 0 )
	{
		cout << "Role[SuperUser] created." << endl;
	}
	else
	{
		cout << "Error inserting SuperUser[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	acRet = getRolesBykey("Administrator", response);
	if ( response->iCode == 0 )
	{
		cout << "Role[Administrator]" << acRet << endl;
	}
	else
	{
		cout << "Error Retrieving Administrator Role.[" << response->sMsg  << "]" << endl;
	}

	response->iCode = 0;
	acRet = getRolesBykey("Administrator2", response);
	if ( response->iCode == 0 )
	{
		cout << "Role[Administrator]" << acRet << endl;
	}
	else
	{
		cout << "Error Retrieving Administrator Role.[" << response->sMsg << "]" << endl;
	}

	sRole = "<Role Key=\"Developer\">";
	sRole+="<Name>Developer</Name>";
	sRole+="<Description>myWorkflow Developer</Description>";
	sRole+="<Users>";
	sRole+="<User Key=\"ddematteo\"></User>";
	sRole+="<User Key=\"mfarina\"></User>";
	sRole+="</Users>";
	sRole+="</Role>";
	response->iCode = 0;
	updateRole((char*)sRole.c_str(), response);
	if ( response->iCode == 0 )
	{
		cout << "Role[Developer] updated." << endl;
	}
	else
	{
		cout << "Error updating Developer[" << response->sMsg << "]" << endl;
	}

	sRole = "<Role Key=\"ScenarioUser\">";
	sRole+="<Name>Developer</Name>";
	sRole+="<Description>Developer</Description>";
	sRole+="<Users>";
	sRole+="<User Key=\"ddematteo\"></User>";
	sRole+="<User Key=\"mfarina\"></User>";
	sRole+="</Users>";
	sRole+="</Role>";
	response->iCode = 0;
	updateRole((char*)sRole.c_str(), response);
	if ( response->iCode == 0 )
	{
		cout << "Role[Developer] updated." << endl;
	}
	else
	{
		cout << "Error updating Developer[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	deleteRole("SuperUser",response);
	if ( response->iCode == 0 )
	{
		cout << "Role[SuperUser] deleted." << endl;
	}
	else
	{
		cout << "Error deleting SuperUser[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	deleteRole("ScenarioUser",response);
	if ( response->iCode == 0 )
	{
		cout << "Role[SuperUser] deleted." << endl;
	}
	else
	{
		cout << "Error deleting SuperUser[" << response->sMsg << "]" << endl;
	}

	sRole = "<Role Key=\"ScenarioUser\">";
	sRole+="<Name>SuperUser</Name>";
	sRole+="<Description>myWorkflow SuperUser</Description>";
	sRole+="<Users>";
	sRole+="<User Key=\"ddematteo\"></User>";
	sRole+="<User Key=\"mfarina\"></User>";
	sRole+="</Users>";
	sRole+="</Role>";
	
	response->iCode = 0;
	createRole((char*)sRole.c_str(), response);
	if ( response->iCode == 0 )
	{
		cout << "Role[SuperUser] created." << endl;
	}
	else
	{
		cout << "Error inserting SuperUser[" << response->sMsg << "]" << endl;
	}

	string sUser = "<User Key=\"ddematteo\">";
	sUser+="<Name>Giancarmine Celentano</Name>";
	sUser+="<Description>Giancarmine Celentano</Description>";
	sUser+="<Password>1234</Password>";
	sUser+="<DisplayName>***</DisplayName>";
	sUser+="<Email>***</Email>";
	sUser+="</User>";
	response->iCode = 0;
	addUserToRole((char*)sUser.c_str(), "ScenarioUser", response);
	if ( response->iCode == 0 )
	{
		cout << "User[gcelentano] added to Developer Role." << endl;
	}
	else
	{
		cout << "Error adding User[gcelentano].[" << response->sMsg << "]" << endl;
	}

	sUser = "<User Key=\"gcelentano\">";
	sUser+="<Name>Giancarmine Celentano</Name>";
	sUser+="<Description>Giancarmine Celentano</Description>";
	sUser+="<Password>1234</Password>";
	sUser+="<DisplayName>***</DisplayName>";
	sUser+="<Email>***</Email>";
	sUser+="</User>";
	response->iCode = 0;
	addUserToRole((char*)sUser.c_str(), "ScenarioUser", response);
	if ( response->iCode == 0 )
	{
		cout << "User[gcelentano] added to Developer Role." << endl;
	}
	else
	{
		cout << "Error adding User[gcelentano].[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	acRet = getUsersByRole("ScenarioUser",response);	
	if ( response->iCode == 0 )
	{
		cout << "Administrator Users[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Administrator not found." << endl;
		CM_TRACE_ERROR("getUsersByRole Error[" << response->sMsg << "]")
	}

	response->iCode = 0;
	acRet = getUsersByRole("ScenarioUser2",response);	
	if ( response->iCode == 0 )
	{
		cout << "Administrator Users[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Administrator not found." << endl;
		CM_TRACE_ERROR("getUsersByRole Error[" << response->sMsg << "]")
	}

	response->iCode = 0;
	removeUserFromRole("gcelentano", "ScenarioUser", response);
	if ( response->iCode == 0 )
	{
		cout << "User[gcelentano] removed from Developer Role." << endl;
	}
	else
	{
		cout << "Error removing User[gcelentano].[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	removeUserFromRole("gcelentano", "ScenarioUser", response);
	if ( response->iCode == 0 )
	{
		cout << "User[gcelentano] removed from Developer Role." << endl;
	}
	else
	{
		cout << "Error removing User[gcelentano].[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	acRet = getRolesByUser("ddematteo", response);
	if ( response->iCode == 0 )
	{
		cout << "User[mfarina] in Role[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving User[mfarina] in Roles.[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	acRet = getRolesByUser("ddematteo2", response);
	if ( response->iCode == 0 )
	{
		cout << "User[mfarina] in Role[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving User[mfarina] in Roles.[" << response->sMsg << "]" << endl;
	}

	response->iCode = 0;
	int iRet = isInRole("ddematteo", "Administrator", response);
	if ( response->iCode == 0 )
	{
		cout << "mfarina2 " << (iRet ? "in" : "not in") << " Administrator" << endl;
	}
	else
	{
		cout << "mfarina2 not found." << endl;
		CM_TRACE_ERROR("isInRole Error[" << response->sMsg << "]")
	}

	response->iCode = 0;
	iRet = isInRole("ddematteo", "ScenarioUser", response);
	if ( response->iCode == 0 )
	{
		cout << "mfarina2 " << (iRet ? "in" : "not in") << " Administrator" << endl;
	}
	else
	{
		cout << "mfarina2 not found." << endl;
		CM_TRACE_ERROR("isInRole Error[" << response->sMsg << "]")
	}

	response->iCode = 0;
	acRet = getRoles(response);
	if ( response->iCode == 0 )
	{
		cout << "Roles[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving Roles.[" << response->sMsg << "]" << endl;
	}
}


