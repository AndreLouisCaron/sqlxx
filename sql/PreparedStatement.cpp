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

#include <sql/PreparedStatement.hpp>
#include <sql/Connection.hpp>
#include <sql/Diagnostic.hpp>

// Since ::SQLBindParameter() does not have a const-correct interface. It's 3rd
// parameter indicates if it should read or write to the given location. If this
// value is SQL_PARAM_INPUT, the data is not modified, even though it requires
// write-access to the value. Do not be surprised to see const casts to discard
// qualifiers.

namespace sql {

    PreparedStatement::PreparedStatement (
        Connection& connection, const string& query
        )
        : Statement(connection), myNext(1)
    {
            // Indicate the statement will be using bound parameters.
        ::SQLRETURN result = ::SQLPrepare(
            handle().value(), const_cast<character*>(query.data()), SQL_NTS
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
    }

    void PreparedStatement::execute ()
    {
            // Execute query with currently bound parameters.
        Statement::execute();
        
            // Prepare for re-execution of the same query.
        reset();
    }

    void PreparedStatement::reset ()
    {
        myNext = 1;
    }

    void PreparedStatement::bind ( const int8& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_STINYINT,
            SQL_TINYINT, 0, 0, const_cast<int8*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const uint8& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_UTINYINT,
            SQL_TINYINT, 0, 0, const_cast<uint8*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const int16& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_SSHORT,
            SQL_SMALLINT, 0, 0, const_cast<int16*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const uint16& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_USHORT,
            SQL_SMALLINT, 0, 0, const_cast<uint16*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const int32& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,
            0, 0, const_cast<int32*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const uint32& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER,
            0, 0, const_cast<uint32*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const int64& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_SBIGINT,
            SQL_BIGINT, 0, 0, const_cast<int64*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const uint64& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_UBIGINT,
            SQL_BIGINT, 0, 0, const_cast<uint64*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const float& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL,
            0, 0, const_cast<float*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const double& value )
    {
        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,
            0, 0, const_cast<double*>(&value), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const string& value )
    {
        ::SQLLEN length = SQL_NTS;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
            value.length(), 0, const_cast<character*>(value.data()), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const wstring& value )
    {
        ::SQLLEN length = SQL_NTS;
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WCHAR,
            value.length(), 0, const_cast<wcharacter*>(value.data()), 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(handle()));
        }
        ++myNext;
    }

    void PreparedStatement::bind ( const Date& date )
    {
        ::SQLLEN length = 0;
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

    void PreparedStatement::bind ( const Guid& guid )
    {
        ::SQLLEN length = 0;
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

    void PreparedStatement::bind ( const Numeric& numeric )
    {
        ::SQLLEN length = 0;
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

    void PreparedStatement::bind ( const Time& time )
    {
        ::SQLLEN length = 0;
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

    void PreparedStatement::bind ( const Timestamp& timestamp )
    {
        ::SQLLEN length = 0;
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

    PreparedStatement& reset ( PreparedStatement& update )
    {
        update.reset();
        return (update);
    }

}
