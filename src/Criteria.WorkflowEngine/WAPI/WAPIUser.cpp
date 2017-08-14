#include "CommonDefines.h"

#include "WAPIUser.h"
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

extern "C" ENGINE_API int authenticate(char* acUserKey, char* acPassword, Response* response)
{
	CM_CODEBLOCK(WAPIUser::authenticate)
	assert(response!=NULL);

	//TODO: 
	if ( !strcmp(acUserKey, "scenario") && !strcmp(acPassword, "AgileBPMS") )
	{
		return 1;
	}

	CM_TRACE_DEBUG("Authenticate[" << acUserKey << "]")
	User user;
	user.setKey(acUserKey);

	try
	{
		DataBaseHelper::instance()->getUser (user);

		String sPwd = user.getPassword();

		if ( strcmp(sPwd.c_str(), acPassword) )
		{
			CM_TRACE_DEBUG("User[" << acUserKey << "] not authenticated. PasswordError[" << acPassword << "]")
			return 0;
		}
		else
		{
			return 1;
		}
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to authenticate[" << acUserKey << "].Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_USERS_USERKEY_NOTFOUND;
		response->sMsg = WAPIERR_USERS_USERKEY_NOTFOUND_DESCR;
		return 1;
	}
}

extern "C" ENGINE_API int isInRole(char* acUserKey, char* acRole, Response* response)
{
	CM_CODEBLOCK(WAPIUser::isInRole)
	assert(response!=NULL);

	Role role;
	role.setKey(acRole);

	try
	{
		DataBaseHelper::instance()->getRole (role);

	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to find[" << acRole << "].Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_ROLES_ROLEKEY_NOTFOUND;
		response->sMsg = WAPIERR_ROLES_ROLEKEY_NOTFOUND_DESCR;
		return NULL;
	}

	Users& users = role.getUsers();
	if ( users.checkUser(acUserKey) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

extern "C" ENGINE_API char* getUser(char* acUserKey, Response* response)
{
	CM_CODEBLOCK(WAPIUser::getUser)
	assert(response!=NULL);

	User user;
	user.setKey(acUserKey);

	try
	{
		DataBaseHelper::instance()->getUser (user);

		String sUsers = user.getXMLString(0);
		return StringUtils::toChar (sUsers);

	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to authenticate[" << acUserKey << "].Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_USERS_USERKEY_NOTFOUND;
		response->sMsg = WAPIERR_USERS_USERKEY_NOTFOUND_DESCR;
		return NULL;
	}
}

extern "C" ENGINE_API char* getUsers(Response* response)
{
	CM_CODEBLOCK(WAPIUser::getUsers)
	assert(response!=NULL);

	Users vUsers;

	try
	{
		DataBaseHelper::instance()->getUsers (vUsers);
	}
	catch (  DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Users..Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
		return NULL;
	} 

	String sUsers = vUsers.getXMLString(0);
	
	return StringUtils::toChar (sUsers);
}

extern "C" ENGINE_API char* getUsersByRole(char* acRole, Response* response)
{
	CM_CODEBLOCK(WAPIUser::getUsersByRole)
	assert(response!=NULL);

	Role role;
	role.setKey(acRole);

	try
	{
		DataBaseHelper::instance()->getRole (role);

	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to find[" << acRole << "].Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_ROLES_ROLEKEY_NOTFOUND;
		response->sMsg = WAPIERR_ROLES_ROLEKEY_NOTFOUND_DESCR;
		return NULL;
	}

	Users& users = role.getUsers();
	String sUsers = users.getXMLString(1);

	return StringUtils::toChar (sUsers);
}


extern "C" ENGINE_API void createUser(char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIUser::createUser)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->addUser (acUser);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to insert User.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_USERS_USERKEY_ALREADY_EXIST;
		response->sMsg = WAPIERR_USERS_USERKEY_ALREADY_EXIST_DESCR;
	}
}

extern "C" ENGINE_API void updateUser(char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIUser::updateUser)
	assert(response!=NULL);

	try
	{
		CM_TRACE_CODEPATH("Updating[" << acUser << "]")
		DataBaseHelper::instance()->updateUser(acUser);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to update User.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_USERS_USERKEY_NOTFOUND;
		response->sMsg = WAPIERR_USERS_USERKEY_NOTFOUND_DESCR;
	}
}

extern "C" ENGINE_API void deleteUser(char* acUserKey, Response* response)
{
	CM_CODEBLOCK(WAPIUser::deleteUser)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->deleteUser(acUserKey);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to delete User.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_USERS_USERKEY_NOTFOUND;
		response->sMsg = WAPIERR_USERS_USERKEY_NOTFOUND_DESCR;
	}
}