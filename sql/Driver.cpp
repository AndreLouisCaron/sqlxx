// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Driver.hpp>
#include <sql/Diagnostic.hpp>
#include <sstream>

namespace sql {

    Driver::Driver ( Environment& environment, const string& how )
        : Connection(environment)
    {
        character outbuf[256];
        ::SQLSMALLINT end = 0;
        const ::SQLRETURN result = ::SQLDriverConnect(
            handle().value(), NULL, const_cast<character*>(how.data()),
            SQL_NTS, outbuf, 256, &end, SQL_DRIVER_NOPROMPT
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    Driver::~Driver ()
    {
        ::SQLDisconnect(handle().value());
    }

}
