#include "MathFunctions.h"

#include "Scenario/FormalParameters.h"
#include "Scenario/FormalParameter.h"
using namespace DataManager::Panorama::Common;

#include "Scenario/ApplicationFunction.h"
#include "Scenario/ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "Scenario/ApplicationTemplate.h"

#include <cmath>

const String OPERATOR1_PARAMETER	= "Operator1";
const String OPERATOR2_PARAMETER	= "Operator2";
const String RESULT_PARAMETER		= "Result";

MathFunctions::MathFunctions()
{
}

MathFunctions::~MathFunctions()
{
}

double MathFunctions::Add(double dAddend1, double dAddend2)
{
	return dAddend1 + dAddend2;
}

double MathFunctions::Sub(double dAddend1, double dAddend2)
{
	return dAddend1 - dAddend2;
}

double MathFunctions::Mul(double dAddend1, double dAddend2)
{
	return dAddend1 * dAddend2;
}

double MathFunctions::Div(double dDividend, double dDivisor)
{
	return dDividend / dDivisor;
}

int MathFunctions::Pot(int dBase, int dExp)
{
	int iResult=1;
	for ( int i=0;i<dExp; i++)
	{
		iResult*=dBase;
	}
	return iResult;
}

char* MathFunctions::Add(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	long lCode = 0;
	String sMessage="";
	
	double dOperator1;
	double dOperator2;
	double dResult;

	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), OPERATOR1_PARAMETER.c_str() ) )
		{
			dOperator1 = atof(parameter->getValue().c_str());
		}
		else if ( !strcmp(parameter->getName().c_str(), OPERATOR2_PARAMETER.c_str() ) )
		{
			dOperator2 = atof(parameter->getValue().c_str());
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.E' indispensabile indicare la superficie.";
		}
	}

	if ( lCode == 0 )
	{
		dResult = MathFunctions::Add(dOperator1, dOperator2);
	}

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);



	result.getParameters().addParameter ( FormalParameter(RESULT_PARAMETER, MathFunctions::Convert (dResult) ));


	return StringUtils::toChar (result.getXMLString(1));
}

char* MathFunctions::Sub(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	long lCode = 0;
	String sMessage="";
	
	double dOperator1;
	double dOperator2;
	double dResult;

	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), OPERATOR1_PARAMETER.c_str() ) )
		{
			dOperator1 = atof(parameter->getValue().c_str());
		}
		else if ( !strcmp(parameter->getName().c_str(), OPERATOR2_PARAMETER.c_str() ) )
		{
			dOperator2 = atof(parameter->getValue().c_str());
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.E' indispensabile indicare la superficie.";
		}
	}

	if ( lCode == 0 )
	{
		dResult = MathFunctions::Sub(dOperator1, dOperator2);
	}

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);

	result.getParameters().addParameter ( FormalParameter(RESULT_PARAMETER, MathFunctions::Convert ( dResult) ));


	return StringUtils::toChar (result.getXMLString(1));
}



char* MathFunctions::Mul(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	long lCode = 0;
	String sMessage="";
	
	double dOperator1;
	double dOperator2;
	double dResult;

	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), OPERATOR1_PARAMETER.c_str() ) )
		{
			dOperator1 = atof(parameter->getValue().c_str());
		}
		else if ( !strcmp(parameter->getName().c_str(), OPERATOR2_PARAMETER.c_str() ) )
		{
			dOperator2 = atof(parameter->getValue().c_str());
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.E' indispensabile indicare la superficie.";
		}
	}

	if ( lCode == 0 )
	{
		dResult = MathFunctions::Mul(dOperator1, dOperator2);
	}

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);

	result.getParameters().addParameter ( FormalParameter(RESULT_PARAMETER, MathFunctions::Convert ( dResult) ));


	return StringUtils::toChar (result.getXMLString(1));
}

char* MathFunctions::Div(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	long lCode = 0;
	String sMessage="";
	
	double dOperator1;
	double dOperator2;
	double dResult;

	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), OPERATOR1_PARAMETER.c_str() ) )
		{
			dOperator1 = atof(parameter->getValue().c_str());
		}
		else if ( !strcmp(parameter->getName().c_str(), OPERATOR2_PARAMETER.c_str() ) )
		{
			dOperator2 = atof(parameter->getValue().c_str());
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.E' indispensabile indicare la superficie.";
		}
	}

	if ( lCode == 0 )
	{
		dResult = MathFunctions::Div(dOperator1, dOperator2);
	}

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);

	result.getParameters().addParameter ( FormalParameter(RESULT_PARAMETER, MathFunctions::Convert ( dResult) ));


	return StringUtils::toChar (result.getXMLString(1));
}

