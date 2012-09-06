#ifndef _sql_odbc_hpp__
#define _sql_odbc_hpp__

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

/*!
 * @file odbc.hpp
 * @brief sqlxx ODBC support.
 *
 * @see sql::odbc
 */

#include "sql.hpp"

namespace sql {

    /*!
     * @brief Data source name (DSN)-based connection support.
     *
     * @see sql.hpp
     * @see odbc.hpp
     * @see http://en.wikipedia.org/wiki/ODBC
     */
    namespace odbc {}

}

namespace sql { namespace odbc {

    /*!
     * @brief Connection by data source name.
     */
    class Connection :
        public sql::Connection
    {
        /* construction. */
    public:
        /*!
         * @brief Connect to a registered ODBC connection.
         * @param environment ODBC environment.
         * @param database Database name.
         * @param username Credentials.
         * @param password Credentials.
         *
         * @todo Verify that @a database is the data source name.
         */
        Connection (Environment& environment, const string& database,
                    const string& username, const string& password);
    };

    /*!
     * @brief Iteratively build a database connection string.
     * @param connection Incomplete database connection.
     * @param settings Existing settings.
     * @return Additional settings to 
     *
     * Attempt a connection and return a non-empty string describing
     * missing parameters if connection string is incomplete. Returns
     * an empty string if the connection was successful.
     *
     * @todo Document the format used for @a settings and the return value.
     */
    sql::string browse (sql::Connection& connection,
                        const sql::string& settings);

    /*!
     * @brief Enumerator for named ODBC data sources.
     *
     * Enumeration of data sources typically looks like:
     * @code
     *  Environment& environment = ...;
     *  DataSources data_sources(environment);
     *  while (data_sources.next()) {
     *    std::cout
     *      << data_sources.name() << ": "
     *      << data_sources.info() << "."
     *      << std::endl;
     *  }
     * @endcode
     */
    class DataSources
    {
        /* nested types. */
    public:
        /*!
         * @brief Enumeration type for categories of data sources.
         *
         * @see DataSources::DataSources(Environment&,Type)
         * @see user()
         * @see system()
         * @see all()
         */
        typedef ::SQLUSMALLINT Type;

        /* class methods. */
    public:
        /*!
         * @brief List all data sources configured for the current user.
         */
        static Type user ();

        /*!
         * @brief List all data sources configured for the system.
         */
        static Type system ();

        /*!
         * @brief List all data sources.
         */
        static Type all ();

        /* data. */
    private:
        Environment& myEnvironment;
        ::SQLUSMALLINT myDirection;

        string myName;
        string myInfo;

        /* construction. */
    public:
        /*!
         * @brief Prepare enumeration of data sources in @a environment.
         * @param environment Environment in which to look for data sources.
         * @param type Type of sources to enumerate.
         *
         * @see user()
         * @see system()
         * @see all()
         */
        DataSources (Environment& environment, Type type=all());

        /* methods. */
    public:
        /*!
         * @brief Fetch information about the next data source.
         * @return @c true if @c name() and @c info() are valid.
         */
        bool next ();

        /*!
         * @brief Get the data source name.
         * @return The data source name.
         * @pre @c next() just returned @c true.
         */
        const string& name () const {
            return (myName);
        }

        /*!
         * @brief Get the data source driver name.
         * @return The data source driver name.
         * @pre @c next() just returned @c true.
         */
        const string& info () const {
            return (myInfo);
        }
    };

} }

#endif /* _sql_odbc_hpp__ */
