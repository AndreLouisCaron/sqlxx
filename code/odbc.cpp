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

#include "odbc.hpp"

namespace sql { namespace odbc {

    Connection::Connection (Environment& environment, const string& database,
        const string& username, const string& password)
        : sql::Connection(environment)
    {
        const ::SQLRETURN result = ::SQLConnect(
            handle().value(),
            const_cast<character*>(database.data()), SQL_NTS,
            const_cast<character*>(username.data()), SQL_NTS,
            const_cast<character*>(password.data()), SQL_NTS
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
    }

    sql::string browse
        (sql::Connection& connection, const sql::string& how)
    {
            // Query the length of the output string.
        ::SQLSMALLINT size = 0;
        ::SQLRETURN result = ::SQLBrowseConnect(
            connection.handle().value(),
            const_cast<character*>(how.data()), SQL_NTS, 0, 0, &size
            );
        
            // The connection string might have been complete.
        if (result == SQL_SUCCESS) {
            return (sql::string());
        }
            // Anything else indicates an error.
        if (result != SQL_NEED_DATA) {
            throw (Diagnostic(connection.handle()));
        }
        
            // Allocate the output string and try again.
        sql::string missing(size);
        result = ::SQLBrowseConnect(
            connection.handle().value(),
            const_cast<character*>(how.data()), SQL_NTS,
            const_cast<character*>(missing.data()), SQL_NTS, &size
            );
        if (result != SQL_NEED_DATA) {
            throw (Diagnostic(connection.handle()));
        }
        
            // Notify the caller of missing information.
        return (missing);
    }

} }
