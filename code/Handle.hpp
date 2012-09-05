#ifndef _sql_Handle_hpp__
#define _sql_Handle_hpp__

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
#include "NotCopyable.hpp"

namespace sql {

    /*!
     * @internal
     * @brief Wrapper for SQL handle management.
     *
     * SQL handles are opaque "pointers" for any implementation of the SQL
     * concepts of environment, connection, statement, etc.  The handle points
     * to bookeeping data for the opaque object delivered by the driver and
     * should be handled with care.
     */
    class Handle :
        private NotCopyable
    {
        /* nested types. */
    public:
        /*!
         * @internal
         * @brief Native representation for handles, opaque "pointer".
         */
        typedef ::SQLHANDLE Value;

        /*!
         * @internal
         * @brief Handle type code.
         *
         * Can be one of:
         * - @c SQL_HANDLE_ENV;
         * - @c SQL_HANDLE_DBC; or
         * - @c SQL_HANDLE_STMT.
         */
        typedef ::SQLSMALLINT Type;

        /*!
         * @internal
         * @brief Cleanup function for handles.
         * @param value Handle value.
         * @param type Type of handle.
         *
         * @see claim
         * @see proxy
         */
        typedef void(*Cleanup)(Value value, Type type);

        /* class methods. */
    public:
        /*!
         * @internal
         * @brief Release the handle.
         * @param value Handle value.
         * @param type Type of handle.
         *
         * @see Cleanup
         * @see proxy
         */
        static void claim (Value value, Type type);

        /*!
         * @internal
         * @brief Abandon the handle.
         * @param value Handle value.
         * @param type Type of handle.
         *
         * @see Cleanup
         * @see claim
         */
        static void proxy (Value value, Type type);

        /* data. */
    private:
       Value myValue;
       Type myType;
       Cleanup myCleanup;

        /* construction. */
    public:
        /*!
         * @brief Wrap a handle.
         * @param value Environment, connection or statement handle.
         * @param type Type code for @a value.
         * @param cleanup Cleanup function for @a value.
         *
         * The handle will be released using @c cleanup(value,type).
         */
        Handle (Value value, Type type, Cleanup cleanup);

        /*!
         * @brief Release the handle using the cleanup function.
         */
        ~Handle ();

        /* methods. */
    public:
        /*!
         * @brief Compares the handle's value to the generic placeholder value
         *  for invalid handles.
         */
        bool bad () const throw();

        /*!
         * @brief Checks the handle's value against the generic placeholder
         *  value for invalid handles.
         */
        bool ok () const throw();

        /*!
         * @brief Obtains the handle's value, in it's native API representation.
         * @return The handle's native value.
         */
        Value value () const throw();

        /*!
         * @brief Obtains the typecode for the resource attached to the handle.
         * @return The handle's typecode.
         */
        Type type () const throw();
    };

}

#endif /* _sql_Handle_hpp__ */
