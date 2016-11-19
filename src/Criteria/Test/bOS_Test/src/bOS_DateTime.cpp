#include <conio.h>
#include <ctype.h>

#include "bOS/bOS.h"
#include "bOS/bOSDateTime.h"

void DateTime()
{
	bOS::Utils::DateTime dt = bOS::Utils::DateTime::getCurrentDateTime();

	cout << "Press a key" << endl;
	getch();

	bOS::Utils::DateTime dt2 = bOS::Utils::DateTime::getCurrentDateTime();

	int iSec = dt.secondsTo(dt2);

	cout << iSec << endl;
}