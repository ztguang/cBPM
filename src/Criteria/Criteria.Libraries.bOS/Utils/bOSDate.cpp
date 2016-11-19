#include "CommonDefines.h"

#include "bOSDate.h"
using namespace bOS::Utils;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;


static const unsigned int   FIRST_DAY	    = 2361222;	// Julian day for 1752/09/14
static const int            FIRST_YEAR	    = 1752;		// ### wrong for many countries

static const short monthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date()
{
    jd = 0;
}

Date::Date( int y, int m, int d )
{
    jd = 0;
    setDate( y, m, d );
}

Date::~Date()
{
}

bool Date::isNull() const
{
    return jd == 0;
}

bool Date::isValid() const
{
    return jd >= FIRST_DAY;
}

int	Date::getYear() const
{
    int y = 0;
    int m = 0;
    int d = 0;
    julianToGregorian( jd, y, m, d );
    return y;
}

int	Date::getMonth() const
{
    int y = 0;
    int m = 0;
    int d = 0;
    julianToGregorian( jd, y, m, d );
    return m;
}

int	Date::getDay() const
{
    int y = 0;
    int m = 0;
    int d = 0;
    julianToGregorian( jd, y, m, d );
    return d;
}

int	Date::getDayOfWeek() const
{
    return (((jd + 1) % 7) + 6) % 7 + 1;
}

int	Date::getDayOfYear() const
{
    return jd - gregorianToJulian( getYear(), 1, 1 ) + 1;
}

int	Date::getDaysInMonth() const
{
    int y = 0;
    int m = 0;
    int d = 0;
    julianToGregorian( jd, y, m, d );
    if ( m == 2 && isLeapYear(y) )
	    return 29;
    else
	    return monthDays[m];
}

int	Date::getDaysInYear() const
{
    int y = 0;
    int m = 0;
    int d = 0;
    julianToGregorian( jd, y, m, d );
    return isLeapYear(y) ? 366 : 365;
}

String Date::getShortMonthName( int month )
{
    if ( month < 1 || month > 12 ) 
	    month = 1;

    String s = "";

    #ifdef _BOS_ON_WIN32_
        SYSTEMTIME st;
        memset( &st, NULL, sizeof(SYSTEMTIME) );
        st.wYear = 2000;
        st.wMonth = month;
        st.wDay = 1;
        char buffer[255];
        if ( GetDateFormatA( LOCALE_USER_DEFAULT, 0, &st, "MMM", (char*)&buffer, 255 ) )
            s = buffer;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        char buffer[255];
        tm tt;
        memset( &tt, 0, sizeof( tm ) );
        tt.tm_mon = month - 1;
        if ( strftime( buffer, sizeof( buffer ), "%b", &tt ) )
            s = buffer;
    #endif
    return s;
}

String Date::getShortDayName( int weekday )
{
    String s = "";

    if ( weekday < 1 || weekday > 7 ) 
	    weekday = 1;

    #ifdef _BOS_ON_WIN32_
        SYSTEMTIME st;
        memset( &st, NULL, sizeof(SYSTEMTIME) );
        st.wYear = 2001;
        st.wMonth = 10;
        st.wDayOfWeek = ( weekday == 7 ) ? 0 : weekday;
        st.wDay = 21 + st.wDayOfWeek;
        char buffer[255];
        if ( GetDateFormatA( LOCALE_USER_DEFAULT, 0, &st, "ddd", (char*)&buffer, 255 ) )
	        s = buffer;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        char buffer[255];
        tm tt;
        memset( &tt, NULL, sizeof( tm ) );
        tt.tm_wday = ( weekday == 7 ) ? 0 : weekday;
        if ( strftime( buffer, sizeof( buffer ), "%a", &tt ) )
	        s = buffer;
    #endif

    return s;
}

String Date::getLongMonthName( int month )
{
    String s = "";

    if ( month < 1 || month > 12 ) 
	    month = 1;

    #ifdef _BOS_ON_WIN32_
        SYSTEMTIME st;
        memset( &st, NULL, sizeof(SYSTEMTIME) );
        st.wYear = 2000;
        st.wMonth = month;
        st.wDay = 1 ;
        char buffer[255];
        if ( GetDateFormatA( LOCALE_USER_DEFAULT, 0, &st, "MMMM", (char*)&buffer, 255 ) )
	        s = buffer;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        char buffer[255];
        tm tt;
        memset( &tt, 0, sizeof( tm ) );
        tt.tm_mon = month - 1;
        if ( strftime( buffer, sizeof( buffer ), "%B", &tt ) )
	        s = buffer;
    #endif

    return s;
}

String Date::getLongDayName( int weekday )
{
    String s = "";
    if ( weekday < 1 || weekday > 7 ) 
	    weekday = 1;

    #ifdef _BOS_ON_WIN32_
        SYSTEMTIME st;
        memset( &st, NULL, sizeof(SYSTEMTIME) );
        st.wYear = 2001;
        st.wMonth = 10;
        st.wDayOfWeek = ( weekday == 7 ) ? NULL : weekday;
        st.wDay = 21 + st.wDayOfWeek;
        char buffer[255];
        if ( GetDateFormatA( LOCALE_USER_DEFAULT, 0, &st, "dddd", (char*)&buffer, 255 ) )
	        s = buffer;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        char buffer[255];
        tm tt;
        memset( &tt, NULL, sizeof( tm ) );
        tt.tm_wday = ( weekday == 7 ) ? NULL : weekday;
        if ( strftime( buffer, sizeof( buffer ), "%A", &tt ) )
	        s = buffer;
    #endif

    return s;
}

