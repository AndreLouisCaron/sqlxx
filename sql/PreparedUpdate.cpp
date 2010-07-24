// Copyright (c) 2009, Andre Caron
//
// This package is free software; you can redistribute it and/or modify it
// under the terms of a Berkely Software Distribution (BSD) license.
//
// This package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the accompanying "license.txt" file
// for more details.
//

/*!
 * @file PreparedUpdate.cpp
 * @author Andre Caron
 */

#include <sql/PreparedUpdate.hpp>
#include <sql/Diagnostic.hpp>

// Since ::SQLBindParameter() does not have a const-correct interface. It's 3rd
// parameter indicates if it should read or write to the given location. If this
// value is SQL_PARAM_INPUT, the data is not modified, even though it requires
// write-access to the value. Do not be surprised to see const casts to discard
// qualifiers.

namespace sql {

    PreparedUpdate::PreparedUpdate (
        Connection& connection, const string& query
        )
        : PreparedStatement(connection,query), myNext(1)
    {
    }

    void PreparedUpdate::reset ()
    {
        myNext = 1;
    }

    void PreparedUpdate::bind ( const int8& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_STINYINT,
            SQL_TINYINT, 0, 0, const_cast<int8*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const uint8& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_UTINYINT,
            SQL_TINYINT, 0, 0, const_cast<uint8*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const int16& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_SSHORT,
            SQL_SMALLINT, 0, 0, const_cast<int16*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const uint16& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_USHORT,
            SQL_SMALLINT, 0, 0, const_cast<uint16*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const int32& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,
            0, 0, const_cast<int32*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const uint32& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER,
            0, 0, const_cast<uint32*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const int64& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_SBIGINT,
            SQL_BIGINT, 0, 0, const_cast<int64*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const uint64& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_UBIGINT,
            SQL_BIGINT, 0, 0, const_cast<uint64*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const float& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL,
            0, 0, const_cast<float*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const double& value )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,
            0, 0, const_cast<double*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const string& value )
    {
        int32 length = SQL_NTS;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
            value.length(), 0, const_cast<character*>(value.data()), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const wstring& value )
    {
        int32 length = SQL_NTS;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WCHAR,
            value.length(), 0, const_cast<wcharacter*>(value.data()), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const Date& date )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_TYPE_DATE,
            SQL_TYPE_TIME, sizeof(::SQL_DATE_STRUCT), 0,
            const_cast<::SQL_DATE_STRUCT*>(&date.value()), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const Guid& guid )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_GUID,
            SQL_GUID, sizeof(::SQLGUID), 0,
            const_cast<::SQLGUID*>(&guid.value()), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const Numeric& numeric )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_NUMERIC,
            SQL_NUMERIC, sizeof(::SQL_NUMERIC_STRUCT), 0,
            const_cast<::SQL_NUMERIC_STRUCT*>(&numeric.value()), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const Time& time )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_TYPE_TIME,
            SQL_TYPE_TIME, sizeof(::SQL_TIME_STRUCT), 0,
            const_cast<::SQL_TIME_STRUCT*>(&time.value()), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedUpdate::bind ( const Timestamp& timestamp )
    {
        int32 length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP,
            SQL_TYPE_TIMESTAMP, sizeof(::SQL_TIMESTAMP_STRUCT), 0,
            const_cast<::SQL_TIMESTAMP_STRUCT*>(&timestamp.value()), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    PreparedUpdate& reset ( PreparedUpdate& update )
    {
        update.reset();
        return (update);
    }

}
