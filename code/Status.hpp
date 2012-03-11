#ifndef _sql_Status_hpp__
#define _sql_Status_hpp__

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
#include <ostream>

namespace sql {

        /*!
         * @brief Generic 5 character SQL status code.
         *
         * The status can be obtained as soon as an error occurs. Note that
         * there can be more than one diagnostic for a given error/status,
         * although it is not clear when or how this happens...
         */
    class Status
    {
        /* class data. */
    public:
        static const Status none;

        /* data. */
    private:
            // Standard 5 characters, plus a null terminator.
        character myValue[6];

        /* construction. */
    public:
            /*!
             * @brief Null status (equivalent to the empty string).
             */
        Status () throw ();

            /*!
             * @brief Creates a status from a 5-character status code.
             *
             * @param value 5-character status code, no terminator required.
             */
        explicit Status ( const character * value ) throw();

            /*!
             * @brief Obtains the 'n'th diagnostic for a given handle.
             *
             * @param culprit Handle to the resource which cause a problem.
             * @param index Identifier for the diagnostic you want. Because
             *    there is usually only one and that is the one you want, the
             *    default is the first. These are numbers from 1, not 0.
             */
        explicit Status ( const Handle& culprit, int16 index = 1 ) throw();

        /* methods. */
    public:
            /*!
             * @brief Obtains the 5-character status code.
             *
             * @return Status code, always null terminated.
             */
        const character * raw () const throw();

            /*!
             * @brief Sets the 5-character status code.
             *
             * @param value 5-character code, no terminator required.
             */
        void raw ( const character * value ) throw();
    };

        /*!
         * @brief Puts the status to a stream.
         */
    std::ostream& operator<< ( std::ostream& out, const Status& status );

}

#endif /* _sql_Status_hpp__ */
