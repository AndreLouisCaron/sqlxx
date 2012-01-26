#ifndef _sql_Timestamp_hpp__
#define _sql_Timestamp_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include "types.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include <cstring>
#include <iosfwd>

namespace sql {

        /*!
         * @brief Merged date and time of day values.
         */
    class Timestamp
    {
        /* nested types. */
    public:
        typedef ::SQL_TIMESTAMP_STRUCT Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Timestamp (
            const Date& date = Date(),
            const Time& time = Time(),
            uint32 fraction = 0
            )
        {
            this->date(date), this->time(time), this->fraction(fraction);
        }

        Timestamp ( const Value& value )
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

        Date date () const {
            return (Date(myValue.year,myValue.month,myValue.day));
        }

        void date ( const Date& value )
        {
            myValue.year = value.year();
            myValue.month = value.month();
            myValue.day = value.day();
        }

        Time time () const {
            return (Time(myValue.hour,myValue.minute,myValue.second));
        }

        void time ( const Time& value )
        {
            myValue.hour = value.hour();
            myValue.minute = value.minute();
            myValue.second = value.second();
        }

        int16 year () const {
            return (myValue.year);
        }

        void year ( int16 value ) {
            myValue.year = value;
        }

        uint16 month () const {
            return (myValue.month);
        }

        void month ( uint16 value ) {
            myValue.month = value;
        }

        uint16 day () const {
            return (myValue.day);
        }

        void day ( uint16 value ) {
            myValue.day = value;
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

        void fraction ( uint32 value ) {
            myValue.fraction = value;
        }

        uint32 fraction () const {
            return (myValue.fraction);
        }

        /* operators. */
    public:
        Timestamp& operator= ( const Value& value )
        {
            myValue = value;
            return (*this);
        }

        bool operator== ( const Timestamp& other ) const {
            return (std::memcmp(&myValue,&other.myValue,sizeof(Value)) == 0);
        }
    };

    std::ostream& operator<< ( std::ostream& out, const Timestamp& value );

}

#endif /* _sql_Timestamp_hpp__ */
