#ifndef _sql_Connection_hpp__
#define _sql_Connection_hpp__

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
#include "Environment.hpp"
#include "Handle.hpp"
#include "NotCopyable.hpp"

// TODO: Implement connection classes to use SQLConnect() and
// SQLBrowseConnect(). The former uses ODBC data sources registered on the
// local machine and the latter allows to interactively edit the connection
// string.
// http://msdn.microsoft.com/en-us/library/ms711810.aspx
// http://msdn.microsoft.com/en-us/library/ms709431(VS.85).aspx
// http://msdn.microsoft.com/en-us/library/ms712446(VS.85).aspx
//
// TODO: Implement support for connection parameters.
// http://msdn.microsoft.com/en-us/library/ms713605(VS.85).aspx

namespace sql {

        /*!
         * @brief Connection to a database.
         *
         * Once your program has initialized SQL libraries by creating an
         * Environment, you need to connect to a database. This class represents
         * an active connection and allows you to manipulate it.
         *
         * This is an abstract class; to connect to a database, use one of the
         * implementation classes.
         */
    class Connection :
        private NotCopyable
    {
        /* data. */
    private:
            // Hold (and automagically release) the connection data.
        Handle myHandle;

        /* construction. */
    protected:
            /*!
             * @brief Create a connection, using a given Environment.
             *
             * The environment object's lifetime must exceed that of this
             * object, because the connection is directly associated to the
             * environment.
             *
             * @param environment Environment to associate to the connection.
             */
        Connection ( Environment& environment );

    public:
        virtual ~Connection ();

        /* methods. */
    public:
            /*!
             * @brief Obtains the Connection's Handle.
             *
             * Use the handle to implement any low-level operation this class
             * does not implement directly. However, take great care when
             * manipulating this object, because it grants you the power to
             * break class invariants.
             *
             * @return The Connection Handle.
             */
        const Handle& handle () const throw();

        void enable_autocommit ();
        void disable_autocommit ();

            /*!
             * @brief Commits all changes made through this connection.
             */
        void commit ();

            /*!
             * @brief Rolls back all changes made through this connection.
             */
        void rollback ();
    };

}

#endif /* _sql_Connection_hpp__ */
