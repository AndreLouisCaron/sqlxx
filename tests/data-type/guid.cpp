// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Guid.hpp>

namespace {

    const char DataType[] = "guid";
    typedef sql::Guid Value;

    const Value values[] = {
        Value(0x2c20b6bd,0x04fb,0x43da,0x88,0x72,0xbb,0xea,0x02,0xb3,0xb4,0xbf),
        Value(0x32e16ccd,0xbcee,0x43ef,0xae,0xb6,0x13,0x42,0x92,0x43,0x1e,0xde),
        Value(0x9ef814c5,0xeb36,0x4d3e,0xbd,0xa7,0xdb,0x79,0xca,0xa7,0x17,0xa1),
    };

}

#include <sql/__tests__/data-type/test-template.cpp>
