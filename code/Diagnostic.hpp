#ifndef _sql_Diagnostic_hpp__
#define _sql_Diagnostic_hpp__

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

#include "__configure__.hpp"
#include "types.hpp"
#include "Handle.hpp"
#include "Status.hpp"

namespace sql {

        /*!
         * @brief SQL related error.
         *
         * When an error related with SQL occurs, an exception of this type
         * occurs to signal what the error is. It is meant to signal the
         * user about failed transactions in general.
         */
    class Diagnostic
    {
        /* class data. */
    private:
            // Do not dynamically allocate memory to avoid possible memory
            // allocation failure (in particular throwing of std::bad_alloc)
            // during exception processing: this would crash the program!
        static const unsigned int MessageLength = 128;

        /* members. */
    private:
        Status myStatus;
        character myMessage[MessageLength];

        /* construction. */
    public:
            /*!
             * @brief Reads Diagnostics for an error on a given Handle.
             */
        Diagnostic (const Handle& culprit) throw();

            /*!
             * @brief Copies \c other's error code.
             *
             * @param other Object whose SQL error code is to be duplicated.
             */
        Diagnostic (const Diagnostic& other) throw ();

        /* methods. */
    public:
            /*!
             * @brief Obtains the diagnostic's 5-character status code.
             */
        const Status& status () const throw();

            /*!
             * @brief Obtains the description as an ASCIIZ string.
             * @return An ASCIIZ string containing a description message.
             */
        const character * what () const throw();

        /* operators. */
    public:
            /*!
             * @brief Copies \c other's error code.
             *
             * Note : although assigning to exceptions is uncommon, this
             * is here for the sake of consistency.
             *
             * @param other Object whose SQL error code is to be duplicated.
             */
        Diagnostic& operator= (const Diagnostic& other) throw();
    };

        /*!
         * @brief Puts the error diagnostic to a stream.
         */
    std::ostream& operator<<
        (std::ostream& stream, const Diagnostic& diagnostic);

}

#endif /* _sql_Diagnostic_hpp__ */
