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

#include "Connection.hpp"
#include "Diagnostic.hpp"
#include <iostream>

namespace {

    ::SQLHANDLE allocate ( sql::Environment& environment )
    {
        ::SQLHANDLE handle = SQL_NULL_HANDLE;
        const ::SQLRETURN result = ::SQLAllocHandle(
            SQL_HANDLE_DBC, environment.handle().value(), &handle
            );
        if ( result != SQL_SUCCESS ) {
            throw (sql::Diagnostic(environment.handle()));
        }
        return (handle);
    }

    ::SQLSMALLINT get_string_attribute_size
        (::SQLHDBC connection, ::SQLUSMALLINT field)
    {
        ::SQLSMALLINT size = 0;
        const ::SQLRETURN result = ::SQLGetInfoA
            (connection, field, 0, 0, &size);
        if ((result != SQL_SUCCESS) && (result != SQL_SUCCESS_WITH_INFO))
        {
            const sql::Handle handle(connection,
                                     SQL_HANDLE_DBC,
                                     &sql::Handle::proxy);
            throw (sql::Diagnostic(handle));
        }
        return (size);
    }

    void get_string_attribute_data (::SQLHDBC connection, ::SQLUSMALLINT field,
                                    ::SQLPOINTER data, ::SQLSMALLINT size)
    {
        ::SQLSMALLINT used = 0;
        const ::SQLRETURN result = ::SQLGetInfoA
            (connection, field, data, size, &used);
        if (result != SQL_SUCCESS)
        {
            const sql::Handle handle(connection,
                                     SQL_HANDLE_DBC,
                                     &sql::Handle::proxy);
            const sql::Diagnostic diagnostic(handle);
            if (result != SQL_SUCCESS_WITH_INFO) {
                throw (diagnostic);
            }
        }
        // Enforce null terminator.
        ((::SQLCHAR*)data)[used] = '\0';
    }

    sql::string get_string_attribute
        (::SQLHDBC connection, ::SQLUSMALLINT field)
    {
        const ::SQLUSMALLINT size =
            get_string_attribute_size(connection, field);
        sql::string attribute(size);
        get_string_attribute_data(connection, field, attribute.data(), size);
        return (attribute);
    }

    ::SQLUSMALLINT get_uint16_attribute (::SQLHDBC connection,
                                         ::SQLUSMALLINT field)
    {
        ::SQLUSMALLINT data = 0;
        const ::SQLRETURN result = ::SQLGetInfoA
            (connection, field, &data, 0, 0);
        if (result != SQL_SUCCESS)
        {
            const sql::Handle handle(connection,
                                     SQL_HANDLE_DBC,
                                     &sql::Handle::proxy);
            const sql::Diagnostic diagnostic(handle);
            if (result != SQL_SUCCESS_WITH_INFO) {
                throw (diagnostic);
            }
        }
        return (data);
    }

    ::SQLUINTEGER get_uint32_attribute (::SQLHDBC connection,
                                         ::SQLUSMALLINT field)
    {
        ::SQLUINTEGER data = 0;
        const ::SQLRETURN result = ::SQLGetInfoA
            (connection, field, &data, 0, 0);
        if (result != SQL_SUCCESS)
        {
            const sql::Handle handle(connection,
                                     SQL_HANDLE_DBC,
                                     &sql::Handle::proxy);
            const sql::Diagnostic diagnostic(handle);
            if (result != SQL_SUCCESS_WITH_INFO) {
                throw (diagnostic);
            }
        }
        return (data);
    }

}

namespace sql {

    Connection::Connection ( Environment& environment )
        : myHandle(::allocate(environment), SQL_HANDLE_DBC, &Handle::claim)
    {
    }

    Connection::~Connection ()
    {
    }

    const Handle& Connection::handle () const throw()
    {
        return (myHandle);
    }

    void Connection::enable_autocommit ()
    {
        const ::SQLINTEGER attribute = SQL_ATTR_AUTOCOMMIT;
        const ::SQLPOINTER data =
            reinterpret_cast<SQLPOINTER>(SQL_AUTOCOMMIT_ON);
        const ::SQLINTEGER size = SQL_IS_UINTEGER;
        const ::SQLRETURN result = ::SQLSetConnectAttr
            (handle().value(), attribute, data, size);
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    void Connection::disable_autocommit ()
    {
        const ::SQLINTEGER attribute = SQL_ATTR_AUTOCOMMIT;
        const ::SQLPOINTER data =
            reinterpret_cast<SQLPOINTER>(SQL_AUTOCOMMIT_OFF);
        const ::SQLINTEGER size = SQL_IS_UINTEGER;
        const ::SQLRETURN result = ::SQLSetConnectAttr
            (handle().value(), attribute, data, size);
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    void Connection::commit ()
    {
        ::SQLRETURN result = ::SQLEndTran(
            handle().type(), handle().value(), SQL_COMMIT
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    void Connection::rollback ()
    {
        ::SQLRETURN result = ::SQLEndTran(
            handle().type(), handle().value(), SQL_ROLLBACK
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    string Connection::driver_odbc_version () const
    {
        return (get_string_attribute(handle().value(), SQL_DRIVER_ODBC_VER));
    }

    string Connection::driver_name () const
    {
        return (get_string_attribute(handle().value(), SQL_DRIVER_NAME));
    }

    string Connection::driver_version () const
    {
        return (get_string_attribute(handle().value(), SQL_DRIVER_VER));
    }

    string Connection::database_name () const
    {
        return (get_string_attribute(handle().value(), SQL_DATABASE_NAME));
    }

    string Connection::host_name () const
    {
        return (get_string_attribute(handle().value(), SQL_SERVER_NAME));
    }

    string Connection::user_name () const
    {
        return (get_string_attribute(handle().value(), SQL_USER_NAME));
    }

    string Connection::data_source_name () const
    {
        return (get_string_attribute(handle().value(), SQL_DATA_SOURCE_NAME));
    }

    uint16 Connection::max_driver_connections () const
    {
        return (get_uint16_attribute(handle().value(),
                                    SQL_MAX_DRIVER_CONNECTIONS));
    }

    uint32 Connection::create_table_support () const
    {
        return (get_uint32_attribute(handle().value(),
                                     SQL_CREATE_TABLE));
    }

}
