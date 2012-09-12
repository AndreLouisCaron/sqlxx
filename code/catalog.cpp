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

#include "catalog.hpp"
#include "Diagnostic.hpp"

namespace sql {

    Catalogs::Catalogs (Connection& connection)
        : Statement(connection)
    {
        ::SQLCHAR any[] = "";
        const ::SQLRETURN result = ::SQLTables(
            handle().value(),
            (::SQLCHAR*)SQL_ALL_CATALOGS, SQL_NTS,
            any, SQL_NTS, // schema name.
            any, SQL_NTS, // table name.
            any, SQL_NTS); // table type.
        if ((result != SQL_SUCCESS) && (result != SQL_SUCCESS_WITH_INFO))
        {
            throw (Diagnostic(handle()));
        }
    }

    Schemas::Schemas (Connection& connection)
        : Statement(connection)
    {
        ::SQLCHAR any[] = "";
        const ::SQLRETURN result = ::SQLTables(
            handle().value(),
            any, SQL_NTS, // catalog name.
            (::SQLCHAR*)SQL_ALL_SCHEMAS, SQL_NTS,
            any, SQL_NTS, // table name.
            any, SQL_NTS); // table type.
        if ((result != SQL_SUCCESS) && (result != SQL_SUCCESS_WITH_INFO))
        {
            throw (Diagnostic(handle()));
        }
    }

    TableTypes::TableTypes (Connection& connection)
        : Statement(connection)
    {
        ::SQLCHAR any[] = "";
        const ::SQLRETURN result = ::SQLTables(
            handle().value(),
            any, SQL_NTS, // catalog name.
            any, SQL_NTS, // schema name.
            any, SQL_NTS, // table name.
            (::SQLCHAR*)SQL_ALL_TABLE_TYPES, SQL_NTS);
        if ((result != SQL_SUCCESS) && (result != SQL_SUCCESS_WITH_INFO))
        {
            throw (Diagnostic(handle()));
        }
    }

    Tables::Tables (Connection& connection)
        : Statement(connection)
    {
        ::SQLCHAR any[] = "";
        const ::SQLRETURN result = ::SQLTables(
            handle().value(),
            any, SQL_NTS, // catalog name.
            any, SQL_NTS, // schema name.
            any, SQL_NTS, // table name.
            any, SQL_NTS); // table type.
        if ((result != SQL_SUCCESS) && (result != SQL_SUCCESS_WITH_INFO))
        {
            throw (Diagnostic(handle()));
        }
    }

    PrimaryKeys::PrimaryKeys (Connection& connection, const string& table)
        : Statement(connection)
    {
        ::SQLCHAR any[] = "";
        const ::SQLRETURN result = ::SQLPrimaryKeys(
            handle().value(),
            any, SQL_NTS, // catalog name.
            any, SQL_NTS, // schema name.
            (::SQLCHAR*)table.data(), SQL_NTS); // table name.
        if ((result != SQL_SUCCESS) && (result != SQL_SUCCESS_WITH_INFO))
        {
            throw (Diagnostic(handle()));
        }
    }

    ForeignKeys::ForeignKeys (Connection& connection, const string& table)
        : Statement(connection)
    {
        ::SQLCHAR any[] = "";
        const ::SQLRETURN result = ::SQLForeignKeys(
            handle().value(),
            any, SQL_NTS, // pk table catalog name.
            any, SQL_NTS, // pk table schema name.
            any, SQL_NTS, // pk table table name.
            any, SQL_NTS, // fk table catalog name.
            any, SQL_NTS, // fk table schema name.
            (::SQLCHAR*)table.data(), SQL_NTS); // fk table name.
        if ((result != SQL_SUCCESS) && (result != SQL_SUCCESS_WITH_INFO))
        {
            throw (Diagnostic(handle()));
        }
    }

}

