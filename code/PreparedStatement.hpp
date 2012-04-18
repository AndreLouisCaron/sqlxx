#ifndef _sql_PreparedStatement_hpp__
#define _sql_PreparedStatement_hpp__

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
#include "string.hpp"
#include "Date.hpp"
#include "Guid.hpp"
#include "Numeric.hpp"
#include "Statement.hpp"
#include "Time.hpp"
#include "Timestamp.hpp"

namespace sql {

    class Connection;

        /*!
         * @brief Fast, safe and convenient way to write queries.
         */
    class PreparedStatement :
        public Statement
    {
        /* nested types. */
    public:
            /*!
             * @brief Function that can be passed in a convenient fashion.
             */
        typedef PreparedStatement&(*Manipulator)(PreparedStatement&);

        /* data. */
    private:
        uint16 myNext;

        /* construction. */
    public:
        PreparedStatement ( Connection& connection, const string& query );

        /* methods. */
    public:
            /*!
             * @brief Makes the next call to \c bind() bind the value to the
             *    first parameter.
             *
             * You usually need this to call this between two different updates
             * on the same prepared update object.
             */
        PreparedStatement& reset ();

            /*!
             * @brief Binds a parameter as null (no value).
             */
        PreparedStatement& bind ( const Null& );

            /*!
             * @brief Binds a signed 8-bit integer to the next parameter.
             */
        PreparedStatement& bind ( const int8& value );

            /*!
             * @brief Binds an unsigned 8-bit integer to the next parameter.
             */
        PreparedStatement& bind ( const uint8& value );

            /*!
             * @brief Binds a signed 16-bit integer to the next parameter.
             */
        PreparedStatement& bind ( const int16& value );

            /*!
             * @brief Binds an unsigned 16-bit integer to the next parameter.
             */
        PreparedStatement& bind ( const uint16& value );

            /*!
             * @brief Binds a signed 32-bit integer to the next parameter.
             */
        PreparedStatement& bind ( const int32& value );

            /*!
             * @brief Binds an unsigned 32-bit integer to the next parameter.
             */
        PreparedStatement& bind ( const uint32& value );

            /*!
             * @brief Binds a signed 64-bit integer to the next parameter.
             */
        PreparedStatement& bind ( const int64& value );

            /*!
             * @brief Binds an unsigned 64-bit integer to the next parameter.
             */
        PreparedStatement& bind ( const uint64& value );

            /*!
             * @brief Binds a 32-bit floating point to the next parameter.
             */
        PreparedStatement& bind ( const float& value );

            /*!
             * @brief Binds a 64-bit floating point to the next parameter.
             */
        PreparedStatement& bind ( const double& value );

            /*!
             * @brief Binds a string to the next parameter.
             */
        PreparedStatement& bind ( const string& value );

            /*!
             * @brief Binds a wide string to the next parameter.
             */
        PreparedStatement& bind ( const wstring& value );

            /*!
             * @brief Binds a date value to the next parameter.
             */
        PreparedStatement& bind ( const Date& date );

            /*!
             * @brief Binds a unique identifier value to the next parameter.
             */
        PreparedStatement& bind ( const Guid& guid );

            /*!
             * @brief Binds a numeric value to the next parameter.
             */
        PreparedStatement& bind ( const Numeric& numeric );

            /*!
             * @brief Binds a time value to the next parameter.
             */
        PreparedStatement& bind ( const Time& time );

            /*!
             * @brief Binds a timestamp value to the next parameter.
             */
        PreparedStatement& bind ( const Timestamp& timestamp );

            /*!
             * @brief Applies a manipulator to the update object.
             */
        PreparedStatement& operator<< ( Manipulator manipulator ) {
            return ((*manipulator)(*this));
        }

        /* overrides. */
    public:
            /*!
             * @brief Executes as a prepared statement, and \c reset()s.
             */
        virtual PreparedStatement& execute ();
    };

        /*!
         * @brief Binds any supported value to the next available parameter.
         */
    template<typename Value>
    PreparedStatement& operator<<
        ( PreparedStatement& statement, const Value& value )
    {
        return (statement.bind(value));
    }

        /*!
         * @brief Make the next binding operation bind to the first parameter.
         */
    PreparedStatement& reset ( PreparedStatement& statement );

        /*!
         * @brief Send the query, then reset.
         */
    PreparedStatement& execute ( PreparedStatement& statement );

}

#endif /* _sql_PreparedStatement_hpp__ */
