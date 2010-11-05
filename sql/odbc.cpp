// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/odbc.hpp>

namespace sql { namespace odbc {

    Connection::Connection ( Environment& environment, const string& database,
        const string& username, const string& password )
        : sql::Connection(environment)
    {
        const ::SQLRETURN result = ::SQLConnect(
            handle().value(),
            const_cast<character*>(database.data()), SQL_NTS,
            const_cast<character*>(username.data()), SQL_NTS,
            const_cast<character*>(password.data()), SQL_NTS
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    sql::string browse
        ( sql::Connection& connection, const sql::string& how )
    {
            // Query the length of the output string.
        ::SQLSMALLINT size = 0;
        ::SQLRETURN result = ::SQLBrowseConnect(
            connection.handle().value(),
            const_cast<character*>(how.data()), SQL_NTS, 0, 0, &size
            );
        
            // The connection string might have been complete.
        if ( result == SQL_SUCCESS ) {
            return (sql::string());
        }
            // Anything else indicates an error.
        if ( result != SQL_NEED_DATA ) {
            throw (Diagnostic(connection.handle()));
        }
        
            // Allocate the output string and try again.
        sql::string missing(size);
        result = ::SQLBrowseConnect(
            connection.handle().value(),
            const_cast<character*>(how.data()), SQL_NTS,
            const_cast<character*>(missing.data()), SQL_NTS, &size
            );
        if ( result != SQL_NEED_DATA ) {
            throw (Diagnostic(connection.handle()));
        }
        
            // Notify the caller of missing information.
        return (missing);
    }

} }
