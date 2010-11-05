// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/execute.hpp>
#include <sql/Connection.hpp>
#include <sql/DirectStatement.hpp>

namespace sql {

    void execute ( Connection& connection, const string& update )
    {
        sql::DirectStatement(connection,update).execute();
    }

}
