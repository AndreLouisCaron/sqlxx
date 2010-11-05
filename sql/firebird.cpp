// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/firebird.hpp>
#include <sstream>

namespace {

    sql::string format ( const sql::string& database,
        const sql::string& username, const sql::string& password )
    {
        std::ostringstream how;
        how << "DRIVER={Firebird/Interbase(r) Driver (*.fdb)};"
            << "DATABASE=" << database << ';'
            << "USER=" << username << ';'
            << "PASSWORD=" << password << ';'
            << "CHARSET=WIN1250;";
        return (how.str());
    }

}

namespace sql { namespace firebird {

    Connection::Connection ( Environment& environment, const string& database,
        const string& username, const string& password )
        : Driver(environment, ::format(database, username, password))
    {
    }

} }
