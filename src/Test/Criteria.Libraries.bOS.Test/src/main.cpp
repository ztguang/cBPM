#include "bOS/bOS.h"

#include <conio.h>
#include <ctype.h>

//bOS::IO
void ls(const char* sDir, const char* acExt);

//bOS::Sql
void mySql();

void sqlite3();

//bOS::Utils
void DateTime();

int main()
{
	sqlite3();
	getch();
}