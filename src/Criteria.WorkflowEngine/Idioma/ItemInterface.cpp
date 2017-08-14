#include "CommonDefines.h"

#include "ItemInterface.h"
using namespace WorkflowEngine::Idioma;

#include "Tracer.h"

unsigned int ItemInterface::CheckDelimiter( String sStatement, const String &sDelimiter )
{
	unsigned int uiSize = sDelimiter.size();

	if ( sStatement.size () < uiSize )
		return 0;

	if ( sStatement.substr (0, uiSize) == sDelimiter )
		return uiSize;

	return 0;
}

bool ItemInterface::isLiteralValue(String sValue)
{
	if ( sValue.find("\"") != -1 ) 
	{
		return true;
	}

	if ( isOnlyDigit(sValue) )
	{
		return true;
	}

	return false;
}

bool ItemInterface::isOnlyDigit(String sValue)
{
	unsigned int iSize = sValue.size();
	for ( unsigned int i=0; i<iSize;i++)
	{
		if ( !(isdigit(sValue.at(i)) ) )
		{

			return false;
		}
	}

	return true;
}


