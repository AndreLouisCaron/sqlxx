#ifndef _sql_Driver_hpp__
#define _sql_Driver_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/types.hpp>
#include <sql/Connection.hpp>
#include <sql/ConnectionString.hpp>

namespace sql {

        /*!
         * @brief Connects to a database using a specific driver and a
         *    connection string to pass it some parameters.
         *
         * This class is useful when you want to use a specific database type
         * and specific driver. If you want more flexibility, you can factor
         * this out of your code by configuring an ODBC connection.
         */
    class Driver :
        public Connection
    {
        /* construction. */
    public:
            /*!
             * @brief Attemps to open a database connection.
             *
             * @param environment General SQL/ODBC parameters.
             * @param string Connection string which specifies which driver to
             *    use and more parameters that depend strongly on that specific
             *    driver. For drivers who support remote access (some don't),
             *    the hostname or protocol information are required by the
             *    driver to open the connection.
             */
        Driver ( Environment& environment, const ConnectionString& string );

            /*!
             * @brief Closes the connection to the database.
             *
             * All operations, unless rolled back, will be commited
             * automatically.
             */
        virtual ~Driver ();
    };

}

#endif /* _sql_Driver_hpp__ */
