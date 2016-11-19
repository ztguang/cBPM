#ifndef _WAPI_ERROR_H_
#define _WAPI_ERROR_H_

//General
const unsigned int WAPI_OK						= 0;

const unsigned int WAPI_DATABASE_INSTANCE_ERROR	= 1;
const unsigned int WAPI_ENGINE_INSTANCE_ERROR	= 2;
const unsigned int WAPI_INSTANCE_ERROR			= 3;

//Workflow
const unsigned int WAPIERR_WORKFLOW				= 100;

const unsigned int WAPIERR_WORKFLOW_NOT_FOUND	= 101;
static char* WAPIERR_WORKFLOW_NOT_FOUND_DESCR	= "Workflow not found";

const unsigned int WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND	= 102;
static char* WAPIERR_WORKFLOW_REPOSITORY_NOT_FOUND_DESCR	= "Impossible to retrieve Workflow Repository infos";

//Process
const unsigned int WAPIERR_PROCESS				= 1000;
static char* WAPIERR_PROCESS_DESCR				= "ProcessInstance not created";

const unsigned int WAPIERR_PROCESS_NOT_FOUND	= 1001;
static char* WAPIERR_PROCESS_NOT_FOUND_DESCR	= "ProcessInstance not found";

const unsigned int WAPIERR_PROCESS_NOTEXECUTED = 1002;

//Activity
const unsigned int WAPIERR_ACTIVITY				= 2000;

const unsigned int WAPIERR_ACTIVITY_NOT_FOUND	= 2001;
static char* WAPIERR_ACTIVITY_NOT_FOUND_DESCR	= "Activity not found";

const unsigned int WAPIERR_USER_NOGRANTS		= 2002;
static char* WAPIERR_USER_NOGRANTS_DESCR		= "User have not grants for activity";

const unsigned int WAPIERR_ACTIVITY_NO_RESULTCODE = 2003;
static char* WAPIERR_ACTIVITY_NO_RESULTCODE_DESCR = "Impossible to complete activity without ResultCode";

const unsigned int WAPIERR_ACTIVITY_NOTQUEUED	= 2004;
static char* WAPIERR_ACTIVITY_NOTQUEUED_DESCR = "Impossible to acquire activity.it's already assigned another user";

//Account  - Roles
const unsigned int WAPIERR_ROLES_ROLEKEY_NOTFOUND	= 3001;
static char* WAPIERR_ROLES_ROLEKEY_NOTFOUND_DESCR	= "RoleKey not found.";

const unsigned int WAPIERR_ROLES_ROLEKEY_ALREADY_EXIST	= 3002;
static char* WAPIERR_ROLES_ROLEKEY_ALREADY_EXIST_DESCR	= "RoleKey already exist.";

const unsigned int WAPIERR_ROLES_USERKEY_NOTFOUND	= 3003;
static char* WAPIERR_ROLES_USERKEY_NOTFOUND_DESCR	= "UserKey not found inside role.";

const unsigned int WAPIERR_ROLES_USERKEY_ALREADY_EXIST	= 3004;
static char* WAPIERR_ROLES_USERKEY_ALREADY_EXIST_DESCR	= "UserKey already exist inside role.";

//Account - Users
const unsigned int WAPIERR_USERS_USERKEY_NOTFOUND	= 3101;
static char* WAPIERR_USERS_USERKEY_NOTFOUND_DESCR	= "UserKey not found.";

const unsigned int WAPIERR_USERS_USERKEY_ALREADY_EXIST	= 3102;
static char* WAPIERR_USERS_USERKEY_ALREADY_EXIST_DESCR	= "UserKey already exist.";

//DataType
const unsigned int WAPIERR_DATATYPE_NOTFOUND	= 4101;
static char* WAPIERR_DATATYPE_NOTFOUND_DESCR	= "DataType not found.";

//Service
const unsigned int WAPIERR_SERVICE_NOTFOUND	= 5101;
static char* WAPIERR_SERVICE_NOTFOUND_DESCR	= "Service not found.";

const unsigned int WAPIERR_SERVICE_ALREADY_EXIST		= 5102;
static char* WAPIERR_SERVICE_ALREADY_EXIST_DESCR	= "Service already exist.";

const unsigned int WAPIERR_SERVICE_NOT_FOUND	= 5103;
static char* WAPIERR_SERVICE_NOT_FOUND_DESCR	= "Service not found.";

const unsigned int WAPIERR_GENERIC_ERROR				= 10000;

#endif //