// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/DirectStatement.hpp>
#include <sql/Diagnostic.hpp>

namespace sql {

    DirectStatement::DirectStatement
        ( Connection& connection, const string& query )
        : Statement(connection), myQuery(query)
    {
    }

    DirectStatement::DirectStatement
        ( Connection& connection, const std::string& query )
        : Statement(connection), myQuery(query)
    {
    }

    void DirectStatement::execute ()
    {
        const ::SQLRETURN result = ::SQLExecDirect(
            handle().value(), myQuery.data(), SQL_NTS
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

}
