// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql.hpp>

namespace {

    const char DataType[] = "time";
    typedef sql::Time Value;

    const sql::Time values[] = {
        sql::Time(7,12,26),
        sql::Time(11,2,27),
        sql::Time(15,3,28),
    };

}

#include "test-template.cpp"
