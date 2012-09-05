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

#include "Status.hpp"
#include <cstring>

namespace sql {

    const Status Status::none ()
    {
        return (Status());
    }

    const Status Status::connection_rejected ()
    {
        return (Status((const character*)"08004"));
    }

    Status::Status () throw ()
    {
        std::memset(myValue,0,6*sizeof(character));
    }

    Status::Status (const character * value) throw()
    {
        std::memcpy(myValue,value,5*sizeof(character));
        myValue[5] = '\0';
    }

    Status::Status (const Handle& culprit, int16 index) throw()
    {
        ::SQLINTEGER nativeError = 0;
        ::SQLSMALLINT length = 0;
        ::SQLRETURN result = ::SQLGetDiagRec(
            culprit.type(), culprit.value(), index, myValue,
            &nativeError, 0, 0, &length
            );
        if (result == SQL_NO_DATA) {
            std::memset(myValue,0,5*sizeof(character));
        }
        myValue[5] = '\0';
    }

    const character * Status::raw () const throw()
    {
        return (myValue);
    }

    void Status::raw (const character * value) throw()
    {
        std::memcpy(myValue,value,5*sizeof(character));
        myValue[5] = '\0';
    }

    bool operator== (const Status& lhs, const Status& rhs)
    {
        return (std::strcmp((const char*)lhs.raw(),
                            (const char*)rhs.raw()) == 0);
    }

    bool operator!= (const Status& lhs, const Status& rhs)
    {
        return (std::strcmp((const char*)lhs.raw(),
                            (const char*)rhs.raw()) != 0);
    }

    std::ostream& operator<< (std::ostream& stream, const Status& status)
    {
        return (stream << status.raw());
    }

}
