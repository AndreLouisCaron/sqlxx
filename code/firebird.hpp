#ifndef _sql_firebird_hpp__
#define _sql_firebird_hpp__

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
 * @file firebird.hpp
 * @brief sqlxx Firebird support.
 *
 * @see sql::firebird
 */

#include "sql.hpp"

namespace sql {

    /*!
     * @brief Support for Firebird.
     *
     * @see sql.hpp
     * @see firebird.hpp
     * @see http://www.firebirdsql.org/
     */
    namespace firebird {}

}

namespace sql { namespace firebird {

    /*!
     * @brief Direct connection to a Firbired 2.x database.
     */
    class Connection :
        public Driver
    {
        /* construction. */
    public:
        /*!
         * @brief Connect to a Firebird database hosted on the current computer.
         * @param environment ODBC environment.
         * @param database Database name.
         * @param username Credentials.
         * @param password Credentials.
         */
        Connection (Environment& environment, const string& database,
                    const string& username, const string& password);
    };

} }

#endif /* _sql_firebird_hpp__ */
