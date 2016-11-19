#include "DataBase/DataBase.h"
using namespace DataManager;

int main(int argc, char* argv[])
{
	CM_SETTING_BY_MAINARGS

	CM_CODEBLOCK(main)

	DataBase::instance();

	DataBase::instance()->drop();

	DataBase::instance()->create();

	DataBase::deinstance();
	
	
	return 0;
}