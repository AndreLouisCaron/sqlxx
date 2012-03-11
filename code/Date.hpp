#ifndef _sql_Date_hpp__
#define _sql_Date_hpp__

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
#include <iosfwd>
#include <string>

namespace sql {

        /*!
         * @brief Group of (year,month,day) values.
         */
    class Date
    {
        /* nested types. */
    public:
        typedef ::SQL_DATE_STRUCT Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Date () {
            myValue.year = 0, myValue.month = 0, myValue.day = 0;
        }

        Date ( int16 year, uint16 month, uint16 day ) {
            myValue.year = year, myValue.month = month, myValue.day = day;
        }

        Date ( const Value value )
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

        /* operators. */
    public:
        Date& operator= ( const Value& value )
        {
            myValue = value;
            return (*this);
        }

        bool operator== ( const Date& other ) const {
            return (std::memcmp(&myValue,&other.myValue,sizeof(Value)) == 0);
        }

        bool operator!= ( const Date& other ) const {
            return (std::memcmp(&myValue,&other.myValue,sizeof(Value)) != 0);
        }

        operator std::string() const;
        operator std::wstring() const;
    };

    std::ostream& operator<< ( std::ostream& out, const Date& value );
    std::wostream& operator<< ( std::wostream& out, const Date& value );

}

#endif /* _sql_Date_hpp__ */
