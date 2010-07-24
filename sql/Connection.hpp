#ifndef _sql_Connection_hpp__
#define _sql_Connection_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/Environment.hpp>
#include <sql/Handle.hpp>
#include <sql/NotCopyable.hpp>

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
        /* nested types. */
    public:
        class Handle :
            public sql::Handle
        {
            /* construction. */
        public:
            explicit Handle ( Value value );
            virtual ~Handle ();
        };

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
