#include "bOS/bOS.h"

#include <conio.h>
#include <ctype.h>

//bOS::IO
void ls(const char* sDir, const char* acExt);

//bOS::Sql
void mySql();

//bOS::Crypto
void RijnDael();
void RijnDaelFile();

//bOS::Utils
void DateTime();

int main()
{
	/*
	ls("c:\\mySoftware\\scenario\\executionenvironment\\database\\process", ".xml");
	getch();
	*/

	/*
	try
	{
		ConnectionManager manager(ODBC_STANDARD,1,1);
		manager.createPool ("ops$ull", "ull", "pitagora","");

		Connection* connection = manager.getFreeConnection ();
		manager.releaseConnection (connection);
	}
	catch ( SqlException& sqlErr)
	{
		cout << sqlErr.getMessage() << endl;
	}
	*/

	
	//mySql();

	DateTime();
	getch();
	

	//RijnDael();
	//RijnDaelFile();
	//getch();
}