// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Connection.hpp>
#include <sql/Diagnostic.hpp>

namespace {

        // Does the actual connection handle allocation.
    ::SQLHANDLE allocate ( sql::Environment& environment )
    {
        ::SQLHANDLE handle = SQL_NULL_HANDLE;
        const ::SQLRETURN result = ::SQLAllocHandle(
            SQL_HANDLE_DBC, environment.handle().value(), &handle
            );
        if ( result != SQL_SUCCESS ) {
            throw (sql::Diagnostic(environment.handle()));
        }
        return (handle);
    }

}

namespace sql {

    Connection::Handle::Handle ( Value value )
        : sql::Handle(value,SQL_HANDLE_DBC)
    {
    }

    Connection::Handle::~Handle ()
    {
        free();
    }

    Connection::Connection ( Environment& environment )
        : myHandle(::allocate(environment))
    {
    }

    Connection::~Connection ()
    {
    }

    const Connection::Handle& Connection::handle () const throw()
    {
        return (myHandle);
    }

    void Connection::commit ()
    {
        ::SQLRETURN result = ::SQLEndTran(
            handle().type(), handle().value(), SQL_COMMIT
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    void Connection::rollback ()
    {
        ::SQLRETURN result = ::SQLEndTran(
            handle().type(), handle().value(), SQL_ROLLBACK
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

}
