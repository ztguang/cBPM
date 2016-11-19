#include "FunctionExecution.h"

#include "bOS/bOS.h"

#include "bOS/bOSXMLHelper.h"
#include "bOS/bOSXMLNode.h"
#include "bOS/bOSXMLException.h"

#include "bOS/bOSSockets.h"
#include "bOS/bOSSocketException.h"
using namespace bOS::Net;

#define MESSAGE_SIZE 80000

#include "bOS/Tracer.h"

FunctionExecution::FunctionExecution(SocketWrapper* sock)
{
	socket= sock;
}

FunctionExecution::~FunctionExecution()
{
}

void FunctionExecution::run()
{
	CM_CODEBLOCK(run)

	char buffer[MESSAGE_SIZE];
	int iLen=0;

	try
	{
		CM_TRACE_CODEPATH("Reading socket............");
		iLen = socket->read (buffer, MESSAGE_SIZE);
	}
	catch (const SocketRunTimeException &srtErr)
	{
		CM_TRACE_FATAL("Socket Exception[" << srtErr.what() << "]")
		delete socket;
		return;
	}
	catch ( const SocketLogicException &slErr)
	{
		CM_TRACE_FATAL("Socket Logic Exception[" << slErr.what() << "]")
		delete socket;
		return;
	}
		
	String sResult;
	ApplicationFunction function;

	if ( iLen ==  0 )
	{
		CM_TRACE_WARNING("no primtive received.")
		//TODO: I codici vanno inseriti in unico file e documentati.
		sResult = this->getXmlResult(1000, "no primtive received.");
	}
	else
	{
		buffer[iLen]='\0';
		CM_TRACE_DEBUG("Received[" << buffer << "] length[" << iLen << "]")

		try
		{
			bOS::XML::XMLNode* root= bOS::XML::XMLHelper::parseFromString (buffer);
			cout << "function parsed." << endl;

			function.init (root);
			delete root;
			
			ApplicationFunctions& functions = application->getFunctions ();
			
			ApplicationFunction* functionConfigured = functions.get(function.getName().c_str());
			
			if ( functionConfigured == NULL) 
			{
				CM_TRACE_FATAL("Primitive[" << function.getName() << "] not supported.")
				sResult = this->getXmlResult(1000, "Function not supported.");
			}
		}
		catch ( bOS::XML::XMLException& xmlErr)
		{
			CM_TRACE_FATAL("Function received Error[" << xmlErr.getMessage() << "]")
			sResult = this->getXmlResult(1000, "Function received Error");
		}
	}

	if ( sResult.length() == 0)
	{
		cout << "function parsed5." << endl;
		char* result=NULL;
		bool bCallBackNotFound=true;
		for ( int i=0; i<vCallBacks.size(); i++)
		{
			CallBackPrimitive& callback = vCallBacks.at(i);

			if ( callback.sFunction == function.getName () )
			{
				bCallBackNotFound=false;
				result=(*(callback.function))(buffer);
				break;
			}

			cout << "function parsed8." << endl;
		}

		if ( bCallBackNotFound ) 
		{
			if ( CallBackSpecial == NULL )
			{
				CM_TRACE_FATAL("Impossible to find function[" << function.getName () << "] in callback list.")
				sResult = this->getXmlResult(1000, "Impossible to find function in callback list.");
			}
			else
			{
				result=(*(CallBackSpecial->function))(buffer);
			}
		}
		
		if ( result == NULL )
		{
			CM_TRACE_FATAL("Impossible to retrieve response")
			sResult = this->getXmlResult(1000, "Impossible to find function in callback list.");
		}
		else
		{
			sResult = result;
		}
	}

	try
	{
		socket->write ( sResult.c_str(), sResult.length() +1);	
	}
	catch (const SocketRunTimeException &e)
	{
		CM_TRACE_FATAL("SocketException[" << e.what() << "]")
	}
	catch ( const SocketLogicException &slErr)
	{
		CM_TRACE_FATAL("Socket Logic Exception[" << slErr.what() << "]")
	}

	delete socket;
}

String FunctionExecution::getXmlResult(long lErrorCode, const char* acErr)
{
	ApplicationFunctionResult result;
	result.setCode(lErrorCode);
	result.setMessage(acErr);

	return result.getXMLString(1);
}