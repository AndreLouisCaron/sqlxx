#ifndef _sql_Statement_hpp__
#define _sql_Statement_hpp__

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

#include "types.hpp"
#include "Connection.hpp"
#include "NotCopyable.hpp"

namespace sql {

        /*!
         * @brief SQL Statement.
         *
         * The statement, in SQL parlance, is the premium mechanism of
         * communication between a client application and a database. Each one
         * represents a single operation from the client side, including any
         * reply the database emits.
         */
    class Statement :
        private NotCopyable
    {
        /* members. */
    private:
            // Hold (and automagically release) the connection data.
        Handle myHandle;

        /* construction. */
    public:
            /*!
             * @brief Create a Statement for a Connection.
             *
             * Create a statement to execute over a specific connection. The
             * statement's text will be sent to whichever database the
             * connection is associated to.
             *
             * @param connection Database to which the statement will talk.
             */
        Statement ( Connection& connection );

        /* methods. */
    public:
            /*!
             * @brief Obtains the statements's handle.
             *
             * Use the handle to implement any low-level operation this class
             * does not implement directly. However, take great care when
             * manipulating this object, because it grants you the power to
             * break class invariants.
             *
             * @return A reference to the statement's handle.
             */
        const Handle& handle () const throw();

            // Not sure when this is useful...
        void cancel ();

            /*!
             * @brief Executes as a prepared statement, and \c reset()s.
             */
        virtual void execute ();
    };

}

#endif /* _sql_Statement_hpp__ */
