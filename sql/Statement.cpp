// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Statement.hpp>
#include <sql/Diagnostic.hpp>

namespace {

    ::SQLHANDLE allocate ( sql::Connection& connection )
    {
        ::SQLHANDLE value = SQL_NULL_HANDLE;
        const ::SQLRETURN result = ::SQLAllocHandle(
            SQL_HANDLE_STMT, connection.handle().value(), &value
            );
        if ( result != SQL_SUCCESS ) {
            throw (sql::Diagnostic(connection.handle()));
        }
        return (value);
    }

}

namespace sql {

    Statement::Statement ( Connection& connection )
        : myHandle(::allocate(connection), SQL_HANDLE_STMT, &Handle::claim)
    {
    }

    const Handle& Statement::handle () const throw()
    {
        return (myHandle);
    }

    void Statement::execute ()
    {
        ::SQLRETURN result = ::SQLExecute(handle().value());
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    void Statement::cancel ()
    {
        ::SQLRETURN result = ::SQLCancel(handle().value());
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

}
