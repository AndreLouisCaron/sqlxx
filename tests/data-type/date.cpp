// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Date.hpp>

namespace {

    const char DataType[] = "date";
    typedef sql::Date Value;

    const sql::Date values[] = {
        sql::Date(2009,1,26),
        sql::Date(2010,2,27),
        sql::Date(2011,3,28),
    };

}

#include <sql/__tests__/data-type/test-template.cpp>
