#include "Application.h"
#include "ApplicationFunction.h"
#include "ApplicationFunctionResult.h"
#include "ApplicationFunctions.h"
#include "Applications.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

//XmlApplications
String XMLApplications::MAIN_NODE		= "Applications";

//XmlApplication
String XMLApplication::MAIN_NODE		= "Application";
String XMLApplication::NAME_ATTRIBUTE	= "Name";
String XMLApplication::TYPE_ATTRIBUTE	= "Type";
String XMLApplication::DLL_ATTRIBUTE	= "File";
String XMLApplication::HOST_NODE		= "Host";
String XMLApplication::PORT_NODE		= "Port";

String XMLApplication::EXECUTABLE_TYPE		= "CriteriaExecutable";
String XMLApplication::LIBRARY_TYPE			= "CriteriaLibrary";
String XMLApplication::PROCESS_TYPE			= "NativeExecutable";

//XmlApplicationFunctions
String XMLApplicationFunctions::MAIN_NODE	= "Functions";

//XmlApplicationFunction
String XMLApplicationFunction::MAIN_NODE		= "Function";
String XMLApplicationFunction::NAME_ATTRIBUTE	= "Name";
String XMLApplicationFunction::TYPE_ATTRIBUTE	= "Type";

String XMLApplicationFunction::SCRIPT_TYPE		= "SCRIPT";

//XmlApplicationFunctionResult
String XMLApplicationFunctionResult::MAIN_NODE			= "Result";
String XMLApplicationFunctionResult::MESSAGE_NODE		= "Message";
String XMLApplicationFunctionResult::CODE_ATTRIBUTE		= "Code";




