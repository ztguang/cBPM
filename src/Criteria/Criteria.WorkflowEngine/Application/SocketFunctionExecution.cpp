#include "SocketFunctionExecution.h"
#include "ApplicationException.h"
using namespace WorkflowEngine;

#include "Applications.h"
#include "Application.h"
#include "ApplicationFunction.h"

#include "bOS.h"
#include "bOSSockets.h"
#include "bOSSocketException.h"
using namespace bOS::Net;

#include "Tracer.h"

SocketFunctionExecution::SocketFunctionExecution(Application* application, ApplicationFunction* function) : 
	FunctionExecution(application, function)
{
	sHost = application->getHost();
	iPort = application->getPort();
}

SocketFunctionExecution::~SocketFunctionExecution()
{
}

const char* SocketFunctionExecution::run()
{
	CM_CODEBLOCK(SocketFunctionExecution::run)

	if (socketsInit() == false)
	{
		CM_TRACE_ERROR("Impossible to execute function." << SOCKET_NOT_INITIALIZE)
		throw ChannelException(SOCKET_NOT_INITIALIZE);
	}

	char acReceive[1001];
	char* acCopy=NULL;
	ChannelException* exception = NULL;

	try
	{
		SocketWrapper sock;

		CM_TRACE_CODEPATH("Connecting to [" << sHost << "] Port[" << iPort << "]")
		sock.connect(sHost.c_str(), iPort);

		CM_TRACE_CODEPATH("Writing [" << sFunction << "]")
		sock.write(sFunction.c_str(), sFunction.length());

		CM_TRACE_CODEPATH("Reading .......")
		int i = 0;
		while (( i = sock.read(acReceive, 1000) ) == 1000)
		{
			acReceive[i]='\0';
			sResultFromExecution.append (acReceive);
		}

		if ( i > 0) 
		{
			acReceive[i]='\0';
			sResultFromExecution.append (acReceive);
		}

		CM_TRACE_DEBUG("Received buff[" << sResultFromExecution.getData() << "] i [" << i << "]")

	}
	catch (const SocketRunTimeException &e)
	{
		CM_TRACE_ERROR("Impossible to execute function.[" << e.what() << "]")
		exception = new ChannelException(e.what());
	}

	socketsEnd();

	if ( exception != NULL ) 
	{
		throw exception;
	}
	
	return sResultFromExecution.getData();
}