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
#include "string.hpp"

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
     * @defgroup driver_information ODBC driver information.
     * @brief Dynamic information on a connection's ODBC driver.
     *
     * @see http://msdn.microsoft.com/en-us/library/windows/desktop/ms711681.aspx
     */

    /*!
     * @defgroup sql_support Data source SQL support.
     * @brief Dynamic information on a data source's SQL support/compliance.
     *
     * @see http://msdn.microsoft.com/en-us/library/windows/desktop/ms711681.aspx
     */

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
         * @internal
         * @brief Create a connection.
         * @param environment Environment to associate to the connection.
         *
         * The environment object's lifetime must exceed that of this
         * object, because the connection is directly associated to the
         * environment.
         */
        Connection (Environment& environment);

    public:
        /*!
         * @brief Release the database connection.
         */
        virtual ~Connection ();

        /* methods. */
    public:
        /*!
         * @internal
         * @brief Obtains the Connection's Handle.
         * @return The Connection Handle.
         *
         * Use the handle to implement any low-level operation this class
         * does not implement directly. However, take great care when
         * manipulating this object, because it grants you the power to
         * break class invariants.
         */
        const Handle& handle () const throw();

        //! @addtogroup transactions
        //! @{

        /*!
         * @brief Enables auto-commit of SQL statements.
         *
         * @note There is usually no need to call this explicitly.  Use the
         *  @c Transaction class instead.
         *
         * @see disable_autocommit()
         */
        void enable_autocommit ();

        /*!
         * @brief Disables auto-commit of SQL statements.
         *
         * @note There is usually no need to call this explicitly.  Use the
         *  @c Transaction class instead.
         *
         * @see enable_autocommit
         */
        void disable_autocommit ();

        /*!
         * @brief Commits all changes made through this connection.
         *
         * @note There is usually no need to call this explicitly.  Use the
         *  @c Transaction class instead.
         *
         * @see rollback()
         */
        void commit ();

        /*!
         * @brief Rolls back all changes made through this connection.
         *
         * @note There is usually no need to call this explicitly.  Use the
         *  @c Transaction class instead.
         *
         * @see commit()
         */
        void rollback ();

        //! @}

        //! @ingroup driver_information
        //! @{

        /*!
         * @brief Obtains the ODBC version supported by the driver.
         */
        string driver_odbc_version () const;
        string driver_name () const;
        string driver_version () const;
        string database_name () const;
        string host_name () const;
        string user_name () const;
        string data_source_name () const;
        uint16 max_driver_connections () const;

        //! @}

        //! @ingroup sql_support
        //! @{

        /*!
         * @todo Refactor this to extract specific aspects from the mask.
         */
        uint32 create_table_support () const;

        //! @}

        /*!
         * @brief Queries the driver for the maximum catalog name length.
         * @return The maximum catalog name length.
         *
         * Use this to reserve memory for result strings returned by the @c
         * Catalogs enumerator.
         */
        uint16 max_catalog_name_size () const;

        /*!
         * @brief Queries the driver for the maximum schema name length.
         * @return The maximum schema name length.
         *
         * Use this to reserve memory for result strings returned by the @c
         * Schemas enumerator.
         */
        uint16 max_schema_name_size () const;

        /*!
         * @brief Queries the driver for the maximum table name length.
         * @return The maximum table name length.
         *
         * Use this to reserve memory for result strings returned by the @c
         * Tables enumerator.
         */
        uint16 max_table_name_size () const;
    };

}

#endif /* _sql_Connection_hpp__ */
