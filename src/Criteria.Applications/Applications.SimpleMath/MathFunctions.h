#ifndef _DLL_MATH_FUNCTIONS_APPLICATION_H_
#define _DLL_MATH_FUNCTIONS_APPLICATION_H_

#ifdef DLL_MATH_FUNCTIONS_EXPORTS
	#define DLL_MATH_FUNCTIONS_API __declspec(dllexport)
#else
	#define DLL_MATH_FUNCTIONS_API __declspec(dllimport)
#endif

extern "C" DLL_MATH_FUNCTIONS_API void InstanceApplication(char*);
extern "C" DLL_MATH_FUNCTIONS_API void DeleteApplication(char*);
extern "C" DLL_MATH_FUNCTIONS_API char* ExecuteApplicationApi(char* );

#include "bOS/bOS.h"
#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "Scenario/CallBackFunction.h"

class DLL_MATH_FUNCTIONS_API MathFunctions
{
public:
	MathFunctions();
	~MathFunctions();

	static double Add(double dAddend1, double dAddend2);
	static double Sub(double dAddend1, double dAddend2);
	static double Mul(double dAddend1, double dAddend2);
	static double Div(double dDividend, double dDivisor);
	static int Pot(int dBase, int dExp);
	static double Sqrt(double dAddend);
	static int Int(double dAddend);

	static char* (CALLBACK Add)(char*);
	static char* (CALLBACK Sub)(char*);
	static char* (CALLBACK Mul)(char*);
	static char* (CALLBACK Div)(char*);
	static char* (CALLBACK Pot)(char*);
	static char* (CALLBACK Sqrt)(char*);
	static char* (CALLBACK Int)(char*);

//private:

	static String Convert(double dValue);

};

#endif //_DLL_MATH_FUNCTIONS_APPLICATION_H_