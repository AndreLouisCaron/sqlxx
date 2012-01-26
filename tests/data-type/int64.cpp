// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql.hpp>

namespace {

    const char DataType[] = "integer";
    typedef sql::int64 Value;

    const sql::int64 values[] = {
        sql::int64(0),
        sql::int64(1),
        sql::int64(2),
    };

}

#include "test-template.cpp"
