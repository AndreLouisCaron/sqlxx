#ifndef _sql_types_hpp_
#define _sql_types_hpp_

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace sql {

    typedef ::SQLCHAR character;
    typedef ::SQLWCHAR wcharacter;
    typedef ::SQLLEN size_t;

    typedef ::SQLSCHAR int8;
    typedef ::SQLCHAR uint8;
    typedef ::SQLSMALLINT int16;
    typedef ::SQLUSMALLINT uint16;
    typedef ::SQLINTEGER int32;
    typedef ::SQLUINTEGER uint32;
    typedef ::SQLBIGINT int64;
    typedef ::SQLUBIGINT uint64;

}

#endif /* _sql_types_hpp_ */
