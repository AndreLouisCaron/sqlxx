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

#include "Diagnostic.hpp"
#include <cstring>

namespace sql {

    Diagnostic::Diagnostic ( const Handle& culprit ) throw()
    {
        character status[6]; status[5] = '\0';
        int32 error = 0;
        int16 length = 0;
        ::SQLRETURN result = ::SQLGetDiagRec(
            culprit.type(), culprit.value(), 1, status,
            &error, myMessage, MessageLength-1, &length
            );
        if ( result == SQL_NO_DATA ) {
            std::memset(status,0,5*sizeof(character));
        }
        if ( length > MessageLength-1 ) {
            length = MessageLength - 1;
        }
        myStatus.raw(status);
        myMessage[length] = '\0';
    }

    Diagnostic::Diagnostic ( const Diagnostic& other ) throw ()
        : myStatus(other.myStatus)
    {
        std::memcpy(myMessage,other.myMessage,sizeof(myMessage));
    }

    const Status& Diagnostic::status () const throw()
    {
        return (myStatus);
    }

    const character * Diagnostic::what () const throw()
    {
        return (myMessage);
    }

    Diagnostic& Diagnostic::operator= ( const Diagnostic& other ) throw()
    {
        myStatus = other.myStatus;
        std::memcpy(myMessage,other.myMessage,sizeof(myMessage));
        return (*this);
    }

    std::ostream& operator<< (
        std::ostream& out, const Diagnostic& diagnostic
        )
    {
        return (out << diagnostic.status() << ": " << diagnostic.what());
    }

}
