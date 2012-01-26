// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
