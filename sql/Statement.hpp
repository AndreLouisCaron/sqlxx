#ifndef _sql_Statement_hpp__
#define _sql_Statement_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
