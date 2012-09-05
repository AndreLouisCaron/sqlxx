#ifndef _sql_Time_hpp__
#define _sql_Time_hpp__

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
     * @brief Time of day: group of (hour,minute,second) values.
     */
    class Time
    {
        /* nested types. */
    public:
        /*!
         * @internal
         * @brief Native representation.
         */
        typedef ::SQL_TIME_STRUCT Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        /*!
         * @brief Default-initialize to 00:00:00.
         */
        Time () {
            myValue.hour = 0, myValue.minute = 0, myValue.second = 0;
        }

        /*!
         * @brief Value-initialize to hh:mm:ss.
         * @param hour Hour of the day.
         * @param minute Minute in @a hour.
         * @param second Second in @a minute.
         */
        Time (uint16 hour, uint16 minute, uint16 second)
        {
            myValue.hour = hour;
            myValue.minute = minute;
            myValue.second = second;
        }

        /*!
         * @internal
         * @brief Copy-initialize from the native representation.
         */
        Time (const Value& value)
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

        /* operators. */
    public:
        /*!
         * @internal
         * @brief Assign directly from the native representation.
         * @return @c *this, for method chaining.
         */
        Time& operator= (const Value& value)
        {
            myValue = value;
            return (*this);
        }

        /*!
         * @brief Compare two times of day for equality.
         * @param rhs Time of day to compare with.
         * @return @c *this, for method chaining.
         */
        bool operator== (const Time& rhs) const {
            return (std::memcmp(&myValue,&rhs.myValue,sizeof(Value)) == 0);
        }

        /*!
         * @brief Compare two times of day for inequality.
         * @param rhs Time of day to compare with.
         * @return @c *this, for method chaining.
         */
        bool operator!= (const Time& rhs) const {
            return (std::memcmp(&myValue,&rhs.myValue,sizeof(Value)) != 0);
        }

        /*!
         * @brief Convert the time to a string.
         * @return *this, formatted as a string.
         *
         * @see operator<<(std::ostream&,const Time&)
         */
        operator std::string () const;

        /*!
         * @brief Convert the time to a string.
         * @return *this, formatted as a string.
         *
         * @see operator<<(std::wostream&,const Time&)
         */
        operator std::wstring () const;
    };

    /*!
     * @brief Serialize the time of day.
     * @param stream Destination output stream.
     * @param value Value to write.
     * @return @a stream, for method chaining.
     */
    std::ostream& operator<< (std::ostream& stream, const Time& value);

    /*!
     * @brief Serialize the time of day.
     * @param stream Destination output stream.
     * @param value Value to write.
     * @return @a stream, for method chaining.
     */
    std::wostream& operator<< (std::wostream& stream, const Time& value);

}

#endif /* _sql_Time_hpp__ */
