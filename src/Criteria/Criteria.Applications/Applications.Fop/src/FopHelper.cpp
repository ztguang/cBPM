#include "FopHelper.h"

#include "ApplicationDataModel/ApplicationFunction.h"
#include "ApplicationDataModel/ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "JniHelper/JniInvoker.h"
using namespace JniHelper;

FopHelper::FopHelper(const String& sClassPath)
{
}

FopHelper::~FopHelper()
{
}

char* FopHelper::createPdf(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	int iSize = parameters.size();

	String sPdfFile;
	String sXslFile;
	String sXmlFile;

	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);
		if ( !strcmp(parameter->getName().c_str(), "XML_FILE") )
		{
			sXmlFile = parameter->getValue();
		}
		else if ( !strcmp(parameter->getName().c_str(), "XSL_FILE") )
		{
			sXslFile = parameter->getValue();
		}
		else if ( !strcmp(parameter->getName().c_str(), "PDF_FILE") )
		{
			sPdfFile = parameter->getValue();
		}
	}

	long lCode = 0;
	String sMessage;
	if ( (sPdfFile == "") || (sXmlFile == "") || (sXslFile == "") ) 
	{
		lCode = 1000;
		sMessage = "One or more parameter not sent";
	}
	else
	{
		String sArgs[3];
		sArgs[0] = sXmlFile;
		sArgs[1] = sXslFile;
		sArgs[2] = sPdfFile;

		//CM_SETTING_TO("JniHelperTest", CodeManager::CodeTracer::CODEBLOCK_LEVEL) 

		cout << "invoker" << endl;
		JniInvoker invoker("FOP_PATH");
		cout << "create JVM" << endl;
		invoker.createJVM();
		//String cargv[3] = {"C:\\mySoftware\\Scenario\\ExecutionEnvironment\\bin\\exit.xml", "C:\\mySoftware\\Scenario\\ExecutionEnvironment\\bin\\exit.xsl", "C:\\mySoftware\\Scenario\\ExecutionEnvironment\\bin\\exit.pdf"};

		try
		{
			cout << "Execute" << endl;
			invoker.execute("FOP","convertXML2PDF", 3, sArgs);
		}
		catch (runtime_error err)
		{
			lCode = 1000;
			sMessage = StringUtils::toChar(err.what());
		}
		catch ( ... )
		{
			lCode = 1000;
			sMessage = StringUtils::toChar("Unknow Error.");
		}

		cout << "Distroy" << endl;
		//invoker.destroyJVM();

		cout << "Return" << endl;



		//jni.execute("FOP","convertXML2PDF", 3, sArgs );
	}

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);

	return (char*)result.getXMLString(0).c_str();
}