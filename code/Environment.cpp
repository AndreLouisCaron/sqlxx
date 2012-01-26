// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Environment.hpp"
#include "Diagnostic.hpp"

namespace {

        // Performs the actual handle allocation.
    ::SQLHANDLE allocate ()
    {
        ::SQLHANDLE handle = SQL_NULL_HANDLE;
        const ::SQLRETURN result = ::SQLAllocHandle(
            SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handle
            );
        if ( result != SQL_SUCCESS ) {
            throw (sql::Environment::Failure());
        }
        return (handle);
    }

}

namespace sql {

    Environment::Environment ( const Version& version )
        : myHandle(::allocate(), SQL_HANDLE_ENV, &Handle::claim)
    {
        const ::SQLRETURN result = ::SQLSetEnvAttr(
            myHandle.value(), SQL_ATTR_ODBC_VERSION, version.value(), 0
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(myHandle));
        }
    }

    const Handle& Environment::handle () const throw()
    {
        return (myHandle);
    }

    void Environment::commit ()
    {
        const ::SQLRETURN result = ::SQLEndTran(
            handle().type(), handle().value(), SQL_COMMIT
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    void Environment::rollback ()
    {
        const ::SQLRETURN result = ::SQLEndTran(
            handle().type(), handle().value(), SQL_ROLLBACK
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

}
