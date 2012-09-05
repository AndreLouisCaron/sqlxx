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
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the accompanying "license.txt" file
// for more details.
//

#include "PreparedStatement.hpp"
#include "Connection.hpp"
#include "Diagnostic.hpp"

// Since ::SQLBindParameter() does not have a const-correct interface. It's 3rd
// parameter indicates if it should read or write to the given location. If this
// value is SQL_PARAM_INPUT, the data is not modified, even though it requires
// write-access to the value. Do not be surprised to see const casts to discard
// qualifiers.

namespace {

    // Shared between all null values.  Must be available between calls
    // to PreparedStatement::bind() and PreparedStatement::execute().
    ::SQLLEN null_value = SQL_NULL_DATA;

    // Shared between all string parameters.  Must be available between calls
    // to PreparedStatement::bind() and PreparedStatement::execute().
    ::SQLLEN null_terminated = SQL_NTS;

}

namespace sql {

    PreparedStatement::PreparedStatement (Connection& connection,
                                          const string& text)
        : Statement(connection), myNext(1)
    {
            // Indicate the statement will be using bound parameters.
        ::SQLRETURN result = ::SQLPrepare(
            handle().value(), const_cast<character*>(text.data()), SQL_NTS
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
    }

    PreparedStatement& PreparedStatement::execute ()
    {
            // Execute query with currently bound parameters.
        Statement::execute();
        
            // Prepare for re-execution of the same query.
        return (reset());
    }

    int16 PreparedStatement::parameter_count () const
    {
        ::SQLSMALLINT count = 0;
        const ::SQLRETURN result = ::SQLNumParams(handle().value(), &count);
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        return (count);
    }

    int16 PreparedStatement::column_count () const
    {
        ::SQLSMALLINT count = 0;
        const ::SQLRETURN result = ::SQLNumResultCols(handle().value(), &count);
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        return (count);
    }

    bool PreparedStatement::generated_results () const
    {
        return (column_count() > 0);
    }

    PreparedStatement& PreparedStatement::reset ()
    {
        myNext = 1; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const Null&)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT,
            0, 0, 0, 0, 0, 0, &::null_value
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const int8& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_STINYINT,
            SQL_TINYINT, 0, 0, const_cast<int8*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const uint8& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_UTINYINT,
            SQL_TINYINT, 0, 0, const_cast<uint8*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const int16& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_SSHORT,
            SQL_SMALLINT, 0, 0, const_cast<int16*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const uint16& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_USHORT,
            SQL_SMALLINT, 0, 0, const_cast<uint16*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const int32& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_SLONG,
            SQL_INTEGER, 0, 0, const_cast<int32*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const uint32& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER,
            0, 0, const_cast<uint32*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const int64& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_SBIGINT,
            SQL_BIGINT, 0, 0, const_cast<int64*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const uint64& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_UBIGINT,
            SQL_BIGINT, 0, 0, const_cast<uint64*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const float& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL,
            0, 0, const_cast<float*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const double& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,
            0, 0, const_cast<double*>(&value), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const string& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
            value.length(), 0, const_cast<character*>(value.data()), 0,
            &::null_terminated
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const wstring& value)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WCHAR,
            value.length(), 0, const_cast<wcharacter*>(value.data()), 0,
            &::null_terminated
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const Date& date)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_TYPE_DATE,
            SQL_TYPE_DATE, SQL_DATE_LEN, 0,
            const_cast<::SQL_DATE_STRUCT*>(&date.value()), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const Guid& guid)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_GUID,
            SQL_GUID, sizeof(::SQLGUID), 0,
            const_cast<::SQLGUID*>(&guid.value()), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const Numeric& numeric)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_NUMERIC,
            SQL_NUMERIC, sizeof(::SQL_NUMERIC_STRUCT), 0,
            const_cast<::SQL_NUMERIC_STRUCT*>(&numeric.value()), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const Time& time)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_TYPE_TIME,
            SQL_TYPE_TIME, SQL_TIME_LEN, 0,
            const_cast<::SQL_TIME_STRUCT*>(&time.value()), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& PreparedStatement::bind (const Timestamp& timestamp)
    {
        ::SQLRETURN result = ::SQLBindParameter(
            handle().value(), myNext, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP,
            SQL_TYPE_TIMESTAMP, sizeof(::SQL_TIMESTAMP_STRUCT), 0,
            const_cast<::SQL_TIMESTAMP_STRUCT*>(&timestamp.value()), 0, 0
            );
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(handle()));
        }
        ++myNext; return (*this);
    }

    PreparedStatement& operator>> (PreparedStatement& statement,
                                   Parameter& parameter)
    {
        const ::SQLRETURN result = ::SQLDescribeParam(
            statement.handle().value(), statement.myNext,
            &parameter.myType, &parameter.mySize,
            &parameter.myBits, &parameter.myNull);
        if (result != SQL_SUCCESS) {
            throw (Diagnostic(statement.handle()));
        }
        ++statement.myNext; return (statement);
    }

    PreparedStatement& reset (PreparedStatement& statement)
    {
        return (statement.reset());
    }

    PreparedStatement& execute (PreparedStatement& statement)
    {
        return (statement.execute());
    }

    Parameter::Parameter ()
        : myType(SQL_UNKNOWN_TYPE)
        , mySize(0)
        , myBits(0)
        , myNull(0)
    {
    }

    int16 Parameter::type () const
    {
        return (myType);
    }

    size_t Parameter::size () const
    {
        return (mySize);
    }

    int16 Parameter::bits () const
    {
        return (myBits);
    }

    bool Parameter::nullable () const
    {
        return (myNull == SQL_NULLABLE);
    }

    bool Parameter::is_unknown_type () const
    {
        return (myType == SQL_UNKNOWN_TYPE);
    }

    bool Parameter::is_int8 () const
    {
        return (myType == SQL_TINYINT);
    }

    bool Parameter::is_int16 () const
    {
        return (myType == SQL_SMALLINT);
    }

    bool Parameter::is_int32 () const
    {
        return (myType == SQL_INTEGER);
    }

    bool Parameter::is_int64 () const
    {
        return (myType == SQL_BIGINT);
    }

    bool Parameter::is_float () const
    {
        return (myType == SQL_REAL);
    }

    bool Parameter::is_double () const
    {
        return (myType == SQL_DOUBLE);
    }

    bool Parameter::is_numeric () const
    {
        return (myType == SQL_NUMERIC);
    }

    bool Parameter::is_varchar () const
    {
        return (myType == SQL_VARCHAR);
    }

    bool Parameter::is_bytes () const
    {
        return (myType == SQL_CHAR);
    }

    bool Parameter::is_string () const
    {
        return (myType == SQL_WCHAR);
    }

    bool Parameter::is_guid () const
    {
        return (myType == SQL_GUID);
    }

    bool Parameter::is_date () const
    {
        return (myType == SQL_TYPE_DATE);
    }

    bool Parameter::is_time () const
    {
        return (myType == SQL_TYPE_TIME);
    }

    bool Parameter::is_timestamp () const
    {
        return (myType == SQL_TYPE_TIMESTAMP);
    }

}
