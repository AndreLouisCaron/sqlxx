#ifndef _sql_Driver_hpp__
#define _sql_Driver_hpp__

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
#include "Connection.hpp"

namespace sql {

        /*!
         * @brief Connects to a database using a specific driver and a
         *    connection string to pass it some parameters.
         *
         * This class is useful when you want to use a specific database type
         * and specific driver. If you want more flexibility, you can factor
         * this out of your code by configuring an ODBC connection.
         */
    class Driver :
        public Connection
    {
        /* construction. */
    public:
            /*!
             * @brief Attemps to open a database connection.
             *
             * @param environment General SQL/ODBC parameters.
             * @param how Connection string which specifies which driver to
             *    use and more parameters that depend strongly on that specific
             *    driver. For drivers who support remote access (some don't),
             *    the hostname or protocol information are required by the
             *    driver to open the connection.
             */
        Driver ( Environment& environment, const string& how );

            /*!
             * @brief Closes the connection to the database.
             *
             * All operations, unless rolled back, will be commited
             * automatically.
             */
        virtual ~Driver ();
    };

}

#endif /* _sql_Driver_hpp__ */
