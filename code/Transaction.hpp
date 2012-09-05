#ifndef _sql_Transaction_hpp__
#define _sql_Transaction_hpp__

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

namespace sql {

    /*!
     * @defgroup transactions SQL transaction support.
     * @brief Support for commit-or-rollback of multiple updates.
     */

    class Connection;

    /*!
     * @ingroup transactions
     * @brief Commit-or-rollback for a group of SQL statements.
     *
     * The typical use case for transactions is the following:
     * @code
     *  sql::Connection& connection = ...;
     *  { sql::Transaction transaction(connection);
     *
     *    // Run a group of related queries and/or updates that should either
     *    // all occur or all be cancelled if any error occurs.
     *    sql::execute(connection, ...);
     *    sql::execute(connection, ...);
     *    //  ...
     *
     *    // If an exception is thrown or a return statement is encountered,
     *    // this line is never reached and the transaction is rolled back.
     *    transaction.commit();
     *  }
     * @endcode
     *
     * @see Connection::enable_autocommit
     * @see Connection::disable_autocommit
     */
    class Transaction :
        private NotCopyable
    {
        /* data. */
    private:
        Connection& myConnection;
        bool myCommitFlag;

        /* construction. */
    public:
        /*!
         * @brief Start a transaction.
         * @param connection Connection over which statements will be issued.
         */
        Transaction (Connection& connection);

        /*!
         * @brief End a transaction.
         *
         * @see commit()
         */
        ~Transaction ();

        /* methods. */
    public:
        /*!
         * @brief Signals that the transaction should be commited.
         *
         * @note By default, the transaction is rolled back.  Call this to
         *  trigger a commit when the transaction ends.
         */
        void commit ();
    };

}

#endif /* _sql_Transaction_hpp__ */
