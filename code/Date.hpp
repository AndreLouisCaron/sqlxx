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
        /*!
         * @internal
         * @brief Native representation.
         */
        typedef ::SQL_DATE_STRUCT Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        /*!
         * @brief Default-initialize to 0000/00/00.
         */
        Date () {
            myValue.year = 0, myValue.month = 0, myValue.day = 0;
        }

        /*!
         * @brief Value-initialize to yyyy/mm/dd.
         * @param year Year component.
         * @param month Month component.
         * @param day Day component.
         */
        Date (int16 year, uint16 month, uint16 day) {
            myValue.year = year, myValue.month = month, myValue.day = day;
        }

        /*!
         * @internal
         * @brief Copy-initialize from the native representation.
         */
        Date (const Value& value)
            : myValue(value)
        {}

        /* methods. */
    public:
        /*!
         * @internal
         * @brief Access the native representation.
         * @return The wrapped value.
         */
        Value& value () {
            return (myValue);
        }

        /*!
         * @internal
         * @brief Access the native representation.
         * @return The wrapped value.
         */
        const Value& value () const {
            return (myValue);
        }

        /*!
         * @brief Obtain the year component.
         * @return The current year component.
         */
        int16 year () const {
            return (myValue.year);
        }

        /*!
         * @brief Change the year component.
         * @param value The new year component.
         */
        void year (int16 value) {
            myValue.year = value;
        }

        /*!
         * @brief Obtain the month component.
         * @return The current month component.
         */
        uint16 month () const {
            return (myValue.month);
        }

        /*!
         * @brief Change the month component.
         * @param value The new month component.
         */
        void month (uint16 value) {
            myValue.month = value;
        }

        /*!
         * @brief Obtain the day component.
         * @return The current day component.
         */
        uint16 day () const {
            return (myValue.day);
        }

        /*!
         * @brief Change the day component.
         * @param value The new day component.
         */
        void day (uint16 value) {
            myValue.day = value;
        }

        /* operators. */
    public:
        /*!
         * @internal
         * @brief Assign directly from the native representation.
         * @return @c *this, for method chaining.
         */
        Date& operator= (const Value& value)
        {
            myValue = value;
            return (*this);
        }

        /*!
         * @brief Compare two dates for equality.
         * @param rhs Right-hand-side argument to compare with.
         * @return @c *this, for method chaining.
         */
        bool operator== (const Date& rhs) const {
            return (std::memcmp(&myValue,&rhs.myValue,sizeof(Value)) == 0);
        }

        /*!
         * @brief Compare two dates for inequality.
         * @param rhs Right-hand-side argument to compare with.
         * @return @c *this, for method chaining.
         */
        bool operator!= (const Date& rhs) const {
            return (std::memcmp(&myValue,&rhs.myValue,sizeof(Value)) != 0);
        }

        /*!
         * @brief Convert the date to a string.
         * @return *this, formatted as a string.
         *
         * @see operator<<(std::ostream&,const Date&)
         */
        operator std::string() const;

        /*!
         * @brief Convert the date to a string.
         * @return *this, formatted as a string.
         *
         * @see operator<<(std::wostream&,const Date&)
         */
        operator std::wstring() const;
    };

    /*!
     * @brief Serialize the date and year.
     * @param stream Destination output stream.
     * @param value Value to write.
     * @return @a stream, for method chaining.
     */
    std::ostream& operator<< (std::ostream& stream, const Date& value);

    /*!
     * @brief Serialize the date and year.
     * @param stream Destination output stream.
     * @param value Value to write.
     * @return @a stream, for method chaining.
     */
    std::wostream& operator<< (std::wostream& stream, const Date& value);

}

#endif /* _sql_Date_hpp__ */
