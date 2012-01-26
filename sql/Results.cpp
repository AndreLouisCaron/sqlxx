// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Results.hpp>
#include <sql/Diagnostic.hpp>

#include <iostream>

namespace {

    int filter ( unsigned int exception, ::EXCEPTION_POINTERS * pointers )
    {
        return (EXCEPTION_EXECUTE_HANDLER);
    }

}

namespace sql {

    const Row row;
    const Null null;

    const Results::State Results::State::good(0);
    const Results::State Results::State::null(1);
    const Results::State Results::State::fail(2);

    Results::State::State ( unsigned int bits )
        : myBits(bits)
    {
    }

    Results::State::State ()
        : myBits(0)
    {
    }

    void Results::State::set ( const State& bits )
    {
        myBits |= bits.myBits;
    }

    void Results::State::clear ( const State& bits )
    {
        myBits &= bits.myBits;
    }

    bool Results::State::get ( const State& bits )
    {
        return ((myBits & bits.myBits) != 0);
    }

    Results::State::operator bool () const
    {
        return (myBits == 0);
    }

    Results::State& Results::State::operator&= ( const State& other )
    {
        clear(other); return (*this);
    }

    Results::State& Results::State::operator|= ( const State& other )
    {
        set(other); return (*this);
    }

    Results::State Results::State::operator& ( const State& other ) const
    {
        return (State(myBits & other.myBits));
    }

    Results::State Results::State::operator| ( const State& other ) const
    {
        return (State(myBits | other.myBits));
    }

    size_t Results::rows () const
    {
        ::SQLLEN count = 0;
        const ::SQLRETURN result = ::SQLRowCount(
            myStatement.handle().value(), &count
            );
        if ( result != SQL_SUCCESS ) {
            throw (Diagnostic(myStatement.handle()));
        }
        return (count);
    }

    Results& Results::operator>> ( const Row& )
    {
        if ( !myState ) {
            return (*this);
        }

        const ::SQLRETURN result = ::SQLFetch(myStatement.handle().value());
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        myColumn = 1;
        return (*this);
    }

    Results& Results::operator>> ( const Null& )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_CHAR, 0, 0, &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( int8& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_STINYINT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( uint8& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_UTINYINT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( int16& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_SSHORT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( uint16& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_USHORT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( int32& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_SLONG,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( uint32& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_ULONG,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( int64& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_SBIGINT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( uint64& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_UBIGINT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( float& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_FLOAT,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( double& value )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_DOUBLE,
            &value, sizeof(value), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( string& value )
    {
        value.clear();

        if ( !myState ) {
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
                    myStatement.handle().value(), myColumn, SQL_C_CHAR,
                    buffer, sizeof(buffer), &length
                    );
                value += buffer;
            }
            __except (::filter(GetExceptionCode(),GetExceptionInformation()))
            {
                myState.set(State::fail);
                return (*this);
            }
        }
            // Should check the diagnosis...
        while ( result == SQL_SUCCESS_WITH_INFO );

        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }

        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( wstring& value )
    {
        value.clear();

        if ( !myState ) {
            return (*this);
        }

        ::SQLRETURN result = SQL_SUCCESS;
        wcharacter buffer[32];
        do
        {
            ::SQLLEN length = 0;
            result = ::SQLGetData(
                myStatement.handle().value(), myColumn, SQL_C_WCHAR, buffer,
                sizeof(buffer), &length
                );
            value += buffer;
        }
            // Should check the diagnosis...
        while ( result == SQL_SUCCESS_WITH_INFO );

        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( Date& date )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_TYPE_DATE,
            &date.value(), sizeof(::SQL_DATE_STRUCT), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( Guid& guid )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_GUID, &guid.value(),
            sizeof(::SQLGUID), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( Numeric& numeric )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_NUMERIC,
            &numeric.value(), sizeof(::SQL_NUMERIC_STRUCT), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( Time& time )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_TYPE_TIME,
            &time.value(), sizeof(::SQL_TIME_STRUCT), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

    Results& Results::operator>> ( Timestamp& timestamp )
    {
        if ( !myState ) {
            return (*this);
        }

        ::SQLLEN length = 0;
        ::SQLRETURN result = ::SQLGetData(
            myStatement.handle().value(), myColumn, SQL_C_TYPE_TIMESTAMP,
            &timestamp.value(), sizeof(::SQL_TIMESTAMP_STRUCT), &length
            );
        if ( result != SQL_SUCCESS ) {
            myState.set(State::fail);
        }
        ++myColumn;
        return (*this);
    }

}
