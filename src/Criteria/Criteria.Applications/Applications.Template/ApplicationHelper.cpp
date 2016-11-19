#include "ApplicationHelper.h"

#include "bOS/bOS.h"

#include "bOS/bOSXMLHelper.h"

#include "bOS/bOSSockets.h"
#include "bOS/bOSSocketException.h"
using namespace bOS::Net;

#include "bOS/bOSFile.h"

#include "Criteria/Applications.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "Criteria/DataBaseHelper.h"
#include "Criteria/DBException.h"
using namespace DataManager::DataBase;

#include "FunctionExecution.h"

#include "bOS/Tracer.h"

ApplicationTemplate::ApplicationTemplate()
{
	
	CM_CODEBLOCK(ApplicationTemplate)
	
	bOS::XML::XMLHelper::initialize();

	CallBackSpecial = NULL;

	/*try
	{*/
	//	DataBaseHelper::instance()->open();
	/*}
	catch (DBException& dbErr ) 
	{
		CM_TRACE_ERROR("Error instancing DB[" << dbErr.getMessage() << "]")
		response->iCode = WAPI_DATABASE_INSTANCE_ERROR;
		strcpy(response->sMsg,dbErr.getMessage().c_str());
	}
	catch ( WorkflowException& wfErr) 
	{
		CM_TRACE_ERROR("Error instancing Engine[" << wfErr.getMessage() << "]")
		response->iCode = WAPI_ENGINE_INSTANCE_ERROR;
		strcpy(response->sMsg,wfErr.getMessage().c_str());
	}
	catch ( ... )
	{
		CM_TRACE_ERROR("Error instancing DB-Engine[Unknow Error]")
		response->iCode = WAPI_INSTANCE_ERROR;
		response->sMsg = "Unknow Error";
	}
	*/
}

ApplicationTemplate::~ApplicationTemplate()
{
	DataBaseHelper::deinstance();
	bOS::XML::XMLHelper::terminate();
}

bool ApplicationTemplate::init(const String& sApplicationName)
{
	CM_CODEBLOCK(ApplicationTemplate::init)

	StringBuffer sbConfigFile;
	sbConfigFile.append (sApplicationName.c_str());
	sbConfigFile.append (".xml");

	CM_TRACE_CODEPATH("Reading Application Configuration File[" << sbConfigFile.getData() << "]")

	//Reading Configuration File
	application.setName ( sApplicationName);
	application.init( bOS::IO::File (sbConfigFile.getData()) );
	return true;
}

void ApplicationTemplate::startup (const String& sApplicationName)
{
	CM_CODEBLOCK(ApplicationTemplate::startup)

	this->init (sApplicationName);

	if ( socketsInit() == false ) 
	{
		CM_TRACE_FATAL("Cannot initialize sockets for Application[" << sApplicationName << "]")
		cout << "Cannot initialize sockets for Application[" << sApplicationName << "]" << endl;
	}

	try
	{
		SocketWrapper sockserver;

		CM_TRACE_CODEPATH("listen on port[" << application.getPort() << "] for Application[" << sApplicationName << "]")
		sockserver.listen(application.getPort());

		while ( true )
		{
			// accept connection from client
			SocketWrapper* sock = new SocketWrapper(sockserver.accept());
			CM_TRACE_CODEPATH("A new API Execution request is accept for Application[" << sApplicationName << "]")

			FunctionExecution* execution = new FunctionExecution(sock);
			execution->setDaemon(true);
			execution->setCallBacks(vCallBacks);
			execution->setApplication(&application);
			execution->setSpecialCallBack ( CallBackSpecial );
			execution->start();
		}

	}
	catch (const SocketRunTimeException &e)
	{
		cout << "socket exception: " << e.what() << endl;
	}
	

	socketsEnd();

}

