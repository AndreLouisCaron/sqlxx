#ifndef _sql_Timestamp_hpp__
#define _sql_Timestamp_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
