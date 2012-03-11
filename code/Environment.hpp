#ifndef _sql_Environment_hpp__
#define _sql_Environment_hpp__

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
#include "NotCopyable.hpp"
#include "Handle.hpp"
#include "Version.hpp"

namespace sql {

        /*!
         * @brief SQL/ODBC execution context.
         *
         * The environment serves as a library initilizer and absolutely must
         * exist to use any of this library's facilities. Typical applications
         * only use a single environement throughout their execution.
         */
    class Environment :
        private NotCopyable
    {
        /* nested types. */
    public:
            /*!
             * @brief Thrown in the *highly unlikely* case where the environment
             *    allocation fails. In this case, there is no standard means of
             *    obtaining a diagnosis: all diagnosis functions require an SQL
             *    handle of some sort.
             */
        class Failure {};

        /* members. */
    private:
            // Hold (and automagically release) the connection data.
        Handle myHandle;

        /* construction. */
    public:
            /*!
             * @brief Create and initialize an SQL/ODBC environment.
             *
             * Initialize an SQL/ODBC environment object for a specific
             * ODBC Version. All Connection objects and their associated
             * statements must comply to its conventions.
             *
             * @param version ODBC Version to use, defaults to '3.x'.
             */
        Environment ( const Version& version = Version::odbc3 );

        /* methods. */
    public:
            /*!
             * @brief Obtains the environment's handle.
             *
             * Use the handle to implement any low-level operation this class
             * does not implement directly. However, take great care when
             * manipulating this object, because it grants you the power to
             * break class invariants.
             *
             * @return A reference to the environment's handle.
             */
        const Handle& handle () const throw();

            /*!
             * @brief Commits all changes made through this environment.
             */
        void commit ();

            /*!
             * @brief Rolls back all changes made through this environment.
             */
        void rollback ();
    };

}

#endif /* _sql_Environment_hpp__ */
