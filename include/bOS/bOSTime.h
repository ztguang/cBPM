#ifndef __BOS_TIME_H__
#define __BOS_TIME_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

namespace bOS
{
    namespace Utils
    {
        class BOS_API Time
        {
            public:
    
                Time();

                Time( int h, int m, int s = 0, int ms = 0 );

                virtual ~Time();

                bool isNull() const;

                bool isValid() const;

                int	getHour() const;

                int	getMinutes() const;

                int	getSeconds() const;

                int	getMilliseconds() const;

                bool setTime( int h, int m, int s, int ms = 0 );

                Time addSeconds( int secs ) const;

                int	secondsTo( const Time& time ) const;

                Time addMilliseconds( int ms ) const;

                int millisecondsTo( const Time& time ) const;

                bool operator==( const Time& t ) const;

                bool operator!=( const Time& t ) const;

                bool operator<( const Time& t )	const;

                bool operator<=( const Time& t ) const;

                bool operator>( const Time& t )	const;

                bool operator>=( const Time& t ) const;

                static Time getCurrentTime();

				void set2CurrentTime();

                static bool isValid( int h, int m, int s, int ms = 0 );

                virtual String toString();

            private:

                static bool currentTime( Time* time );

                unsigned int ds;

                friend class DateTime;
				friend class Timer;
        };
    }
};

#endif



