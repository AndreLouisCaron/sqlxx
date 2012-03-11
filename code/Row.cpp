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

#include "Row.hpp"
#include "Diagnostic.hpp"
#include "Results.hpp"

namespace {

    int filter ( unsigned int exception, ::EXCEPTION_POINTERS * pointers )
    {
        return (EXCEPTION_EXECUTE_HANDLER);
    }

}

namespace sql {

#if 0

    Row& Row::operator>> ( int8& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_STINYINT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( uint8& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_UTINYINT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( int16& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_SSHORT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( uint16& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_USHORT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( int32& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_SLONG,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( uint32& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_ULONG,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( int64& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_SBIGINT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( uint64& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_UBIGINT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( float& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_FLOAT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( double& value )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_DOUBLE,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( string& value )
    {
        value.clear();

        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLRETURN result = SQL_SUCCESS;
        character buffer[32];
        do
        {
                // Hmmm... this shouldn't happen. We aren't checking the the
                // proper conditions for column exhaustion.
            __try
            {
                ::SQLLEN length = 0;
                result = ::SQLGetData(
                    myResults->handle().value(), myColumn, SQL_C_CHAR,
                    buffer, sizeof(buffer), &length
                    );
                value += buffer;
            }
            __except (::filter(GetExceptionCode(),GetExceptionInformation()))
            {
                myResults = 0;
                return (*this);
            }
        }
            // Should check the diagnosis...
        while ( result == SQL_SUCCESS_WITH_INFO );

        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }

        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( wstring& value )
    {
        value.clear();

        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLRETURN result = SQL_SUCCESS;
        wcharacter buffer[32];
        do
        {
            ::SQLLEN length = 0;
            result = ::SQLGetData(
                myResults->handle().value(), myColumn, SQL_C_WCHAR, buffer,
                sizeof(buffer), &length
                );
            value += buffer;
        }
            // Should check the diagnosis...
        while ( result == SQL_SUCCESS_WITH_INFO );

        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }

        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( Date& date )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_TYPE_DATE,
            &date.value(), sizeof(::SQL_DATE_STRUCT), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( Guid& guid )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_GUID, &guid.value(),
            sizeof(::SQLGUID), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( Numeric& numeric )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_NUMERIC,
            &numeric.value(), sizeof(::SQL_NUMERIC_STRUCT), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( Time& time )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_TYPE_TIME,
            &time.value(), sizeof(::SQL_TIME_STRUCT), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& Row::operator>> ( Timestamp& timestamp )
    {
        if ( myResults == 0 ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myResults->handle().value(), myColumn, SQL_C_TYPE_TIMESTAMP,
            &timestamp.value(), sizeof(::SQL_TIMESTAMP_STRUCT), &length
            );
        if ( result != SQL_SUCCESS ) {
            myResults = 0;
        }
        ++myColumn;
        return (*this);
    }

    Row& skip ( Row& row )
    {
        row.skip();
        return (row);
    }

#endif

}

