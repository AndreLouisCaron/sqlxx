#ifndef _sql_mysql_hpp__
#define _sql_mysql_hpp__

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
 * @file mysql.hpp
 * @brief sqlxx MySQL support.
 *
 * @see sql::mysql
 */

#include "sql.hpp"

namespace sql {

    /*!
     * @brief Support for MySQL.
     *
     * @see sql.hpp
     * @see mysql.hpp
     * @see http://www.mysql.com/
     */
    namespace mysql {}

}

namespace sql { namespace mysql {

    /*!
     * @brief Direct connection to a MySQL 5.1 database.
     */
    class Connection :
        public Driver
    {
        /* construction. */
    public:
        /*!
         * @brief Connect to a MySQL database hosted on the current computer.
         * @param environment ODBC environment.
         * @param database Database name.
         * @param username Credentials.
         * @param password Credentials.
         */
        Connection (Environment& environment, const string& database,
                    const string& username, const string& password);

        /*!
         * @brief Connect to a MySQL database hosted on a remote computer.
         * @param environment ODBC environment.
         * @param database Database name.
         * @param username Credentials.
         * @param password Credentials.
         * @param hostname The server's host name or IP address.
         */
        Connection (Environment& environment,
                    const string& database, const string& username,
                    const string& password, const string& hostname);
    };

} }

#endif /* _sql_mysql_hpp__ */
