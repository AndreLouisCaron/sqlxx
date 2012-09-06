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

#include <iostream>

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

    DataSources::Type DataSources::user ()
    {
        return (SQL_FETCH_FIRST_USER);
    }

    DataSources::Type DataSources::system ()
    {
        return (SQL_FETCH_FIRST_SYSTEM);
    }

    DataSources::Type DataSources::all ()
    {
        return (SQL_FETCH_FIRST);
    }

    DataSources::DataSources (Environment& environment, Type type)
        : myEnvironment(environment)
        , myDirection(type)
        , myName(SQL_MAX_DSN_LENGTH)
        , myInfo(SQL_MAX_DSN_LENGTH)
    {
    }

    bool DataSources::next ()
    {
        ::SQLRETURN result = SQL_NO_DATA;
        do {
            ::SQLSMALLINT name_size = 0;
            ::SQLSMALLINT info_size = 0;

            result = ::SQLDataSources(
                myEnvironment.handle().value(),
                myDirection,
                myName.data(), myName.capacity()+1, &name_size,
                myInfo.data(), myInfo.capacity()+1, &info_size);
            if (result == SQL_SUCCESS) {
                myDirection = SQL_FETCH_NEXT;
                return (true);
            }
            if (result == SQL_NO_DATA) {
                return (false);
            }
            if (result == SQL_SUCCESS_WITH_INFO) {
                const Diagnostic diagnostic(myEnvironment.handle());
                if (diagnostic.status() != Status::string_truncated()) {
                    throw (diagnostic);
                }
                myName.reserve(name_size);
                myInfo.reserve(info_size);
            }
        }
        while (result != SQL_ERROR);

        throw (Diagnostic(myEnvironment.handle()));
    }

} }
