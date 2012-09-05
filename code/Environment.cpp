// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
        if (result != SQL_SUCCESS) {
            throw (sql::Environment::Failure());
        }
        return (handle);
    }

}

namespace sql {

    Environment::Environment (const Version& version)
        : myHandle(::allocate(), SQL_HANDLE_ENV, &Handle::claim)
    {
        const ::SQLRETURN result = ::SQLSetEnvAttr(
            myHandle.value(), SQL_ATTR_ODBC_VERSION, version.value(), 0
            );
        if (result != SQL_SUCCESS) {
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
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
    }

    void Environment::rollback ()
    {
        const ::SQLRETURN result = ::SQLEndTran(
            handle().type(), handle().value(), SQL_ROLLBACK
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
    }

}
