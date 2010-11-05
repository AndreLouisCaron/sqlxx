// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Handle.hpp>

namespace sql {

    Handle::Handle ( Value value, Type type )
        : myValue(value), myType(type)
    {
    }

    Handle::~Handle ()
    {
    }

    bool Handle::bad () const throw()
    {
        return (myValue == SQL_NULL_HANDLE);
    }

    bool Handle::ok () const throw()
    {
        return (myValue != SQL_NULL_HANDLE);
    }

    Handle::Value Handle::value () const throw()
    {
        return (myValue);
    }

    Handle::Type Handle::type () const throw()
    {
        return (myType);
    }

    void Handle::free () throw()
    {
        if ( ok() )
        {
            ::SQLFreeHandle(myType,myValue);
            myType = SQL_HANDLE_ENV;
            myValue = SQL_NULL_HANDLE;
        }
    }

}