char* ApplicationTemplate::executeApi(char* acFunction)
{
	ApplicationFunction function;
	
	bool bRet = function.init (acFunction);
	if ( !bRet ) 
	{
		cout << "Function received Error" << endl;
		//TODO: Error to manage
	}

	ApplicationFunctions& functions = application.getFunctions ();
	ApplicationFunction* functionConfigured = functions.get (function.getName().c_str());

	if ( functionConfigured == NULL) 
	{
		cout << "Primitive not supported." << endl;
	}

	char* result=NULL;
	for ( unsigned int i=0; i<vCallBacks.size(); i++)
	{
		CallBackPrimitive& callback = vCallBacks.at(i);

		if ( callback.sFunction == function.getName () )
		{
			//result = (*(callback.function))(buffer);
			 result=(*(callback.function))(acFunction);
			break;
		}
	}

	if ( result == NULL )
	{
		cout << "Impossible to retrieve response" << endl;
	}

	return result;
}


void ApplicationTemplate::addCallBack(const String& sFunctionName, CallBackFunction function)
{
	vCallBacks.push_back ( CallBackPrimitive(sFunctionName, function));
}

void ApplicationTemplate::addSpecialCallBack(const String& sFunctionName, CallBackFunction function)
{
	CallBackSpecial = new CallBackPrimitive(sFunctionName, function);
}

extern "C" APPLICATIONTEMPLATE_API ApplicationTemplate* CreateClass()
{
	cout << "CreateClass" << endl;
	return new ApplicationTemplate();
}

extern "C" APPLICATIONTEMPLATE_API void DeleteClass( ApplicationTemplate* instance )
{
	delete instance;
}

extern "C" APPLICATIONTEMPLATE_API void StartUp( ApplicationTemplate* instance, char* acApplicationName )
{
	instance->startup (acApplicationName);
}

extern "C" APPLICATIONTEMPLATE_API void AddSpecialCallBack( ApplicationTemplate* instance, CallBackFunction function, char* acFunctionName )
{
	instance->addSpecialCallBack(acFunctionName, function);
}

extern "C" APPLICATIONTEMPLATE_API void AddCallBack( ApplicationTemplate* instance, CallBackFunction function, char* acFunctionName )
{
	instance->addCallBack (acFunctionName, function);
}

extern "C" APPLICATIONTEMPLATE_API void GetFunctionParameters( char* acFunction, int* pSize, FunctionParameter** ppParam )
{
	ApplicationFunction function;
	function.init(acFunction);

	*pSize = function.getParameters().size();

	if ( *pSize == 0 )
	{
		return;
	}

	FunctionParameter* abcde=new FunctionParameter[(*pSize)];
	*ppParam = new FunctionParameter[(*pSize)];

	FunctionParameter* pCurrent = *ppParam;
	Common::FormalParameter* parameter = NULL;
	for ( int i=0; i<(*pSize); i++, pCurrent++ )
	{
		parameter = (Common::FormalParameter*)function.getParameters().at(i);
		pCurrent->acName = StringUtils::toChar (parameter->getName());
		pCurrent->acValue = StringUtils::toChar (parameter->getValue());
	}
}


extern "C" APPLICATIONTEMPLATE_API ApplicationFunctionResult* CreateResultClass(char* acMessage, int iCode)
{
	ApplicationFunctionResult* result = new ApplicationFunctionResult();
	result->setCode (iCode);
	result->setMessage (acMessage);

	return result;
}

extern "C" APPLICATIONTEMPLATE_API void DeleteResultClass(ApplicationFunctionResult* instance)
{
	delete instance;
}

extern "C" APPLICATIONTEMPLATE_API void AddResultParameter(ApplicationFunctionResult* instance, char* acName, char* acValue)
{
	Common::FormalParameters& parameters = instance->getParameters();

	Common::FormalParameter parameter;
	parameter.setName (acName);
	parameter.setValue (acValue);

	parameters.addParameter (parameter);
}

extern "C" APPLICATIONTEMPLATE_API void AddResultParameterType(ApplicationFunctionResult* instance, char* acName, char* acValue, char* acType)
{
	Common::FormalParameters& parameters = instance->getParameters();

	Common::FormalParameter parameter;
	parameter.setName (acName);
	parameter.setValue (acValue);
	parameter.setType (acType);

	parameters.addParameter (parameter);
}

extern "C" APPLICATIONTEMPLATE_API char* GetResultXml(ApplicationFunctionResult* instance)
{
	return StringUtils::toChar(instance->getXMLString(1));
}
