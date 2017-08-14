
#ifndef __BOS_DATETIME_H__
#define __BOS_DATETIME_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSDate.h"
#include "bOSTime.h"

namespace bOS
{
    namespace Utils
    {
        class BOS_API DateTime
        {
            public:

                DateTime();

                DateTime( const Date& dt );

                DateTime( const Date& dt, const Time& tm );

                virtual ~DateTime();

                bool isNull() const;

                bool isValid() const;

                Date getDate() const;

                Time getTime() const;


                void setDate( const Date& date );

                void setTime( const Time& time );

                void setTimeT( unsigned int secsSince1Jan1970UTC );

                time_t getTimeT() const;

                DateTime addDays( int days ) const;

                DateTime addMonths( int months ) const;

                DateTime addYears( int years ) const;

                DateTime addSeconds( int secs ) const;

                int daysTo( const DateTime& dt ) const;

                int secondsTo( const DateTime& dt ) const;

                bool operator==( const DateTime& dt ) const;

                bool operator!=( const DateTime& dt ) const;

                bool operator<( const DateTime& dt ) const;

                bool operator<=( const DateTime& dt ) const;

                bool operator>( const DateTime& dt ) const;

                bool operator>=( const DateTime& dt ) const;

                static DateTime getCurrentDateTime();

				void set2CurrentDateTime();

                static String getOracleDateTime( const String& s );

                String toString();

            private:

                Date d;
                Time t;

                //friend class DateTime;            //ztg delete
        };
    }
};

#endif



