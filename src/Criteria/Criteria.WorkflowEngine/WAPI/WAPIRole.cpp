#include "CommonDefines.h"

#include "WAPIRole.h"

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

//DB
#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "Roles.h"
#include "Role.h"
#include "Users.h"
#include "User.h"
using namespace DataManager::Panorama::WorkflowParticipantsData;

#include "WAPIError.h"

extern "C" ENGINE_API char* getRoles(Response* response)
{
	CM_CODEBLOCK(WAPIRole::getRoles)
	assert(response!=NULL);

	Roles vRoles;

	try
	{
		DataBaseHelper::instance()->getRoles (vRoles);
	}
	catch (  DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Roles..Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
		return NULL;
	} 

	String sRoles = vRoles.getXMLString(0);
	
	return StringUtils::toChar (sRoles);
}

extern "C" ENGINE_API char* getRolesBykey(char* acRoleKey, Response* response)
{
	CM_CODEBLOCK(WAPIRole::getRolesBykey)
	assert(response!=NULL);

	Role role;
	role.setKey(acRoleKey);

	try
	{
		DataBaseHelper::instance()->getRole (role);

		String sRole = role.getXMLString(0);
		return StringUtils::toChar (sRole);

	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to find[" << acRoleKey << "].Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_ROLES_ROLEKEY_NOTFOUND;
		response->sMsg = WAPIERR_ROLES_ROLEKEY_NOTFOUND_DESCR;
		return NULL;
	}
}

extern "C" ENGINE_API void createRole(char* acRole, Response* response)
{
	CM_CODEBLOCK(WAPIRole::createRole)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->addRole (acRole);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to insert Role.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_ROLES_ROLEKEY_ALREADY_EXIST;
		response->sMsg = WAPIERR_ROLES_ROLEKEY_ALREADY_EXIST_DESCR;
	}
}

extern "C" ENGINE_API void updateRole(char* acRole, Response* response)
{
	CM_CODEBLOCK(WAPIRole::updateRole)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->updateRole(acRole);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to update Role.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_ROLES_ROLEKEY_NOTFOUND;
		response->sMsg = WAPIERR_ROLES_ROLEKEY_NOTFOUND_DESCR;
	}
}

extern "C" ENGINE_API void deleteRole(char* acRoleKey, Response* response)
{
	CM_CODEBLOCK(WAPIRole::deleteRole)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->deleteRole(acRoleKey);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to delete Role.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_ROLES_ROLEKEY_NOTFOUND;
		response->sMsg = WAPIERR_ROLES_ROLEKEY_NOTFOUND_DESCR;
	}
}

extern "C" ENGINE_API void addUserToRole(char* acUser, char* acRoleKey, Response* response)
{
	CM_CODEBLOCK(WAPIRole::addUserToRole)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->addUserToRole(acUser, acRoleKey);
	}
	catch ( DBException& dbErr )
	{
		//TODO: Manager other errors.
		CM_TRACE_ERROR("Impossible to delete Role.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_ROLES_ROLEKEY_NOTFOUND;
		response->sMsg = WAPIERR_ROLES_ROLEKEY_NOTFOUND_DESCR;
	}

	//TODO: response->iCode = WAPIERR_ROLES_USERKEY_ALREADY_EXIST;
	//response->sMsg = WAPIERR_ROLES_USERKEY_ALREADY_EXIST_DESCR;
}

extern "C" ENGINE_API void removeUserFromRole(char* acUserKey, char* acRoleKey, Response* response)
{
	CM_CODEBLOCK(WAPIRole::removeUserFromRole)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->deleteUserFromRole(acUserKey, acRoleKey);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to delete Role.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_ROLES_ROLEKEY_NOTFOUND;
		response->sMsg = WAPIERR_ROLES_ROLEKEY_NOTFOUND_DESCR;
	}

	//TODO: response->iCode = WAPIERR_ROLES_USERKEY_NOTFOUND;
	//response->sMsg = WAPIERR_ROLES_USERKEY_NOTFOUND_DESCR;
}

extern "C" ENGINE_API char* getRolesByUser(char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIRole::getRoleByUser)
	assert(response!=NULL);

	Roles roles;
	try
	{
		DataBaseHelper::instance()->getRolesByUser (acUser, roles);

		String sRoles = roles.getXMLString(0);
		return StringUtils::toChar (sRoles);

	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to find[" << acUser << "].Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_USERS_USERKEY_NOTFOUND;
		response->sMsg = WAPIERR_USERS_USERKEY_NOTFOUND_DESCR;
		return NULL;
	}
}
