#ifndef _sql_Handle_hpp__
#define _sql_Handle_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/NotCopyable.hpp>

namespace sql {

        /*!
         * @brief Wrapper for SQL handle management.
         *
         * SQL handles are generic placeholders for any implementation of
         * the SQL concepts of environment, connection, statement, etc. The
         * handle contains all bookeeping data for the opaque object delivered
         * by the driver and should be handled with care.
         *
         * Handles are not automatically freed, call the \c free() function to
         * release the handle.
         */
    class Handle :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::SQLHANDLE Value;
        typedef ::SQLSMALLINT Type;

        /* data. */
    private:
       Value myValue;
       Type myType;

        /* construction. */
    protected:
        Handle ( Value value, Type type );

    public:
        virtual ~Handle ();

        /* methods. */
    public:
            /*!
             * @brief Compares the handle's value to the generic placeholder
             *    value for invalid handles.
             */
        bool bad () const throw();

            /*!
             * @brief Checks the handle's value against the generic placeholder
             *    value for invalid handles.
             */
        bool ok () const throw();

            /*!
             * @brief Obtains the handle's value, in it's native API
             *    representation.
             * @return The handle's native value.
             */
        Value value () const throw();

            /*!
             * @brief Obtains the typecode for the resource attached to the
             *    handle.
             * @return The handle's typecode.
             */
        Type type () const throw();

            /*!
             * @brief Releases the handle back to the environment.
             */
        void free () throw();
    };

}

#endif /* _sql_Handle_hpp__ */
