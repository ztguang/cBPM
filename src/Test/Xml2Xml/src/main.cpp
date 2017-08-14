#include "bOS/bOS.h"

#include "bOS/bOSXmlInitializer.h"
using namespace bOS::Xml;

#include "bOS/bOSXSLTManager.h"
#include "bOS/bOSXSLTException.h"
using namespace bOS::Xml::Xslt;

#include "bOS/bOSFileSystem.h"
using namespace bOS::IO;

int main(int argc, char* argv[])
{
	String sXmlIn;
	String sXslIn;
	String sXmlOut;

	// Lettura Parametri
	if( argc < 4 )
	{
		sXmlIn="C:\\Scenario\\ExecutionEnvironment\\database\\test\\xml-xslt\\PRO_01_01.xml";
		sXslIn="C:\\Scenario\\ExecutionEnvironment\\database\\test\\xml-xslt\\procedura2.xsl";
		sXmlOut="C:\\Scenario\\ExecutionEnvironment\\database\\test\\xml-xslt\\prova.html";
	}
	else
	{
		sXmlIn=argv[1];
		sXslIn=argv[2];
		sXmlOut=argv[3];
	}

	cout << "Source XML File[" << sXmlIn << "]" << endl;
	cout << "Source XSL File[" << sXslIn << "]" << endl;
	cout << "Target XML File[" << sXmlOut << "]" << endl;

	/*
	if ( !(FileSystem::getFileAttribute(sXmlIn) & FileSystem::Exists ) )
	{
		cout << "Source XML File[" << sXmlIn << "] doesn't not exist" << endl;
		return -1;
	}

	if ( !(FileSystem::getFileAttribute(sXslIn) & FileSystem::Exists ) )
	{
		cout << "Source XSL File[" << sXslIn << "] doesn't not exist" << endl;
		return -1;
	}

	if ( FileSystem::getFileAttribute(sXmlOut) & FileSystem::Exists )
	{
		cout << "Target XML File[" << sXmlOut << "] does exist. It'll be overwrite." << endl;
		
	}
	*/

	XmlInitializer::initialize();
	try
	{

		XSLTManager::byFile (sXmlIn.c_str(), sXslIn.c_str(), sXmlOut.c_str());
	}
	catch ( XSLTException& err)
	{
		cout << "Impossible to transform [" << sXmlIn << "] by [" << sXslIn << "]. " << err.getMessage() << endl;
	}

	XmlInitializer::terminate();

	return 0;
}
	
