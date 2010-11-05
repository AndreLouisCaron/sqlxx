#ifndef _sql_odbc_hpp__
#define _sql_odbc_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql.hpp>

// Query list of available data sources by using: SQLDataSources().
//
// SQLDrivers() lists installed drivers and their attributes.

namespace sql { namespace odbc {

    class Connection :
        public sql::Connection
    {
        /* construction. */
    public:
        Connection (
            Environment& environment, const string& database,
            const string& username, const string& password
            );
    };

        // Attempt a connection and return a non-empty string describing
        // missing parameters if connection string is incomplete. Returns
        // an empty string if the connection was successful.
    sql::string browse
        ( sql::Connection& connection, const sql::string& how );

} }

#endif /* _sql_odbc_hpp__ */
