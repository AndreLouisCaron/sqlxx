// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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

