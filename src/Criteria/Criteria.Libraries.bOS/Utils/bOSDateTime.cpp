#include "CommonDefines.h"

#include "bOSDateTime.h"
using namespace bOS::Utils;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;


static const unsigned int   SECS_PER_DAY	= 86400;
static const unsigned int   MSECS_PER_DAY   = 86400000;
static const unsigned int   SECS_PER_HOUR   = 3600;
static const unsigned int   MSECS_PER_HOUR  = 3600000;
static const unsigned int   SECS_PER_MIN	= 60;
static const unsigned int   MSECS_PER_MIN   = 60000;

DateTime::DateTime()
{
}

DateTime::DateTime( const Date& dt ) : d(dt)
{
}

DateTime::DateTime( const Date& dt, const Time& tm ) : d(dt), t(tm)
{
}

DateTime::~DateTime()
{
}

bool DateTime::isNull() const
{
    return d.isNull() && t.isNull();
}

bool DateTime::isValid() const
{
    return d.isValid() && t.isValid();
}

Date DateTime::getDate() const
{
    return d;
}

Time DateTime::getTime() const
{
    return t;
}

void DateTime::setDate( const Date& date )
{
    d = date;
}

void DateTime::setTime( const Time& time )
{
    t = time;
}

void DateTime::setTimeT( unsigned int secsSince1Jan1970UTC )
{
    time_t tmp = (time_t) secsSince1Jan1970UTC;
    tm* tM = localtime( &tmp );
    if ( !tM ) 
    {
        tM = gmtime( &tmp );
        if ( !tM ) 
        {
            d.jd = Date::gregorianToJulian( 1970, 1, 1 );
            t.ds = 0;
            return;
        }
    }
    d.jd = Date::gregorianToJulian( tM->tm_year + 1900, tM->tm_mon + 1, tM->tm_mday );
    t.ds = MSECS_PER_HOUR * tM->tm_hour + MSECS_PER_MIN * tM->tm_min + 1000 * tM->tm_sec;
}

time_t DateTime::getTimeT() const
{
	// Re-base our Julian Day to be equal to the UNIX epoch of
	// 01/01/1970 which has a JD of 2440588
	const long UnixReference = 2440588;
	time_t ret = (d.jd - UnixReference) * SECS_PER_DAY + (t.getMilliseconds() / 1000);
	return ret;
}

DateTime DateTime::addDays( int days ) const
{
    return DateTime( d.addDays(days), t );
}

DateTime DateTime::addMonths( int months ) const
{
    return DateTime( d.addMonths(months), t );
}

DateTime DateTime::addYears( int years ) const
{
    return DateTime( d.addYears(years), t );
}

DateTime DateTime::addSeconds( int secs ) const
{
    unsigned int dd = d.jd;
    int  tt = t.ds;
    int  sign = 1;
    if ( secs < 0 ) 
    {
        secs = -secs;
        sign = -1;
    }
    if ( secs >= (int)SECS_PER_DAY ) 
    {
        dd += sign * ( secs / SECS_PER_DAY );
        secs %= SECS_PER_DAY;
    }
    tt += sign * secs * 1000;
    if ( tt < 0 ) 
    {
        tt = MSECS_PER_DAY - tt - 1;
        dd -= tt / MSECS_PER_DAY;
        tt = tt % MSECS_PER_DAY;
        tt = MSECS_PER_DAY - tt - 1;
    } 
    else if ( tt >= (int)MSECS_PER_DAY ) 
    {
        dd += ( tt / MSECS_PER_DAY );
        tt = tt % MSECS_PER_DAY;
    }
    DateTime ret;
    ret.t.ds = tt;
    ret.d.jd = dd;
    return ret;
}

int DateTime::daysTo( const DateTime& dt ) const
{
    return d.daysTo( dt.d );
}

int DateTime::secondsTo( const DateTime& dt ) const
{
    return t.secondsTo(dt.t) + d.daysTo(dt.d) * SECS_PER_DAY;
}

bool DateTime::operator==( const DateTime& dt ) const
{
    return  t == dt.t && d == dt.d;
}

bool DateTime::operator!=( const DateTime& dt ) const
{
    return  t != dt.t || d != dt.d;
}

bool DateTime::operator<( const DateTime& dt ) const
{
    if ( d < dt.d )
        return true;
    return d == dt.d ? t < dt.t : false;
}

bool DateTime::operator<=( const DateTime& dt ) const
{
    if ( d < dt.d )
        return true;
    return d == dt.d ? t <= dt.t : false;
}

bool DateTime::operator>( const DateTime& dt ) const
{
    if ( d > dt.d )
        return true;
    return d == dt.d ? t > dt.t : false;
}

bool DateTime::operator>=( const DateTime& dt ) const
{
    if ( d > dt.d )
        return true;
    return d == dt.d ? t >= dt.t : false;
}

DateTime DateTime::getCurrentDateTime()
{
    Date cd = Date::getCurrentDate();
    Time ct;
    if ( Time::currentTime( &ct ) )      // too close to midnight?
        cd = Date::getCurrentDate();        // YES! then... voodoo, fetch date again
    return DateTime( cd, ct );
}

void DateTime::set2CurrentDateTime()
{
	d.set2CurrentDate();
	t.set2CurrentTime();
}

String DateTime::getOracleDateTime( const String& s )
{
    String result = "";
	String sDate;
    if ( s.empty() )
    {
        sDate = getCurrentDateTime().toString();
    }
	else
	{
		sDate = s;
	}

    result = "TO_DATE('";
    result += sDate;
    result += "', 'DD/MM/YYYY HH24:MI:SS')";
    return result;
}

String DateTime::toString()
{
    DateTime dt = getCurrentDateTime();
    String formatText = "%02i/%02i/%04i %02i:%02i:%02i";
    return StringUtils::format( formatText, 
        dt.d.getDay(), dt.d.getMonth(), dt.d.getYear(), 
        dt.t.getHour(), dt.t.getMinutes(), dt.t.getSeconds() );
}

