// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Status.hpp"
#include <cstring>

namespace sql {

    const Status Status::none;

    Status::Status () throw ()
    {
        std::memset(myValue,0,6*sizeof(character));
    }

    Status::Status ( const character * value ) throw()
    {
        std::memcpy(myValue,value,5*sizeof(character));
        myValue[5] = '\0';
    }

    Status::Status ( const Handle& culprit, int16 index ) throw()
    {
        ::SQLINTEGER nativeError = 0;
        ::SQLSMALLINT length = 0;
        ::SQLRETURN result = ::SQLGetDiagRec(
            culprit.type(), culprit.value(), index, myValue,
            &nativeError, 0, 0, &length
            );
        if ( result == SQL_NO_DATA ) {
            std::memset(myValue,0,5*sizeof(character));
        }
        myValue[5] = '\0';
    }

    const character * Status::raw () const throw()
    {
        return (myValue);
    }

    void Status::raw ( const character * value ) throw()
    {
        std::memcpy(myValue,value,5*sizeof(character));
        myValue[5] = '\0';
    }

    std::ostream& operator<< ( std::ostream& out, const Status& status )
    {
        return (out << status.raw());
    }

}
