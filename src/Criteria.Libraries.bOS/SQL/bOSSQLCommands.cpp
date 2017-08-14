#include "CommonDefines.h"

#include "bOSSQLCommands.h"
using namespace bOS::SQL;

SQLCommands::SQLCommands()
{
}

SQLCommands::~SQLCommands()
{
	unsigned int uiSize = vCommands.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		delete vCommands.at(i);
	}

	vCommands.clear();
}
