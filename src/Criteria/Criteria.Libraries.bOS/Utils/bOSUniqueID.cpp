#include "CommonDefines.h"

#include "bOSUniqueID.h"

#include "bOSDateTime.h"
using namespace bOS::Utils;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;


UniqueID::UniqueID()
{
}

UniqueID::~UniqueID()
{
}

String UniqueID::getNewValue()
{
	srand(time(NULL));

	/*
	return StringUtils::format("%x%x-%x-%x-%x-%x%x%x", 
    rand(), rand(),                 // Generates a 64-bit Hex number
    rand(),                         // Generates a 32-bit Hex number
    ((rand() & 0x0fff) | 0x4000),   // Generates a 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
    rand() % 0x3fff + 0x8000,       // Generates a 32-bit Hex number in the range [0x8000, 0xbfff]
    rand(), rand(), rand());        // Generates a 96-bit Hex number
	*/

	DateTime dt = DateTime::getCurrentDateTime();
    String formatText = "%04i-%02i%02i-%02i%02i-%02i%02i-%04i";
	
	return StringUtils::format( formatText, 
		dt.getDate().getYear(), dt.getDate().getMonth(), dt.getDate().getDay(), 
		dt.getTime().getHour(), dt.getTime().getMinutes(), dt.getTime().getSeconds(),dt.getTime().getMilliseconds(),rand() );
	
}
