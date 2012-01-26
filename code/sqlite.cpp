// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "sqlite.hpp"
#include <sstream>

namespace {

    sql::string format ( const sql::string& database )
    {
        std::ostringstream how;
        how << "Driver={SQLite ODBC Driver};"
            << "Database=" << database << ';';
        return (how.str());
    }

}

namespace sql { namespace sqlite {

    Connection::Connection ( Environment& environment, const string& database )
        : Driver(environment, ::format(database))
    {
    }

} }
