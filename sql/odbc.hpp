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
// SQLBrowseConnect() is useful for building connection string in an
//   interactive fashon but is hard to wrap in a general setup.
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

} }

#endif /* _sql_odbc_hpp__ */
