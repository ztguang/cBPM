#include "CommonDefines.h"

#include "bOSTime.h"
using namespace bOS::Utils;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

static const unsigned int   SECS_PER_DAY	= 86400;
static const unsigned int   MSECS_PER_DAY   = 86400000;
static const unsigned int   SECS_PER_HOUR   = 3600;
static const unsigned int   MSECS_PER_HOUR  = 3600000;
static const unsigned int   SECS_PER_MIN	= 60;
static const unsigned int   MSECS_PER_MIN   = 60000;


Time::Time()
{
    ds = 0;
}

Time::Time( int h, int m, int s, int ms )
{
    this->setTime( h, m, s, ms );
}

Time::~Time()
{
}

bool Time::isNull() const
{
    return (ds == NULL);
}

bool Time::isValid() const
{
    return ds < MSECS_PER_DAY;
}

int	Time::getHour() const
{
    return ds / MSECS_PER_HOUR;
}

int	Time::getMinutes() const
{
    return (ds % MSECS_PER_HOUR) / MSECS_PER_MIN;
}

int	Time::getSeconds() const
{
    return (ds / 1000) % SECS_PER_MIN;
}

int	Time::getMilliseconds() const
{
    return ds % 1000;
}

bool Time::setTime( int h, int m, int s, int ms )
{
    if ( !isValid(h, m, s, ms) ) 
    {
        // make this invalid
        ds = MSECS_PER_DAY;
        return false;
    }
    ds = (h * SECS_PER_HOUR + m * SECS_PER_MIN + s) * 1000 + ms;
    return true;
}


Time Time::addSeconds( int secs ) const
{
    return this->addMilliseconds( secs * 1000 );
}

int	Time::secondsTo( const Time& time ) const
{
    return ((int)time.ds - (int)ds) / 1000;
}

Time Time::addMilliseconds( int ms ) const
{
    Time t;
    if ( ms < 0 ) 
    {
        // % not well-defined for -ve, but / is.
        int negdays = (MSECS_PER_DAY - ms) / MSECS_PER_DAY;
        t.ds = ((int)ds + ms + negdays * MSECS_PER_DAY) % MSECS_PER_DAY;
    }
    else 
    {
        t.ds = ((int)ds + ms) % MSECS_PER_DAY;
    }
    return t;
}

int Time::millisecondsTo( const Time& time ) const
{
    return (int)time.ds - (int)ds;
}

bool Time::operator==( const Time& t ) const
{
    return ds == t.ds;
}

bool Time::operator!=( const Time& t ) const
{
    return ds != t.ds;
}

bool Time::operator<( const Time& t )	const
{
    return ds < t.ds;
}

bool Time::operator<=( const Time& t ) const
{
    return ds <= t.ds;
}

bool Time::operator>( const Time& t )	const
{
    return ds > t.ds;
}

bool Time::operator>=( const Time& t ) const
{
    return ds >= t.ds;
}

Time Time::getCurrentTime()
{
    Time ct;
    currentTime( &ct );
    return ct;
}

void Time::set2CurrentTime()
{
	this->currentTime(this);
}

bool Time::isValid( int h, int m, int s, int ms )
{
    return (unsigned int)h < 24 && (unsigned int)m < 60 && 
        (unsigned int)s < 60 && (unsigned int)ms < 1000;
}

String Time::toString()
{
    int h = 0;
    int m = 0;
    int s = 0;
    long ms = 0;

    if ( this->isValid() )
    {
        h = this->getHour();
        m = this->getMinutes();
        s = this->getSeconds();
        ms = this->getMilliseconds();
    }
    else
    {
        Time t = getCurrentTime();
        h = t.getHour();
        m = t.getMinutes();
        s = t.getSeconds();
        ms = t.getMilliseconds();
    }
    String formatText = "%02i:%02i:%02i.%03i";
    return StringUtils::format( formatText, h, m, s, ms );
}

bool Time::currentTime( Time* time )
{
    if ( time == NULL ) 
    {
        return false;
    }

    #ifdef _BOS_ON_WIN32_
        SYSTEMTIME t;
        GetLocalTime( &t );
        time->ds = MSECS_PER_HOUR * t.wHour + MSECS_PER_MIN * t.wMinute + 
                 1000 * t.wSecond + t.wMilliseconds;
        return (t.wHour == 0 && t.wMinute == 0);
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        struct timeval tv;
        gettimeofday( &tv, 0 );
        time_t ltime = tv.tv_sec;
        tm* t = localtime( &ltime );
        time->ds = (unsigned int)( MSECS_PER_HOUR * t->tm_hour + MSECS_PER_MIN * t->tm_min +
                                 1000 * t->tm_sec + tv.tv_usec / 1000 );
        return (t->tm_hour== 0 && t->tm_min == 0);
    #endif
}
