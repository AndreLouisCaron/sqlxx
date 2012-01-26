// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Version.hpp"

namespace sql {

    const Version Version::odbc2(
        reinterpret_cast<::SQLPOINTER>(SQL_OV_ODBC2)
        );
    const Version Version::odbc3(
        reinterpret_cast<::SQLPOINTER>(SQL_OV_ODBC3)
        );

    Version::Version ( Value value ) throw()
        : myValue(value)
    {
    }

    Version::Value Version::value () const throw()
    {
        return (myValue);
    }

}
