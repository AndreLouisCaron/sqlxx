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

#include "Results.hpp"
#include "Diagnostic.hpp"

#include <iostream>

namespace {

    int filter ( unsigned int exception, ::EXCEPTION_POINTERS * pointers )
    {
        return (EXCEPTION_EXECUTE_HANDLER);
    }

}

namespace sql {

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
