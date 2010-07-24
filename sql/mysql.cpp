// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/mysql.hpp>

namespace sql { namespace mysql {

    std::ostream& LocalConnectionString::put ( std::ostream& out ) const
    {
        std::ostream::sentry ok(out);
        if ( ok )
        {
            out << "Driver={MySQL ODBC 5.1 Driver};"
                << "Server=localhost;"
                << "Database=" << database() << ';'
                << "User=" << user() << ';'
                << "Password=" << password() << ';'
                << "Option=3;";
        }
        return (out);
    }

} }
