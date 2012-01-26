// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "mysql.hpp"
#include <sstream>

namespace {

    sql::string format ( const sql::string& database,
        const sql::string& username, const sql::string& password )
    {
        std::ostringstream how;
        how << "Driver={MySQL ODBC 5.1 Driver};"
            << "Server=localhost;"
            << "Database=" << database << ';'
            << "User=" << username << ';'
            << "Password=" << password << ';'
            << "Option=3;";
        return (how.str());
    }

}

namespace sql { namespace mysql {

    Connection::Connection ( Environment& environment, const string& database,
        const string& username, const string& password )
        : Driver(environment, ::format(database, username, password))
    {
    }

} }
