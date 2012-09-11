#ifndef _sql_catalog_hpp__
#define _sql_catalog_hpp__

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

#include "Statement.hpp"

namespace sql {

    // <http://msdn.microsoft.com/en-us/library/windows/desktop/ms711722.aspx>

    /*!
     * @brief Enumerates all catalogs in the database.
     *
     * @see Connection::max_catalog_name_size()
     */
    class Catalogs :
        public Statement
    {
        /* construction. */
    public:
        /*!
         * @brief Enumerate catalogs in @a connection's data source.
         * @param connection Connection to the data source of interest.
         */
        Catalogs (Connection& connection);
    };

    /*!
     * @brief Enumerates all schemas in the database.
     *
     * @see Connection::max_schema_name_size()
     */
    class Schemas :
        public Statement
    {
        /* construction. */
    public:
        /*!
         * @brief Enumerate schemas in @a connection's data source.
         * @param connection Connection to the data source of interest.
         */
        Schemas (Connection& connection);
    };

    /*!
     * @brief Enumerates types of tables in the database.
     */
    class TableTypes :
        public Statement
    {
        /* construction. */
    public:
        /*!
         * @brief Enumerate table types in @a connection's data source.
         * @param connection Connection to the data source of interest.
         */
        TableTypes (Connection& connection);
    };

    /*!
     * @brief Enumerates all tables in the database.
     *
     * @see Connection::max_table_name_size()
     */
    class Tables :
        public Statement
    {
        /* construction. */
    public:
        /*!
         * @brief Enumerate tables in @a connection's data source.
         * @param connection Connection to the data source of interest.
         */
        Tables (Connection& connection);
    };

}

#endif /* _sql_catalog_hpp__ */
