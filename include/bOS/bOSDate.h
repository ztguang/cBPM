#ifndef __BOS_DATE_H__
#define __BOS_DATE_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

namespace bOS
{
    namespace Utils
    {
        class BOS_API Date
        {
            public:
    
                Date();

                Date( int y, int m, int d );

                virtual ~Date();

                bool isNull() const;

                bool isValid() const;

                int	getYear() const;

                int	getMonth() const;

                int	getDay() const;

                int	getDayOfWeek() const;

                int	getDayOfYear() const;

                int	getDaysInMonth() const;

                int	getDaysInYear() const;

                static String getShortMonthName( int month );

                static String getShortDayName( int weekday );

                static String getLongMonthName( int month );

                static String getLongDayName( int weekday );

                bool setDate( int y, int m, int d );

                Date addDays( int days ) const;

                Date addMonths( int months ) const;

                Date addYears( int years ) const;

                int daysTo( const Date& date ) const;

                bool operator==( const Date& d ) const;

                bool operator!=( const Date& d ) const;

                bool operator<( const Date& d )	const;

                /**
                 * Returns TRUE if this date is earlier than or equal to d, 
                 * otherwise returns FALSE.
                 *
                 */
                bool operator<=( const Date& d ) const;

                /**
                 * Returns TRUE if this date is later than d, otherwise 
                 * returns FALSE.
                 *
                 */
                bool operator>( const Date& d )	const;

                /**
                 * Returns TRUE if this date is later than or equal to d,
                 * otherwise returns FALSE.
                 *
                 */
                bool operator>=( const Date& d ) const;

                /**
                 * Returns a Date object representing the current date
                 *
                 */
                static Date getCurrentDate();

				void set2CurrentDate();
				static void setCurrentDate(Date& d);

                /**
                 * Returns the current date, as reported by the system clock.
                 *
                 */
                static bool isValid( int y, int m, int d );

                /**
                 * Returns TRUE if the specified year year is a leap year.
                 *
                 */
                static bool isLeapYear( int year );

                /**
                 * Converts a Gregorian date to a Julian day.
                 * This algorithm is taken from Communications of the ACM, Vol 6, No 8.
                 *
                 * @see julianToGregorian()
                 *
                 */
                static unsigned int gregorianToJulian( int y, int m, int d );

                /**
                 * Converts a Julian day to a Gregorian date.
                 * This algorithm is taken from Communications of the ACM, Vol 6, No 8.
                 * 
                 * @see gregorianToJulian()
                 *
                 */
                static void julianToGregorian( unsigned int jd, int& y, int& m, int& d );

                /**
                 * Returns a String representation of this date object
                 *
                 */
                virtual String toString();
                
            private:

                unsigned int jd;

                friend class DateTime;
        };
    }
};

#endif



