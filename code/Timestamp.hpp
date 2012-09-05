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
     * @brief Point in time with billionth of a second resolution.
     */
    class Timestamp
    {
        /* nested types. */
    public:
        /*!
         * @internal
         * @brief Native representation.
         */
        typedef ::SQL_TIMESTAMP_STRUCT Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        /*!
         * @brief Value-initialize.
         * @param date Date of the year.
         * @param time Time of the day.
         * @param fraction Fraction of a second.
         */
        Timestamp (const Date& date = Date(),
                   const Time& time = Time(),
                   uint32 fraction = 0)
        {
            this->date(date), this->time(time), this->fraction(fraction);
        }

        /*!
         * @internal
         * @brief Copy-initialize from the native representation.
         */
        Timestamp (const Value& value)
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
         * @brief Obtain the date and year.
         * @return The time of day.
         */
        Date date () const {
            return (Date(myValue.year,myValue.month,myValue.day));
        }

        /*!
         * @brief Change the date and year.
         * @param value New date an year.
         */
        void date (const Date& value)
        {
            myValue.year = value.year();
            myValue.month = value.month();
            myValue.day = value.day();
        }

        /*!
         * @brief Obtain the time of day (1 second resolution).
         * @return The time of day.
         */
        Time time () const {
            return (Time(myValue.hour,myValue.minute,myValue.second));
        }

        /*!
         * @brief Change the time of day (1 second resolution).
         * @param value New time of day.
         */
        void time (const Time& value)
        {
            myValue.hour = value.hour();
            myValue.minute = value.minute();
            myValue.second = value.second();
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

        /*!
         * @brief Obtain the hour component.
         * @return The current hour component.
         */
        uint16 hour () const {
            return (myValue.hour);
        }

        /*!
         * @brief Change the hour component.
         * @param value The new hour component.
         */
        void hour (uint16 value) {
            myValue.hour = value;
        }

        /*!
         * @brief Obtain the minute component.
         * @return The current minute component.
         */
        uint16 minute () const {
            return (myValue.minute);
        }

        /*!
         * @brief Change the minute component.
         * @param value The new minute component.
         */
        void minute (uint16 value) {
            myValue.minute = value;
        }

        /*!
         * @brief Obtain the second component.
         * @return The current second component.
         */
        uint16 second () const {
            return (myValue.second);
        }

        /*!
         * @brief Change the second component.
         * @param value The new second component.
         */
        void second (uint16 value) {
            myValue.second = value;
        }

        /*!
         * @brief Change the fraction component.
         * @param value The new fraction component.
         */
        void fraction (uint32 value) {
            myValue.fraction = value;
        }

        /*!
         * @brief Obtain the fraction component.
         * @return The current fraction component.
         */
        uint32 fraction () const {
            return (myValue.fraction);
        }

        /* operators. */
    public:
        /*!
         * @internal
         * @brief Copy-assign from the native representation.
         * @param value Value to copy.
         * @return @c *this, for method chaining.
         */
        Timestamp& operator= (const Value& value)
        {
            myValue = value;
            return (*this);
        }

        /*!
         * @brief Compare two timestamps for equality.
         * @param rhs Right-hand-side value.
         * @return @c true if the two values are exactly equal.
         *
         * Comparison is done for an exact match, at the billionth-of-a-second
         * resolution.  You may want to compare using some sort of tolerance.
         */
        bool operator== (const Timestamp& rhs) const {
            return (std::memcmp(&myValue,&rhs.myValue,sizeof(Value)) == 0);
        }

        /*!
         * @brief Compare two timestamps for inequality.
         * @param rhs Right-hand-side value.
         * @return @c true if the two values not are exactly equal.
         *
         * Comparison is done for an exact match, at the billionth-of-a-second
         * resolution.  You may want to compare using some sort of tolerance.
         */
        bool operator!= (const Timestamp& rhs) const {
            return (std::memcmp(&myValue,&rhs.myValue,sizeof(Value)) != 0);
        }
    };

    /*!
     * @brief Serialize the point in time.
     * @param stream Destination output stream.
     * @param value Value to write.
     * @return @a stream, for method chaining.
     */
    std::ostream& operator<< (std::ostream& stream, const Timestamp& value);

}

#endif /* _sql_Timestamp_hpp__ */