double MathFunctions::Sqrt(double dAddend)
{
	return sqrt(dAddend);
}

int MathFunctions::Int(double dAddend)
{
	return dAddend;
}
char* MathFunctions::Sqrt(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	long lCode = 0;
	String sMessage="";
	
	double dOperator1;
	double dResult;

	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), OPERATOR1_PARAMETER.c_str() ) )
		{
			dOperator1 = atof(parameter->getValue().c_str());
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.E' indispensabile indicare la superficie.";
		}
	}

	if ( lCode == 0 )
	{
		dResult = MathFunctions::Sqrt(dOperator1);
	}

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);

	result.getParameters().addParameter ( FormalParameter(RESULT_PARAMETER, MathFunctions::Convert ( dResult) ));


	return StringUtils::toChar (result.getXMLString(1));
}

char* MathFunctions::Int(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	long lCode = 0;
	String sMessage="";
	
	double dOperator1;
	int iResult;

	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), OPERATOR1_PARAMETER.c_str() ) )
		{
			dOperator1 = atof(parameter->getValue().c_str());
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.E' indispensabile indicare la superficie.";
		}
	}

	if ( lCode == 0 )
	{
		iResult = MathFunctions::Int(dOperator1);
	}

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);

	result.getParameters().addParameter ( FormalParameter(RESULT_PARAMETER, MathFunctions::Convert ( iResult) ));


	return StringUtils::toChar (result.getXMLString(1));
}

char* MathFunctions::Pot(char* acFunction)
{
	ApplicationFunction function;
	function.init(acFunction);

	Common::FormalParameters& parameters = function.getParameters();

	long lCode = 0;
	String sMessage="";
	
	int iOperator1;
	int iOperator2;
	int iResult;

	int iSize = parameters.size();
	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		if ( !strcmp(parameter->getName().c_str(), OPERATOR1_PARAMETER.c_str() ) )
		{
			iOperator1 = atoi(parameter->getValue().c_str());
		}
		else if ( !strcmp(parameter->getName().c_str(), OPERATOR2_PARAMETER.c_str() ) )
		{
			iOperator2 = atoi(parameter->getValue().c_str());
		}
		else
		{
			lCode =1000;
			sMessage = "Parametro Errato.E' indispensabile indicare la superficie.";
		}
	}

	if ( lCode == 0 )
	{
		iResult = MathFunctions::Pot(iOperator1, iOperator2);
	}

	ApplicationFunctionResult result;
	result.setCode (lCode);
	result.setMessage (sMessage);

	result.getParameters().addParameter ( FormalParameter(RESULT_PARAMETER, MathFunctions::Convert ( iResult) ));


	return StringUtils::toChar (result.getXMLString(1));
}

ApplicationTemplate* application = NULL;

extern "C" DLL_MATH_FUNCTIONS_API void InstanceApplication(char* acApplicationName)
{
	if ( application == NULL)
	{	application = new ApplicationTemplate();
		application->init("MathFunctions");

		/*
		*/
		application->addCallBack("Add", MathFunctions::Add);
		application->addCallBack("Sub", MathFunctions::Sub);
		application->addCallBack("Mul", MathFunctions::Mul);
		application->addCallBack("Div", MathFunctions::Div);
		application->addCallBack("Pot", MathFunctions::Pot);
		application->addCallBack("Sqrt", MathFunctions::Sqrt);
		application->addCallBack("Int", MathFunctions::Int);
	}
}

extern "C" DLL_MATH_FUNCTIONS_API void DeleteApplication(char* acApplicationName)
{
	//TODO: delete application;
}

extern "C" DLL_MATH_FUNCTIONS_API char* ExecuteApplicationApi(char* acFunction)
{
	return application->executeApi (acFunction);
}

String MathFunctions::Convert(double dValue)
{
	char tmp[50];
    memset( tmp, 0, 50);
    sprintf( tmp, "%.2f", dValue );

    return String( tmp );
}