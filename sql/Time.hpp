#ifndef _sql_Time_hpp__
#define _sql_Time_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/types.hpp>
#include <iosfwd>
#include <string>

namespace sql {

        /*!
         * @brief Time of day: group of (hour,minute,second) values.
         */
    class Time
    {
        /* nested types. */
    public:
        typedef ::SQL_TIME_STRUCT Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Time () {
            myValue.hour = 0, myValue.minute = 0, myValue.second = 0;
        }

        Time ( uint16 hour, uint16 minute, uint16 second )
        {
            myValue.hour = hour;
            myValue.minute = minute;
            myValue.second = second;
        }

        Time ( const Value value )
            : myValue(value)
        {}

        /* methods. */
    public:
        Value& value () {
            return (myValue);
        }

        const Value& value () const {
            return (myValue);
        }

        uint16 hour () const {
            return (myValue.hour);
        }

        void hour ( uint16 value ) {
            myValue.hour = value;
        }

        uint16 minute () const {
            return (myValue.minute);
        }

        void minute ( uint16 value ) {
            myValue.minute = value;
        }

        uint16 second () const {
            return (myValue.second);
        }

        void second ( uint16 value ) {
            myValue.second = value;
        }

        /* operators. */
    public:
        Time& operator= ( const Value& value )
        {
            myValue = value;
            return (*this);
        }

        bool operator== ( const Time& other ) const {
            return (std::memcmp(&myValue,&other.myValue,sizeof(Value)) == 0);
        }

        bool operator!= ( const Time& other ) const {
            return (std::memcmp(&myValue,&other.myValue,sizeof(Value)) != 0);
        }

        operator std::string() const;
        operator std::wstring() const;
    };

    std::ostream& operator<< ( std::ostream& out, const Time& value );
    std::wostream& operator<< ( std::wostream& out, const Time& value );

}

#endif /* _sql_Time_hpp__ */
