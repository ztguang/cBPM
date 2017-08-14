#include <iostream>

#include "bOS/bOS.h"
#include "bOS/bOSString.h"
#include "bOS/bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOS/bOS.h"
#include "bOS/bOSXMLHelper.h"

#include "ApplicationTemplate/ApplicationTemplate.h"
#include "ApplicationTemplate/CallBackFunction.h"

#include "FopHelper.h"

#include "JniHelper/JniInvoker.h"
using namespace JniHelper;

#include "CodeManager/Tracer.h"

int main(int argc, char* argv[])
{
	CM_SETTING_TO("FopApplication", 7);
	CM_CODEBLOCK(main)

	/*
	String sAppName;
	String sClassPath;
	
	if ( argc < 3 )
	{
		CM_TRACE_ERROR("Impossible to start-up Application.Name and classpath is mandatory.")
		cout << "Impossible to start-up Application.Name is mandatory." << endl;
		exit(1);
	}
	else
	{
		sAppName = argv[1];
		sClassPath = argv[2];
		CM_TRACE_INFO("Application[" << sAppName << "] starting...............")
	}

	ApplicationTemplate application;
	FopHelper fop(sClassPath);

	//Adding CallBackFunction
	application.addCallBack("CreatePDF", fop.createPdf);

	application.startup (sAppName);
	*/

	if ( argc < 4 )
	{
		cout << "Impossible to start FopApplicacion. Missing Parameters." << endl;
		cout << "FopApplication XMLFILE XSLFILE PDFFILE" << endl; 

		return 1;
	}

	String sArgs[3];
	sArgs[0] = argv[1];
	sArgs[1] = argv[2];
	sArgs[2] = argv[3];
	JniInvoker invoker("FOP_PATH");
	invoker.createJVM();
	invoker.execute("FOP","convertXML2PDF", 3, sArgs);

	return 0;
}