bool Date::setDate( int y, int m, int d )
{
    if ( getYear() == y && getMonth() == m && getDay() == d )
        return isValid();

    if ( !isValid(y,m,d) ) 
    {
        return false;
    }
    jd = gregorianToJulian( y, m, d );
    return true;
}

Date Date::addDays( int days ) const
{
    Date d;
    d.jd = jd + days;
    return d;
}

Date Date::addMonths( int months ) const
{
    int y = 0;
    int m = 0;
    int d = 0;
    julianToGregorian( jd, y, m, d );

    while ( months != 0 ) 
    {
        if ( months < 0 && months + 12 <= 0 ) 
        {
            y--;
            months += 12;
        }
        else if ( months < 0 ) 
        {
            m += months;
            months = 0;
            if ( m <= 0 ) 
            {
                --y;
                m += 12;
            }
        }
        else if ( months - 12 >= 0 ) 
        {
            y++;
            months -= 12;
        }
        else if ( m == 12 ) 
        {
            y++;
            m = 0;
        }
        else 
        {
            m += months;
            months = 0;
            if ( m > 12 ) 
            {
                ++y;
                m -= 12;
            }
        }
    }

    Date tmp(y, m, 1);

    if ( d > tmp.getDaysInMonth() )
        d = tmp.getDaysInMonth();
    Date date(y, m, d);
    return date;
}

Date Date::addYears( int years ) const
{
    int y = 0;
    int m = 0;
    int d = 0;
    julianToGregorian( jd, y, m, d );
    y += years;
    Date date(y, m, d);
    return date;
}

int Date::daysTo( const Date& date ) const
{
    return date.jd - jd;
}

bool Date::operator==( const Date& d ) const
{
    return jd == d.jd;
}

bool Date::operator!=( const Date& d ) const
{
    return jd != d.jd;
}

bool Date::operator<( const Date& d )	const
{
    return jd < d.jd;
}

bool Date::operator<=( const Date& d ) const
{
    return jd < d.jd;
}

bool Date::operator>( const Date& d )	const
{
    return jd > d.jd;
}

bool Date::operator>=( const Date& d ) const
{
    return jd >= d.jd;
}

void Date::setCurrentDate(Date& d)
{
    #ifdef _BOS_ON_WIN32_
        SYSTEMTIME t;
        memset( &t, 0, sizeof(SYSTEMTIME) );
        GetLocalTime( &t );
        d.jd = gregorianToJulian( t.wYear, t.wMonth, t.wDay );
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        time_t ltime;
        time( &ltime );
        tm t;
        localtime_r( &ltime, &t );
        d.jd = gregorianToJulian( t.tm_year + 1900, t.tm_mon + 1, t.tm_mday );
    #endif

}

Date Date::getCurrentDate()
{
	Date d;

	setCurrentDate(d);

	return d;

}

void Date::set2CurrentDate()
{
	this->setCurrentDate(*this);
}

bool Date::isValid( int y, int m, int d )
{
    if ( y >= 0 && y <= 99 )
        y += 1900;
    else if ( y < FIRST_YEAR || (y == FIRST_YEAR && (m < 9 || (m == 9 && d < 14))) )
        return false;

    return (d > 0 && m > 0 && m <= 12) && 
        (d <= monthDays[m] || (d == 29 && m == 2 && isLeapYear(y)));
}

bool Date::isLeapYear( int year )
{
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

unsigned int Date::gregorianToJulian( int y, int m, int d )
{
    unsigned int c = 0;
    unsigned int ya = 0;
    if ( y <= 99 )
        y += 1900;
    if ( m > 2 ) 
    {
        m -= 3;
    }
    else 
    {
        m += 9;
        y--;
    }
    c = y;
    c /= 100;
    ya = y - 100 * c;
    return 1721119 + d + (146097 * c) / 4 + (1461 * ya) / 4 + (153 * m + 2) / 5;
}

void Date::julianToGregorian( unsigned int jd, int& y, int& m, int& d )
{
    unsigned int x = 0;
    unsigned int j = jd - 1721119;
    y = (j * 4 - 1) / 146097;
    j = j * 4 - 146097 * y - 1;
    x = j / 4;
    j = (x * 4 + 3) / 1461;
    y = 100 * y + j;
    x = (x * 4) + 3 - 1461 * j;
    x = (x + 4) / 4;
    m = (5 * x - 3) / 153;
    x = 5 * x - 3 - 153 * m;
    d = (x + 5) / 5;
    if ( m < 10 ) 
    {
        m += 3;
    } 
    else 
    {
        m -= 9;
        y++;
    }
}

String Date::toString()
{
    int d = 0;
    int m = 0;
    int y = 0;

    if ( this->isValid() )
    {
        d = this->getDay();
        m = this->getMonth();
        y = this->getYear();
    }
    else
    {
        Date dt = getCurrentDate();
        d = dt.getDay();
        m = dt.getMonth();
        y = dt.getYear();
    }
    String formatText = "%02i/%02i/%04i";
    return StringUtils::format( formatText, d, m, y );
}
