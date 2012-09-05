#ifndef _sql_odbc_hpp__
#define _sql_odbc_hpp__

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

/*!
 * @file odbc.hpp
 * @brief sqlxx ODBC support.
 *
 * @see sql::odbc
 */

#include <sql.hpp>

// Query list of available data sources by using: SQLDataSources().
//
// SQLDrivers() lists installed drivers and their attributes.

namespace sql {

    /*!
     * @brief Data source name (DSN)-based connection support.
     *
     * @see sql.hpp
     * @see odbc.hpp
     * @see http://en.wikipedia.org/wiki/ODBC
     */
    namespace odbc {}

}

namespace sql { namespace odbc {

    /*!
     * @brief Connection by data source name.
     */
    class Connection :
        public sql::Connection
    {
        /* construction. */
    public:
        /*!
         * @brief Connect to a registered ODBC connection.
         * @param environment ODBC environment.
         * @param database Database name.
         * @param username Credentials.
         * @param password Credentials.
         *
         * @todo Verify that @a database is the data source name.
         */
        Connection (Environment& environment, const string& database,
                    const string& username, const string& password);
    };

    /*!
     * @brief Iteratively build a database connection string.
     * @param connection Incomplete database connection.
     * @param settings Existing settings.
     * @return Additional settings to 
     *
     * Attempt a connection and return a non-empty string describing
     * missing parameters if connection string is incomplete. Returns
     * an empty string if the connection was successful.
     *
     * @todo Document the format used for @a settings and the return value.
     */
    sql::string browse (sql::Connection& connection,
                        const sql::string& settings);

} }

#endif /* _sql_odbc_hpp__ */
