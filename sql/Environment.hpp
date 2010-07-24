#ifndef _sql_Environment_hpp__
#define _sql_Environment_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/NotCopyable.hpp>
#include <sql/Handle.hpp>
#include <sql/Version.hpp>

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
        class Handle :
            public sql::Handle
        {
            /* construction. */
        public:
            explicit Handle ( Value value );
            virtual ~Handle ();
        };

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
