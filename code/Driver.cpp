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

#include "Driver.hpp"
#include "Diagnostic.hpp"
#include <sstream>

namespace sql {

    Driver::Driver (Environment& environment, const string& settings)
        : Connection(environment)
    {
        character outbuf[256];
        ::SQLSMALLINT end = 0;
        const ::SQLRETURN result = ::SQLDriverConnect(
            handle().value(), NULL, const_cast<character*>(settings.data()),
            SQL_NTS, outbuf, 256, &end, SQL_DRIVER_NOPROMPT
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
    }

    Driver::Driver (Environment& environment, const wstring& settings)
        : Connection(environment)
    {
        wcharacter outbuf[256];
        ::SQLSMALLINT end = 0;
        const ::SQLRETURN result = ::SQLDriverConnectW(
            handle().value(), NULL, const_cast<wcharacter*>(settings.data()),
            SQL_NTS, outbuf, 256, &end, SQL_DRIVER_NOPROMPT
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
    }

    Driver::~Driver ()
    {
        ::SQLDisconnect(handle().value());
    }

    Drivers::Drivers (Environment& environment)
        : myEnvironment(environment)
        , myDirection(SQL_FETCH_FIRST)
        , myName(1)
        , myInfo(1)
    {
    }

    bool Drivers::next ()
    {
        ::SQLRETURN result = SQL_NO_DATA;
        do {
            ::SQLSMALLINT name_size = 0;
            ::SQLSMALLINT info_size = 0;

            result = ::SQLDrivers(
                myEnvironment.handle().value(),
                myDirection,
                myName.data(), myName.capacity()+1, &name_size,
                myInfo.data(), myInfo.capacity()+1, &info_size);
            if (result == SQL_SUCCESS) {
                myDirection = SQL_FETCH_NEXT;
                return (true);
            }
            if (result == SQL_NO_DATA) {
                return (false);
            }
            if (result == SQL_SUCCESS_WITH_INFO) {
                const Diagnostic diagnostic(myEnvironment.handle());
                if (diagnostic.status() != Status::string_truncated()) {
                    throw (diagnostic);
                }
                myName.reserve(name_size);
                myInfo.reserve(info_size);
            }
        }
        while (result != SQL_ERROR);

        throw (Diagnostic(myEnvironment.handle()));
    }

}
