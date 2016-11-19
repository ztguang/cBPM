#ifndef _BOS_SQL_COMMANDS_H_
#define _BOS_SQL_COMMANDS_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSSQLCommand.h"

namespace bOS
{
	namespace SQL
	{
		typedef vector<SQLCommand*> SQLCommandList;

		class BOS_API SQLCommands
		{
		public:
			SQLCommands();
			virtual ~SQLCommands();

			unsigned int size() { return vCommands.size();}
			SQLCommand* at(unsigned int i) { return vCommands.at(i);}
			void add(SQLCommand* command) { vCommands.push_back(command);}

		private:
			SQLCommandList vCommands;

		};
	}
}

#endif //_BOS_SQL_COMMAND_H_